#ifndef THEMAINWINDOW_H
#define THEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class theMainWindow;
}

class theMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit theMainWindow(QWidget *parent = nullptr);
    ~theMainWindow();

private:
    Ui::theMainWindow *ui;
};

#endif // THEMAINWINDOW_H
