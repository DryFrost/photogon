#include "themainwindow.h"
#include "ui_themainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QThread>
#include "computervision.h"
#include <QSettings>
#include <QTextStream>
#include <QTime>
#include <QDate>

theMainWindow::theMainWindow(QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::theMainWindow)

{
    int num=0;
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat >("cv::Mat");
    startupDialog();
    show();
    QString status = "Please Press Start when ready";
    ui->status->setText(status);


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

void theMainWindow::displayFrame(cv::Mat frame, int  index)
{
    Frm = frame;
    cv::Size size(256,200);
    cv::resize(frame,frame,size);
    cvtColor(frame,frame,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    ui->Front->setPixmap(QPixmap::fromImage(qimgOriginal));


}

void theMainWindow::on_capBlank_clicked()
{
    FrmC = Frm;
    ui->capPlant->setEnabled(true);
    QString status = "Please load "+AtreatmentList[Anum]+" sample "+QString::number(AnumS);
    ui->status->setText(status);
    ui->capBlank->setEnabled(false);

}

void theMainWindow::on_capPlant_clicked()
{
    FrmA = Frm;
    cv::Mat FrmAS;
    cv::Size size(256,200);
    cv::resize(FrmA,FrmAS,size);
    cvtColor(FrmAS,FrmAS,COLOR_BGR2RGB);
    QImage qimgOriginal((uchar*) FrmAS.data,FrmAS.cols,FrmAS.rows,FrmAS.step,QImage::Format_RGB888);
    ui->FrontC->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->Accept->setEnabled(true);
    QString status = "Press Accept to keep picture";
    ui->status->setText(status);

    ComputerVision cvA;
    Mat noBG = cvA.remove_background(FrmA);
    cv::Size size1(376,276);
    cv::resize(noBG,noBGS,size1);
    hist = cvA.get_RGB_HIST(Frm,noBG);
    cv::resize(hist,hist,size1);
    std::vector<Point> cc = cvA.get_cc(noBG);

    shapes = cvA.get_shapes(cc,noBG);

    Mat shapesImage = cvA.drawShapes(FrmA,cc);

    cv::resize(shapesImage,shapesImage,size1);



    emit SendMask(noBGS);
    emit SendHist(hist);
    emit SendShape(shapesImage);


}

void theMainWindow::on_Accept_clicked()
{
    QString fileName;
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString fileDir;
    fileDir = Adir+"/images";
    QDir(fileDir).exists();
    if(!QDir(fileDir).exists()){
        QDir().mkdir(fileDir);
    }
    fileName = Adir+"/images/"+AprojectName+"-"+"front"+"-"+AtreatmentList[Anum]+"-"+QString::number(AnumS)+"-"+QString::number(Atrial)+"-"+cd.toString()+"-"+ct.toString()+".png";
    std::string fileNameA = fileName.toUtf8().constData();
    cv::imwrite(fileNameA,Frm);

    QSettings setup(AprojDir,QSettings::IniFormat);
    setup.setValue("num",QVariant::fromValue(Anum));
    setup.setValue("numS",QVariant::fromValue(AnumS));
    setup.setValue("trial",QVariant::fromValue(Atrial));


    qDebug() << fileName;

    AnumS=AnumS+1;
    if(AnumS >= AnumSamples){
        AnumS = 0;
        Anum=Anum+1;
    }
    if(Anum >= AnumTreatments){
        Anum = 0;
        Atrial = Atrial+1;
    }

    setup.setValue("num",QVariant::fromValue(Anum));
    setup.setValue("numS",QVariant::fromValue(AnumS));
    setup.setValue("trial",QVariant::fromValue(Atrial));

    QString status = "Please empty the chamber and press Capture Blank";
    ui->status->setText(status);
    ui->capPlant->setEnabled(false);
    ui->Accept->setEnabled(false);
    ui->capBlank->setEnabled(true);

}

void theMainWindow::on_pushButton_clicked()
{

    QSettings internal("ProjectDir.ini",QSettings::IniFormat);
    AprojDir = internal.value("projectDir").value<QString>();
    Adir = internal.value("projectDirA").value<QString>();
    QSettings setup(AprojDir,QSettings::IniFormat);
    AprojectName = setup.value("projectName").value<QString>();
    AnumTreatments = setup.value("numTreatments").value<int>();
    AnumSamples = setup.value("numSamples").value<int>();
    AtreatmentList = setup.value("treatmentList").value<QStringList>();
    Anum = setup.value("num").value<int>();
    AnumS = setup.value("numS").value<int>();
    Atrial = setup.value("trial").value<int>();

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
    ui->pushButton->setEnabled(false);
    ui->capBlank->setEnabled(true);
    ui->end->setEnabled(true);
    ui->skip->setEnabled(true);

    QString status;

    status = "Please empty the chamber and press Capture Blank";
    ui->status->setText(status);

}

void theMainWindow::on_end_clicked()
{
    ui->pushButton->setEnabled(true);
}

void theMainWindow::on_skip_clicked()
{

}

void theMainWindow::on_commandLinkButton_clicked()
{
    auto *mshowMask = new showMask(this);
    connect(this,SIGNAL(SendMask(cv::Mat)),mshowMask,SLOT(updateMask(cv::Mat)));
    mshowMask->show();

}

void theMainWindow::on_commandLinkButton_2_clicked()
{
    auto *mshowHist = new showHistogram(this);
    connect(this,SIGNAL(SendHist(cv::Mat)),mshowHist,SLOT(updateHist(cv::Mat)));
    mshowHist->show();

}

void theMainWindow::on_commandLinkButton_3_clicked()
{
    auto *mshowShape = new showShape(this);
    connect(this,SIGNAL(SendShape(cv::Mat)),mshowShape,SLOT(updateShape(cv::Mat)));
    mshowShape->show();
}
