#include "showshape.h"
#include "ui_showshape.h"

showShape::showShape(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showShape)
{
    ui->setupUi(this);
}

showShape::~showShape()
{
    delete ui;
}

void showShape::updateShape(cv::Mat frame){
    QImage qimgNOBG((uchar*) frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qimgNOBG));
}
