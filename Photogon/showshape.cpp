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
