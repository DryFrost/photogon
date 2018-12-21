#include "editmask.h"
#include "ui_editmask.h"
using namespace std;
editmask::editmask(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::editmask)
{
  ui->setupUi(this);
  timer = new QTimer(this);
  show();
  ui->b1Low->setSliderPosition(0);
  ui->b2Low->setSliderPosition(135);
  ui->b1High->setSliderPosition(120);
  ui->b2High->setSliderPosition(200);
  ui->thresholdLow->setSliderPosition(40);
  ui->thresholdHigh->setSliderPosition(255);
  ui->blurK->setSliderPosition(6);


}

editmask::~editmask()
{
  delete ui;
}



void editmask::on_thresholdLow_sliderReleased()
{

}

void editmask::on_thresholdHigh_sliderReleased()
{

}

void editmask::on_b1Low_sliderReleased()
{

}

void editmask::on_b1High_sliderReleased()
{

}

void editmask::on_b2Low_sliderReleased()
{

}

void editmask::on_b2High_sliderReleased()
{

}

void editmask::on_blurK_sliderReleased()
{

}

void editmask::on_pushButton_4_clicked()
{

}

void editmask::update_window()
{
  cap >> frame;

  tLowM = ui->thresholdLow->value();
  tHighM = ui->thresholdHigh->value();
  b1LM = ui->b1Low->value();
  b1HM = ui->b1High->value();
  b2LM = ui->b2Low->value();
  b2HM = ui->b2High->value();
  blurKM = ui->blurK->value();


  Size size(300,275);
  cv::resize(frame,frame,size);
  cvtColor(frame,frame,CV_BGR2RGB);
  qt_image = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
  ui->viewM->setPixmap(QPixmap::fromImage(qt_image));

  Mat dest;
  absdiff(blank,plant,dest);
  vector<Mat> channels(3);
  split(dest,channels);
  Mat dest_blur;
  blur(channels[1],dest_blur,Size(blurKM,blurKM));
  Mat dest_thresh;
  threshold(dest_blur,dest_thresh,tLowM,tHighM,THRESH_BINARY);
  Mat dest_dilate;
  dilate(dest_thresh,dest_dilate,Mat(), Point(-1,-1),5,1,1);
  Mat dest_erode;
  erode(dest_dilate,dest_erode,Mat(),Point(-1,-1),5,1,1);

  Mat dest_lab;
  cvtColor(dest,dest_lab,CV_BGR2Lab);
  vector<Mat> channels_lab;
  split(dest_lab,channels_lab);
  Mat pot_thresh1;
  inRange(channels_lab[2],b1LM,b1HM,pot_thresh1);
  Mat pot_thresh2;
  inRange(channels_lab[2],b2LM,b2HM,pot_thresh2);
  Mat pot_or;
  bitwise_or(pot_thresh1,pot_thresh2,pot_or);
  Mat pot_dilate;
  dilate(pot_or, pot_dilate, Mat(), Point(-1, -1), 2, 1, 1);
  Mat pot_erode;
  erode(pot_dilate,pot_erode, Mat(), Point(-1, -1), 3, 1, 1);
  Mat pot_and;
  bitwise_and(pot_erode,dest_erode,pot_and);

  cv::resize(pot_and,pot_and,size);
  qt_imageM = QImage((const unsigned char*)(pot_and.data),pot_and.cols,pot_and.rows,QImage::Format_Indexed8);
  ui->maskM->setPixmap(QPixmap::fromImage(qt_imageM));


}

void editmask::on_LoadCamera_clicked()
{

  QString camera = ui->comboBox->currentText();
  cap.open(0);
  cap >> frame;
  plant = Mat::zeros(frame.size(),CV_8UC3);
  blank = Mat::zeros(frame.size(),CV_8UC3);


  connect(timer,SIGNAL(timeout()),this,SLOT(update_window()));
  timer->start(20);

}

void editmask::on_capEmpty_clicked()
{
  cap >> frame;
  blank = frame;

}

void editmask::on_capPlant_clicked()
{
  cap >> frame;
  plant = frame;

}
