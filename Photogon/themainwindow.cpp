#include "themainwindow.h"
#include "ui_themainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QThread>
#include "computervision.h"

theMainWindow::theMainWindow(QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::theMainWindow)
{
    int num=0;
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat >("cv::Mat");
    init();
    show();
    startupDialog();

}

theMainWindow::~theMainWindow()
{
    delete ui;
}

void theMainWindow::startupDialog(){
    new windowStartup(this);
}



void theMainWindow::on_actionNew_Project_triggered()
{
    new newProject();
}

void theMainWindow::init()
{

    numCams = 1;
    for(int i = 0; i < numCams; i++)
    {
        threads[i] = new QThread;
        workers[i] = new Worker(QString("http://10.106.47.112:8080/live.wmv"),i);

        workers[i]->moveToThread(threads[i]);

        connect(workers[i], SIGNAL(frameFinished(cv::Mat, int)), this, SLOT(displayFrame(cv::Mat,int)));
        connect(threads[i], SIGNAL(started()), workers[i], SLOT(readVideo()));

        connect(workers[i], SIGNAL(finished(int)), threads[i], SLOT(quit()));
        connect(workers[i], SIGNAL(finished(int)), workers[i], SLOT(deleteLater()));

        connect(threads[i], SIGNAL(finished()), threads[i], SLOT(deleteLater()));

        threads[i]->start();
    }
}

void theMainWindow::displayFrame(cv::Mat frame, int index)
{
    Frm = frame;
    cv::Size size(241,199);
    cv::resize(frame,frame,size);
    cvtColor(frame,frame,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    ui->Front->setPixmap(QPixmap::fromImage(qimgOriginal));


}

void theMainWindow::on_capBlank_clicked()
{
    cv::Size size(241,199);
    cv::resize(Frm,Frm,size);
    cvtColor(Frm,Frm,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) Frm.data,Frm.cols,Frm.rows,Frm.step,QImage::Format_RGB888);
    //ui->FrontC->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->capPlant->setEnabled(true);

}

void theMainWindow::on_capPlant_clicked()
{
    cv::Size size(241,199);
    cv::resize(Frm,Frm,size);
    cvtColor(Frm,Frm,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) Frm.data,Frm.cols,Frm.rows,Frm.step,QImage::Format_RGB888);
    ui->FrontC->setPixmap(QPixmap::fromImage(qimgOriginal));
    num=num+1;
    qDebug() << num;
    ui->Accept->setEnabled(true);

}

void theMainWindow::on_Accept_clicked()
{

}
