#include "mainwindow.h"
#include "themainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.init();
    //w.show();
    QApplication::setOrganizationName("MyOrganization");
    QApplication::setOrganizationDomain("MyDomain");
    QApplication::setApplicationName("MyAppName");
    new theMainWindow();


    return QApplication::exec();
}
