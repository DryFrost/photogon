#include "cameradiscovery.h"
#include "ui_cameradiscovery.h"

cameraDiscovery::cameraDiscovery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cameraDiscovery)
{
    ui->setupUi(this);
}

cameraDiscovery::~cameraDiscovery()
{
    delete ui;
}
