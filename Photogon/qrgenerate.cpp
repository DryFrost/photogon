#include "qrgenerate.h"
#include "ui_qrgenerate.h"
#include "qrcode.hpp"
#include <QSettings>
#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <iostream>
#include <fstream>
#include <string>
#include <QtCore>
#include <QDebug>
QRGenerate::QRGenerate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QRGenerate)
{
  ui->setupUi(this);
  QSettings internal("ProjectDir.ini",QSettings::IniFormat);
  AprojDir = internal.value("projectDir").value<QString>();
  Adir = internal.value("projectDirA").value<QString>();
  QSettings setup(AprojDir,QSettings::IniFormat);
  AprojectName = setup.value("projectName").value<QString>();
  show();
}

QRGenerate::~QRGenerate()
{
  delete ui;
}

void QRGenerate::on_pushButton_clicked()
{
  int brd =4;
  QString msgfromtextbox = ui->lineEdit->text();
  std::string stringtext = msgfromtextbox.toStdString();
  const char *text = stringtext.c_str();
  qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(msgfromtextbox.toUtf8().constData(),qrcodegen::QrCode::Ecc::HIGH);
  std::ofstream myfile;
  myfile.open("temp.svg");
  myfile << qr.toSvgString(brd)<<std::endl;
  myfile.close();

  QSvgRenderer renderer(QString("temp.svg"));
  QImage image(200,200, QImage::Format_ARGB32);
  QPainter painter(&image);
  renderer.render(&painter);

  ui->label->setPixmap(QPixmap::fromImage(image));
  QString output;
  output = "Generated QR Code "+msgfromtextbox;
  ui->outputQ->addItem(output);

}

void QRGenerate::on_pushButton_2_clicked()
{

  const int brd =4;
  QString msgfromtextbox = ui->lineEdit->text();
  std::string stringtext = msgfromtextbox.toStdString();
  const char *text = stringtext.c_str();
  qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(msgfromtextbox.toUtf8().constData(),qrcodegen::QrCode::Ecc::HIGH);
  std::ofstream outfile;
  QString out;
  QString fileDir;
  fileDir = Adir+"/QRs/";
  if(!QDir(fileDir).exists()){
      QDir().mkdir(fileDir);
  }
  out = Adir+"/QRs/"+msgfromtextbox+".svg";
  outfile.open(out.toStdString());
  outfile << qr.toSvgString(brd)<<std::endl;
  outfile.close();
  //qDebug() << out;

}
