#include "camera.h"
#include "ui_camera.h"

camera::camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
}

camera::~camera()
{
    delete ui;
}
