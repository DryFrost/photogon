#ifndef SHOWHISTOGRAM_H
#define SHOWHISTOGRAM_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class showHistogram;
}

class showHistogram : public QDialog
{
    Q_OBJECT
public slots:
    void updateHist(cv::Mat frame);

public:
    explicit showHistogram(QWidget *parent = nullptr);
    ~showHistogram();

private:
    Ui::showHistogram *ui;
};

#endif // SHOWHISTOGRAM_H
