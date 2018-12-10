#include "worker.h"

#include "worker.h"
#include <QDebug>
#include <QThread>
#include <QTime>
Worker::Worker(QString path, int id, bool b) : filepath(path), index(id), Stop(b)
{

}

Worker::~Worker()
{
}

void Worker::readVideo(QString path)
{
    if (path.length() > 0)
        filepath = path;

    cv::VideoCapture cap(0);


    cv::Mat frame;
    while (Stop=true)
    {

        cap >> frame;
        if (frame.empty())
        {
            frame = cv::Mat(cv::Size(640, 480), CV_8UC3, cv::Scalar(192, 0, 0));
            emit frameFinished(frame, index);
            break;
        }




        emit frameFinished(frame.clone(), index);


        QThread::msleep(40);
    }


    emit finished(index);
}
