#include "editroi.h"
#include "ui_editroi.h"

editROI::editROI(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::editROI)
{
  ui->setupUi(this);
  timer = new QTimer(this);
  show();
  P1x = 300;
  P1y = 100;
  P2x = 1000;
  P2y = 600;
  point1 = true;

}

editROI::~editROI()
{
  delete ui;
}

void editROI::on_LoadCamera_clicked()
{
  QString camera = ui->comboBox->currentText();
  cap.open(0);

  connect(timer,SIGNAL(timeout()),this,SLOT(update_window()));
  timer->start(20);
}

void editROI::on_Up_clicked()
{
  if(point1 == true){
      P1y = P1y - 10;
    }
  else {
      P2y = P2y - 10;
    }

}

void editROI::on_Right_clicked()
{
  if(point1 == true){
      P1x = P1x + 10;
    }
  else {
      P2x = P2x + 10;
    }

}

void editROI::on_Down_clicked()
{

  if(point1 == true){
      P1y = P1y + 10;
    }
  else {
      P2y = P2y + 10;
    }

}

void editROI::on_Left_clicked()
{

  if(point1 == true){
      P1x = P1x - 10;
    }
  else {
      P2x = P2x - 10;
    }

}

void editROI::on_NextCorner_clicked()
{

  point1 = false;


}

void editROI::on_Cancel_clicked()
{
  disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
  cap.release();
  close();

}

void editROI::on_Apply_clicked()
{
  disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
  cap.release();

  Mat image = Mat::zeros(frame.size(),CV_8UC3);

  qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);

  ui->label->setPixmap(QPixmap::fromImage(qt_image));


}

void editROI::update_window()
{

  cap >> frame;

  cv::rectangle(frame,Point(P1x,P1y),Point(P2x,P2y),Scalar(255,255,0),4,LINE_8,0);

  Size size(200,200);
  cv::resize(frame,frame,size);
  cvtColor(frame,frame,CV_BGR2RGB);
  qt_image = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
  ui->label->setPixmap(QPixmap::fromImage(qt_image));
}
