#include "showmask.h"
#include "ui_showmask.h"
#include "computervision.h"

showMask::showMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showMask)
{
    ui->setupUi(this);
    show();
}

showMask::~showMask()
{
    delete ui;
}

void showMask::updateMask(cv::Mat frame){
    QImage qimgNOBG((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_Indexed8);
    ui->label->setPixmap(QPixmap::fromImage(qimgNOBG));
}
