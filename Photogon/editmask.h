#ifndef EDITMASK_H
#define EDITMASK_H

#include <QDialog>

namespace Ui {
  class editmask;
}

class editmask : public QDialog
{
  Q_OBJECT

public:
  explicit editmask(QWidget *parent = nullptr);
  ~editmask();

private:
  Ui::editmask *ui;
};

#endif // EDITMASK_H
