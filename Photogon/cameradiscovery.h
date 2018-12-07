#ifndef CAMERADISCOVERY_H
#define CAMERADISCOVERY_H

#include <QDialog>

namespace Ui {
class cameraDiscovery;
}

class cameraDiscovery : public QDialog
{
    Q_OBJECT

public:
    explicit cameraDiscovery(QWidget *parent = nullptr);
    ~cameraDiscovery();

private:
    Ui::cameraDiscovery *ui;
};

#endif // CAMERADISCOVERY_H
