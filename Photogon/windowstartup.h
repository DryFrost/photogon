#ifndef WINDOWSTARTUP_H
#define WINDOWSTARTUP_H

#include <QDialog>


#include "ui_windowstartup.h"


class theMainWindow;

class windowStartup : public QDialog
{
    Q_OBJECT

public:
    explicit windowStartup(QWidget *parent = nullptr);
    ~windowStartup();

private slots:
    void on_createProjectButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::windowStartup *ui;
};

#endif // WINDOWSTARTUP_H
