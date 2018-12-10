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
    a.setOrganizationName("MyOrganization");
    a.setOrganizationDomain("MyDomain");
    a.setApplicationName("MyAppName");
    new theMainWindow();


    return a.exec();
}
