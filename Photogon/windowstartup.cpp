#include "windowstartup.h"
#include "themainwindow.h"
#include <QSettings>
#include <QFileDialog>
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

void windowStartup::on_openProjectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Existing Project"), "",
            tr("Project File (*.ini);;All Files (*)"));
    QSettings internal("ProjectDir.ini",QSettings::IniFormat);
    internal.setValue("projectDir",QVariant::fromValue(fileName));

}
