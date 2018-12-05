#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QLabel>
#include <QGridLayout>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType< cv::Mat >("cv::Mat");

    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //QGridLayout *grid = new QGridLayout;
    //int numCols = 2;

    numCams = 3;

    int row = 0, col = 0;
    for (int i = 0; i < numCams; i++)
    {
        //labels[i] = new QLabel;

        //row = i / numCols;
       // col = i % numCols;
       // grid->addWidget(labels[i], row, col);


        threads[i] = new QThread;
        workers[i] = new Worker(QString("http://192.168.0.36:8081"), i);
        workers[i]->moveToThread(threads[i]);

        connect(workers[i], SIGNAL(frameFinished(cv::Mat, int)), this, SLOT(displayFrame(cv::Mat,int)));
        connect(threads[i], SIGNAL(started()), workers[i], SLOT(readVideo()));

        connect(workers[i], SIGNAL(finished(int)), threads[i], SLOT(quit()));
        connect(workers[i], SIGNAL(finished(int)), workers[i], SLOT(deleteLater()));

        connect(threads[i], SIGNAL(finished()), threads[i], SLOT(deleteLater()));

        threads[i]->start();
    }

    //this->centralWidget()->setLayout(grid);

}

void MainWindow::displayFrame(cv::Mat frame, int index)
{
    cv::Size size(241,199);
    cv::resize(frame,frame,size);
   // if(index =0){
        QImage qimgOriginal((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888); // for color images
        ui->labels1->setPixmap(QPixmap::fromImage(qimgOriginal));
    //}else if (index = 1) {
       // QImage qimgOriginal((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888); // for color images
        ui->labels2->setPixmap(QPixmap::fromImage(qimgOriginal));
    //}else{
       // QImage qimgOriginal((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888); // for color images
        ui->labels3->setPixmap(QPixmap::fromImage(qimgOriginal));
    //}

}
