#include "calibrationmask.h"
#include "ui_calibrationmask.h"

calibrationMask::calibrationMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrationMask)
{
    ui->setupUi(this);
}

calibrationMask::~calibrationMask()
{
    delete ui;
}
