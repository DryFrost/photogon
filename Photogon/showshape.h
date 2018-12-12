#ifndef SHOWSHAPE_H
#define SHOWSHAPE_H

#include <QDialog>

namespace Ui {
class showShape;
}

class showShape : public QDialog
{
    Q_OBJECT

public:
    explicit showShape(QWidget *parent = nullptr);
    ~showShape();

private:
    Ui::showShape *ui;
};

#endif // SHOWSHAPE_H
