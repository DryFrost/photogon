#ifndef EDITMASK_H
#define EDITMASK_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <opencv2/imgproc.hpp>

using namespace cv;
namespace Ui {
  class editmask;
}

class editmask : public QDialog
{
  Q_OBJECT

public:
  explicit editmask(QWidget *parent = nullptr);
  ~editmask();

private slots:

  void on_thresholdLow_sliderReleased();

  void on_thresholdHigh_sliderReleased();

  void on_b1Low_sliderReleased();

  void on_b1High_sliderReleased();

  void on_b2Low_sliderReleased();

  void on_b2High_sliderReleased();

  void on_blurK_sliderReleased();

  void on_pushButton_4_clicked();

  void update_window();

  void on_LoadCamera_clicked();

  void on_capEmpty_clicked();

  void on_capPlant_clicked();

private:
  Ui::editmask *ui;

  QTimer *timer;

  VideoCapture cap;
  Mat frame;
  QImage qt_image;
  QImage qt_imageM;

  Mat blank;
  Mat plant;

  int tLowM;
  int tHighM;
  int b1LM;
  int b1HM;
  int b2LM;
  int b2HM;
  int blurKM;

};

#endif // EDITMASK_H
