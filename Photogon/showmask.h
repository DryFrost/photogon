#ifndef SHOWMASK_H
#define SHOWMASK_H

#include <QDialog>
#include <opencv2/opencv.hpp>
namespace Ui {
class showMask;
}

class showMask : public QDialog
{
    Q_OBJECT
public slots:
    void updateMask(cv::Mat frame);
public:
    explicit showMask(QWidget *parent = nullptr);
    ~showMask();


private:
    Ui::showMask *ui;
};

#endif // SHOWMASK_H
