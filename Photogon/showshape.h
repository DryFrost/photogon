#ifndef SHOWSHAPE_H
#define SHOWSHAPE_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class showShape;
}

class showShape : public QDialog
{
    Q_OBJECT
public slots:
    void updateShape(cv::Mat frame);
public:
    explicit showShape(QWidget *parent = nullptr);
    ~showShape();

private:
    Ui::showShape *ui;
};

#endif // SHOWSHAPE_H
