#ifndef COMPUTERVISION_H
#define COMPUTERVISION_H
#include <opencv2/opencv.hpp>
using namespace cv;

class ComputerVision
{
public:
    Mat remove_background(Mat img);
    Mat get_RGB_HIST(Mat img, Mat mask);
};

#endif // COMPUTERVISION_H
