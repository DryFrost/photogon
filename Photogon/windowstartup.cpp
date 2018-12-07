#include "windowstartup.h"
#include "ui_windowstartup.h"

windowStartup::windowStartup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::windowStartup)
{
    ui->setupUi(this);
}

windowStartup::~windowStartup()
{
    delete ui;
}
