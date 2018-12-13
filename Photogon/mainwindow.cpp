#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QLabel>
#include <QGridLayout>
#include "computervision.h"
using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType< cv::Mat >("cv::Mat");
    qDebug() << "Main thread " << QThread::currentThreadId();
    num = 0;
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{


    numCams = 1;

  const   int row = 0, col = 0;
    for (int i = 0; i < numCams; i++)
    {
        threads[i] = new QThread;
        workers[i] = new Worker(QString("http://10.106.47.112:8081/live.mpg"), i);
        workers[i]->moveToThread(threads[i]);

        connect(workers[i], SIGNAL(frameFinished(cv::Mat, int)), this, SLOT(displayFrame(cv::Mat,int)));
        connect(threads[i], SIGNAL(started()), workers[i], SLOT(readVideo()));

        connect(workers[i], SIGNAL(finished(int)), threads[i], SLOT(quit()));
        connect(workers[i], SIGNAL(finished(int)), workers[i], SLOT(deleteLater()));

        connect(threads[i], SIGNAL(finished()), threads[i], SLOT(deleteLater()));

        threads[i]->start();
    }



}

void MainWindow::displayFrame(cv::Mat frame, int index)
{
    Frm = frame;
    cv::Size size(241,199);
    Mat org;
    cv::resize(frame,org,size);
    cvtColor(org,org,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) org.data,org.cols,org.rows,org.step,QImage::Format_RGB888);
    ui->labels3->setPixmap(QPixmap::fromImage(qimgOriginal));
    ComputerVision cvA;
    Mat noBG = cvA.remove_background(frame);
    cv::resize(noBG,noBG,size);
    QImage qimgNOBG((uchar*) noBG.data,noBG.cols,noBG.rows,noBG.step,QImage::Format_Indexed8);
    ui->labels2->setPixmap(QPixmap::fromImage(qimgNOBG));
    Mat justPlant;
    org.copyTo(justPlant,noBG);
    QImage qimgJustPlant((uchar*) justPlant.data,justPlant.cols,justPlant.rows,justPlant.step,QImage::Format_RGB888);
    ui->labels1->setPixmap(QPixmap::fromImage(qimgJustPlant));
    Mat RGBHIST = cvA.get_RGB_HIST(org,noBG);
    QImage hist((uchar*) RGBHIST.data,RGBHIST.cols,RGBHIST.rows,RGBHIST.step,QImage::Format_RGB888);
    ui->histogram->setPixmap(QPixmap::fromImage(hist));
}

void MainWindow::on_pushButton_clicked()
{
    cv::Size size(241,199);
    cv::resize(Frm,Frm,size);
    cvtColor(Frm,Frm,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) Frm.data,Frm.cols,Frm.rows,Frm.step,QImage::Format_RGB888);
    ui->cap->setPixmap(QPixmap::fromImage(qimgOriginal));
    num=num+1;
    qDebug() << num;


}
