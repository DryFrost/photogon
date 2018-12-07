#ifndef WINDOWSTARTUP_H
#define WINDOWSTARTUP_H

#include <QDialog>

namespace Ui {
class windowStartup;
}

class windowStartup : public QDialog
{
    Q_OBJECT

public:
    explicit windowStartup(QWidget *parent = nullptr);
    ~windowStartup();

private:
    Ui::windowStartup *ui;
};

#endif // WINDOWSTARTUP_H
