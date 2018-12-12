#include "showhistogram.h"
#include "ui_showhistogram.h"

showHistogram::showHistogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showHistogram)
{
    ui->setupUi(this);
}

showHistogram::~showHistogram()
{
    delete ui;
}

void showHistogram::updateHist(cv::Mat frame){
    QImage qimgNOBG((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qimgNOBG));
}
