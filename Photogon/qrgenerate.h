#ifndef QRGENERATE_H
#define QRGENERATE_H

#include <QDialog>

namespace Ui {
  class QRGenerate;
}

class QRGenerate : public QDialog
{
  Q_OBJECT

public:
  explicit QRGenerate(QWidget *parent = nullptr);
  ~QRGenerate();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::QRGenerate *ui;
  QString AprojDir;
  QString Adir;
  QString AprojectName;
};

#endif // QRGENERATE_H
