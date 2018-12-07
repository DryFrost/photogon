#ifndef CALIBRATIONMASK_H
#define CALIBRATIONMASK_H

#include <QDialog>

namespace Ui {
class calibrationMask;
}

class calibrationMask : public QDialog
{
    Q_OBJECT

public:
    explicit calibrationMask(QWidget *parent = nullptr);
    ~calibrationMask();

private:
    Ui::calibrationMask *ui;
};

#endif // CALIBRATIONMASK_H
