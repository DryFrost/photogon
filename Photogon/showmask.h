#ifndef SHOWMASK_H
#define SHOWMASK_H

#include <QDialog>

namespace Ui {
class showMask;
}

class showMask : public QDialog
{
    Q_OBJECT

public:
    explicit showMask(QWidget *parent = nullptr);
    ~showMask();

private:
    Ui::showMask *ui;
};

#endif // SHOWMASK_H
