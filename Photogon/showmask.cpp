#include "showmask.h"
#include "ui_showmask.h"

showMask::showMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showMask)
{
    ui->setupUi(this);
}

showMask::~showMask()
{
    delete ui;
}
