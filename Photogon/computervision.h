#ifndef COMPUTERVISION_H
#define COMPUTERVISION_H
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class ComputerVision
{
public:
    Mat remove_background(Mat img);
    Mat get_RGB_HIST(Mat img, Mat mask);
    vector<Point> get_cc(Mat img);
    vector<double> get_shapes(vector<Point> cc,Mat mask);
    Mat drawShapes(Mat img, vector<Point> cc);
private:
    vector<Point>hull;
    double x;
    double y;
    double width;
    double height;
    double cmx;
    double cmy;

};

#endif // COMPUTERVISION_H
