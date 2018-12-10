#ifndef CAMERA_H
#define CAMERA_H

#include <QDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "themainwindow.h"
#include "worker.h"
#define MAX_NUM_CAM 4

namespace Ui {
class camera;
}
class QThread;
class camera : public QDialog
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = nullptr);
    ~camera();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

public slots:
    void displayFrame(cv::Mat frame,int index);

private:
    Ui::camera *ui;
    int numCams;
    QThread* threads[MAX_NUM_CAM];
    Worker* workers[MAX_NUM_CAM];
};

#endif // CAMERA_H
