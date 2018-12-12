#ifndef SHOWHISTOGRAM_H
#define SHOWHISTOGRAM_H

#include <QDialog>

namespace Ui {
class showHistogram;
}

class showHistogram : public QDialog
{
    Q_OBJECT

public:
    explicit showHistogram(QWidget *parent = nullptr);
    ~showHistogram();

private:
    Ui::showHistogram *ui;
};

#endif // SHOWHISTOGRAM_H
