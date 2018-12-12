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
