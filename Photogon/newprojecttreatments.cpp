#include "newprojecttreatments.h"
#include "ui_newprojecttreatments.h"

newProjectTreatments::newProjectTreatments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProjectTreatments)
{
    ui->setupUi(this);
}

newProjectTreatments::~newProjectTreatments()
{
    delete ui;
}
