#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <iostream>
#include <sstream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Maximize window on start
    this->setWindowState(Qt::WindowMaximized);


    ui->timeStep->appendPlainText(QString("20"));

    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));

    tmrTimer->start(ui->timeStep->toPlainText().toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFrameAndUpdateGUI(){

    cv::Mat original = cv::imread("/Users/dnguyen/Desktop/snapshot207042/pic.jpg");
    cv::Size size(600,600);
    cv::resize(original,original,size);

    // OpenCV to QImage datatype to display on labels
    cv::cvtColor(original,original,CV_BGR2RGB);
    QImage qimgOriginal((uchar*) original.data,original.cols,original.rows,original.step,QImage::Format_RGB888); // for color images
    // Update the labels on the form
    ui->label->setPixmap(QPixmap::fromImage(qimgOriginal));
}


