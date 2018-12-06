#include "worker.h"

#include "worker.h"
#include <QDebug>
#include <QThread>
#include <QTime>
Worker::Worker(QString path, int id) : filepath(path), index(id)
{

}

Worker::~Worker()
{
}

void Worker::readVideo(QString path)
{
    if (path.length() > 0)
        filepath = path;

    cv::VideoCapture cap("http://10.211.55.7:8080/stream.wmv");


    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            frame = cv::Mat(cv::Size(640, 480), CV_8UC3, cv::Scalar(192, 0, 0));
            emit frameFinished(frame, index);
            break;
        }


        emit frameFinished(frame.clone(), index);
        QThread::msleep(30);
    }

    emit finished(index);
}
