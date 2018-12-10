#include "newproject.h"
#include "ui_newproject.h"
#include <QFileDialog>
#include "themainwindow.h"
#include <QDebug>
#include <QSettings>
#include "inputdialog.h"
newProject::newProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProject)
{
    ui->setupUi(this);
    show();
}

newProject::~newProject()
{
    delete ui;
}

void newProject::on_setDirectoryButton_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    qDebug() << dir;
}

void newProject::on_pushButton_2_clicked()
{
    new windowStartup();
    close();
}

void newProject::on_commandLinkButton_clicked()
{
    new camera();
}

void newProject::on_pushButton_clicked()
{
    ProjectName = ui->lineEdit->text();
    QSettings setup("stuff.ini",QSettings::IniFormat);
    qDebug() << ProjectName;
    setup.setValue("projectName",QVariant::fromValue(ProjectName));
    new theMainWindow();
    close();
}

void newProject::on_pushButton_3_clicked()
{
    int numTreatments = ui->spinBox->value();
    QStringList list = InputDialog::getStrings(this,numTreatments);
    if(!list.isEmpty()){
        qDebug() << list;
    }

}
