#include "camera.h"
#include "ui_camera.h"
#include <QDebug>
#include <QtCore>
#include <QThread>
#include <QLabel>

camera::camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
    show();
    qRegisterMetaType<cv::Mat>("cv::Mat");
}

camera::~camera()
{
    delete ui;
}

void camera::on_pushButton_4_clicked()
{
    close();
}


void camera::on_pushButton_6_clicked()
{

    QString cam1IP = ui->camera1IP->text();
    QString cam2IP = ui->camera1IP->text();
    QString cam3IP = ui->camera1IP->text();



    numCams = 3;
    for (int i = 0; i < numCams;i++)
    {


        threads[i] = new QThread;
        workers[0] = new Worker(cam1IP,0);
        workers[1] = new Worker(cam2IP,1);
        workers[2] = new Worker(cam3IP,2);
        workers[i]->moveToThread(threads[i]);

        connect(workers[i], SIGNAL(frameFinished(cv::Mat, int)), this, SLOT(displayFrame(cv::Mat,int)));
        connect(threads[i], SIGNAL(started()), workers[i], SLOT(readVideo()));

        connect(workers[i], SIGNAL(finished(int)), threads[i], SLOT(quit()));
        connect(workers[i], SIGNAL(finished(int)), workers[i], SLOT(deleteLater()));

        connect(threads[i], SIGNAL(finished()), threads[i], SLOT(deleteLater()));

        threads[i]->start();

    }
}

void camera::displayFrame(cv::Mat frame, int index){
    cv::Size size(104,78);
    cv::resize(frame,frame,size);
    cv::cvtColor(frame,frame,cv::COLOR_BGR2RGB);
    if(index == 0){
        QImage viewA((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        ui->view1->setPixmap(QPixmap::fromImage(viewA));
    }else if(index == 1){
        QImage viewB((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        ui->view2->setPixmap(QPixmap::fromImage(viewB));
    }else if(index == 2){
        QImage viewC((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        ui->view3->setPixmap(QPixmap::fromImage(viewC));
    }

}

void camera::on_pushButton_5_clicked()
{
  workers[0]-> Stop = true;
  workers[1]-> Stop = true;
  workers[2]-> Stop = true;
  //new newProject();
  //close();
}

void camera::on_pushButton_clicked()
{
    new cameraDiscovery();
}
