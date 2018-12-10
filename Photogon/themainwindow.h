#ifndef THEMAINWINDOW_H
#define THEMAINWINDOW_H

#include <QMainWindow>
#include <windowstartup.h>
#include "ui_themainwindow.h"
#include "newproject.h"
#include "camera.h"
#include "calibrationmask.h"
#include "cameradiscovery.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "worker.h"
#define MAX_NUM_CAM 4
namespace Ui {
class theMainWindow;
}

class QThread;

class theMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit theMainWindow(QWidget *parent = 0);
    ~theMainWindow();
    cv::Mat Frm;
    void init();
public slots:
    void displayFrame(cv::Mat frame, int index);

private slots:
    void startupDialog();
    void on_actionNew_Project_triggered();
    void on_capBlank_clicked();

    void on_capPlant_clicked();

    void on_Accept_clicked();

private:
    Ui::theMainWindow *ui;
    int numCams;
    QThread* threads[MAX_NUM_CAM];
    Worker* workers[MAX_NUM_CAM];
    int num;
};

#endif // THEMAINWINDOW_H
