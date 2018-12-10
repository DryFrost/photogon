#ifndef NEWPROJECTSETUP_H
#define NEWPROJECTSETUP_H

#include <QDialog>

namespace Ui {
class newProjectSetup;
}

class newProjectSetup : public QDialog
{
    Q_OBJECT

public:
    explicit newProjectSetup(QWidget *parent = nullptr);
    ~newProjectSetup();

private slots:
    void on_pushButton_clicked();

private:
    Ui::newProjectSetup *ui;
};

#endif // NEWPROJECTSETUP_H
