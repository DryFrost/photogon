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

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    //qDebug() << dir;




    ui->setDirectoryButton->setEnabled(false);
    ui->lineEdit->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);


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

    int num = 0;
    int trial = 0;
    QSettings setup(ProjectDir,QSettings::IniFormat);
    setup.setValue("numTreatments",QVariant::fromValue(numTreatments));
    setup.setValue("numSamples",QVariant::fromValue(numSamples));
    setup.setValue("projectDir",QVariant::fromValue(dir));
    setup.setValue("treatmentList",QVariant::fromValue(treatmentList));
    setup.setValue("num",QVariant::fromValue(num));
    setup.setValue("numS",QVariant::fromValue(num));
    setup.setValue("trial",QVariant::fromValue(trial));
    //new theMainWindow();
    close();
}

void newProject::on_pushButton_3_clicked()
{
    numTreatments = ui->spinBox->value();
    numSamples = ui->spinBox_2->value();
    treatmentList = InputDialog::getStrings(this,numTreatments);
    if(!treatmentList.isEmpty()){
        qDebug() << treatmentList;
    }

}

void newProject::on_checkQR_clicked()
{
  if(ui->checkQR->isChecked()){
      ui->CreateQRCode->setEnabled(true);
      ui->pushButton_3->setEnabled(false);
      ui->spinBox->setEnabled(false);
      ui->spinBox_2->setEnabled(false);

    }else {
      ui->pushButton_3->setEnabled(true);
      ui->spinBox->setEnabled(true);
      ui->spinBox_2->setEnabled(true);
      ui->CreateQRCode->setEnabled(false);
}
}

void newProject::on_lineEdit_returnPressed()
{
    ui->checkQR->setEnabled(true);
}

void newProject::on_CreateQRCode_clicked()
{

    QSettings internal("ProjectDir.ini",QSettings::IniFormat);
    internal.setValue("projectDirA",QVariant::fromValue(dir));
    ProjectName = ui->lineEdit->text();
    ProjectDir = dir+"/"+ProjectName+".ini";
    internal.setValue("projectDir",QVariant::fromValue(ProjectDir));
    QSettings setup(ProjectDir,QSettings::IniFormat);
    setup.setValue("projectName",QVariant::fromValue(ProjectName));


    new QRGenerate();
}
