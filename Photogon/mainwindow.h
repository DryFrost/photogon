#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTimer>
#include "worker.h"
#define MAX_NUM_CAM 4
namespace Ui {
class MainWindow;
}

class QThread;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();

public slots:
    void displayFrame(cv::Mat frame, int index);
private:
    Ui::MainWindow *ui;
    int numCams;
    QLabel *labels[MAX_NUM_CAM];
    QThread* threads[MAX_NUM_CAM];
    Worker* workers[MAX_NUM_CAM];
};

#endif // MAINWINDOW_H
