#include "newprojectsetup.h"
#include "ui_newprojectsetup.h"

newProjectSetup::newProjectSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProjectSetup)
{
    ui->setupUi(this);
}

newProjectSetup::~newProjectSetup()
{
    delete ui;
}
