#include "windowstartup.h"
#include "themainwindow.h"
windowStartup::windowStartup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::windowStartup)
{
    ui->setupUi(this);
    show();
}

windowStartup::~windowStartup()
{
    delete ui;
}



void windowStartup::on_createProjectButton_clicked()
{
    new newProject();
    close();
}

void windowStartup::on_commandLinkButton_clicked()
{
    new cameraDiscovery();
    close();
}
