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
#include "showmask.h"
#include "showhistogram.h"
#include "showshape.h"
#include "editroi.h"
#include "editmask.h"
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
    cv::Mat FrmA;
    cv::Mat FrmC;
    cv::Mat noBGS;
    cv::Mat hist;
    QString AprojectName;
    int AnumTreatments;
    int AnumSamples;
    QString AprojDir;
    QStringList AtreatmentList;
    int Anum;
    int AnumS;
    int Atrial;
    QString Adir;
    std::vector<double> shapes;

    void init();



signals:
    void SendMask(cv::Mat frame);
    void SendHist(cv::Mat frame);
    void SendShape(cv::Mat frame);


public slots:
    void displayFrame(cv::Mat frame, int index);

private slots:
    void startupDialog();
    void on_actionNew_Project_triggered();
    void on_capBlank_clicked();

    void on_capPlant_clicked();

    void on_Accept_clicked();

    void on_pushButton_clicked();

    void on_end_clicked();

    void on_skip_clicked();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_actionEdit_ROI_triggered();

    void on_actionEdit_Mask_triggered();

private:
    Ui::theMainWindow *ui;
    int numCams;
    QThread* threads[MAX_NUM_CAM];
    Worker* workers[MAX_NUM_CAM];
    int num;
};

#endif // THEMAINWINDOW_H
