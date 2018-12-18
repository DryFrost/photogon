#include "editmask.h"
#include "ui_editmask.h"

editmask::editmask(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::editmask)
{
  ui->setupUi(this);
}

editmask::~editmask()
{
  delete ui;
}
