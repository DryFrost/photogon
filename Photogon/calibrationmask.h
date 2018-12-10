#ifndef CALIBRATIONMASK_H
#define CALIBRATIONMASK_H

#include <QDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTimer>
#include "worker.h"
#define MAX_NUM_CAM 4

namespace Ui {
class calibrationMask;
}

class QThread;


class calibrationMask : public QDialog
{
    Q_OBJECT

public:
    explicit calibrationMask(QWidget *parent = nullptr);
    ~calibrationMask();
    void init();
public slots:
    void displayFrame(cv::Mat frame, int index);

private:
    Ui::calibrationMask *ui;
    int numCams;
    QThread* threads[MAX_NUM_CAM];
    Worker* workers[MAX_NUM_CAM];
};

#endif // CALIBRATIONMASK_H
