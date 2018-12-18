#ifndef EDITROI_H
#define EDITROI_H

#include <QDialog>
#include <QTimer>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Ui {
  class editROI;
}

class editROI : public QDialog
{
  Q_OBJECT

public:
  explicit editROI(QWidget *parent = nullptr);
  ~editROI();

private slots:
  void on_LoadCamera_clicked();

  void on_Up_clicked();

  void on_Right_clicked();

  void on_Down_clicked();

  void on_Left_clicked();

  void on_NextCorner_clicked();

  void on_Cancel_clicked();

  void on_Apply_clicked();

  void update_window();

private:
  Ui::editROI *ui;

  QTimer *timer;

  VideoCapture cap;
  Mat frame;
  QImage qt_image;
  int P1x;
  int P1y;
  int P2x;
  int P2y;
  bool point1;


};

#endif // EDITROI_H
