#include "themainwindow.h"
#include "ui_themainwindow.h"

theMainWindow::theMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::theMainWindow)
{
    ui->setupUi(this);
}

theMainWindow::~theMainWindow()
{
    delete ui;
}
