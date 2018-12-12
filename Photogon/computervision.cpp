#include "computervision.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <math.h>


using namespace cv;
using namespace std;

Mat fill_holes(Mat src){
    Mat dst = Mat::zeros(src.size(),src.type());
    vector<vector<Point>>contours;
    vector<Vec4i> hierarchy;
    findContours(src,contours,hierarchy, RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
    for(unsigned int i = 0; i < contours.size(); i++){
        drawContours(dst,contours,i,255,CV_FILLED);
    }
    return dst;
}
vector<Point> keep_roi(Mat img,Point tl, Point br, Mat &mask){
    //-- Get contours of mask
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //-- Get contours of rectangular roi
    Mat src = Mat::zeros(img.size(),img.type());
    rectangle(src,tl,br,255,CV_FILLED);

    vector<vector<Point> > contours_roi;
    vector<Vec4i> hierarchy_roi;
    findContours( src, contours_roi, hierarchy_roi, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //-- Keep only those contours that have a point inside roi
    vector<Point> cc;
    Mat kept = Mat::zeros(img.size(),img.type());
    for(unsigned int i=0; i < contours.size(); i++){
        for(unsigned int j=0; j<contours[i].size(); j++){
            int test = pointPolygonTest(contours_roi[0],Point2f(contours[i][j]),false);
            if(test==1 || test == 0){
                for(unsigned int k=0; k<contours[i].size(); k++){
                    cc.push_back(contours[i][k]);
                }
                drawContours(kept, contours, i, 255, CV_FILLED);
                break;
            }
        }
    }
    Mat kept_mask;
    bitwise_and(img,kept,kept_mask);

    mask = kept_mask;
    return cc;
}
vector<double> ComputerVision::get_shapes(vector<Point> cc,Mat mask){
    //-- Get measurements
    Moments mom = moments(mask,true);
    double area = mom.m00;
    convexHull( Mat(cc), hull, false );
    double hull_verticies = hull.size();
    double hull_area = contourArea(Mat(hull));
    double solidity = area/hull_area;
    double perimeter = arcLength(Mat(cc),false);
    cmx = mom.m10 / mom.m00;
    cmy = mom.m01 / mom.m00;
    Rect boundRect = boundingRect( cc );
    width = boundRect.width;
    height = boundRect.height;
    x = boundRect.x;
    y = boundRect.y;
    double circ = 4*M_PI*area/(perimeter*perimeter);
    double angle = -1;
    double ex = -1;
    double ey = -1;
    double emajor = -1;
    double eminor = -1;
    double eccen = -1;
    double round = -1;
    double ar = -1;
    if(cc.size() >= 6){
        Mat pointsf;
        Mat(cc).convertTo(pointsf, CV_32F);
        RotatedRect ellipse = fitEllipse(pointsf);
        angle = ellipse.angle;
        ex = ellipse.center.x;
        ey = ellipse.center.y;
        if(ellipse.size.height > ellipse.size.width){
            emajor = ellipse.size.height;
            eminor = ellipse.size.width;
        }else{
            eminor = ellipse.size.height;
            emajor = ellipse.size.width;
        }
        eccen = sqrt((1- eminor / emajor)*2);
        round = eminor/emajor;
        ar = emajor/eminor;
    }
    double shapes[20] = {area,hull_area,solidity,perimeter,width,height,cmx,cmy,hull_verticies,ex,ey,emajor,eminor,angle,eccen,circ,round,ar,x,y};
    vector<double> shapes_v(shapes,shapes+20);
    return shapes_v;
}

Mat ComputerVision::drawShapes(Mat org, vector<Point> cc){
    vector<vector<Point>> tmp;
    vector<vector<Point>> tmp1;
    tmp.push_back(hull);
    tmp1.push_back(cc);
    drawContours(org, tmp1,-1,Scalar(0,0,255),1);
    drawContours(org, tmp,-1,Scalar(255,0,0),1);
    cv::line(org, Point(x,y), Point(x+width,y), Scalar(0,0,255),2);
    cv::line(org,Point(cmx,y),Point(cmx,y+height),Scalar(0,0,255),2);
    cv::circle(org, Point(cmx,cmy), 10, Scalar(0,0,255),2);
    return org;
}

Mat get_color(Mat img,Mat mask){
    Mat composite;
    cvtColor(img,composite,COLOR_BGR2HSV);
    vector<Mat> channels1;
    split(composite, channels1);
    Mat hist;
    int dims = 1; // Only 1 channel, the hue channel
    int histSize = 180; // 180 bins, actual range is 0-360.
    float hranges[] = { 0, 180 }; // hue varies from 0 to 179, see cvtColor
    const float *ranges = {hranges};

    //-- Compute the histogram
    calcHist(&channels1[0],1,0,mask,hist, dims, &histSize, &ranges    ,true ,false);

    return hist;
}

Mat ComputerVision::get_RGB_HIST(Mat img, Mat mask){

    const size_t number_of_channels = img.channels();
    const cv::Scalar background_color(0,0,0);

    vector<Mat> split;
    cv::split(img,split);

    const int height = 480;
    const int width = 640;
    const int histogram_size = 256;
    const float range[] = {0,255};
    const float * ranges = {range};
    const bool uniform = true;
    const bool accumulate = false;

    const int margin = 3;
    const int min_y = margin;
    const int max_y = height - margin;
    const int thickness = 1;
    const int line_type = LINE_AA;
    const float bin_width = static_cast<float>(width)/static_cast<float>(histogram_size);
    Mat dst(height,width,CV_8UC3,background_color);
    cv::Scalar colors[] =
    {
        {255,0,0},
        {0,255,0},
        {0,0,255}
    };

    for (size_t idx=0; idx < split.size(); idx++)
    {
        const cv::Scalar colour = colors[idx % 3];

        cv::Mat & m = split[idx];

        cv::Mat histogram;
        cv::calcHist(&m, 1, 0, mask, histogram, 1, &histogram_size, &ranges, uniform, accumulate);

        cv::normalize(histogram, histogram, 0, dst.rows, cv::NORM_MINMAX);

        for (int i = 1; i < histogram_size; i++)
        {
            const int x1 = std::round(bin_width * (i - 1));
            const int x2 = std::round(bin_width * (i - 0));

            const int y1 = std::clamp(height - static_cast<int>(std::round(histogram.at<float>(i - 1))), min_y, max_y);
            const int y2 = std::clamp(height - static_cast<int>(std::round(histogram.at<float>(i - 0))), min_y, max_y);

            cv::line(dst, cv::Point(x1, y1), cv::Point(x2, y2), colour, thickness, line_type);
        }
    }

    return dst;




}

Mat ComputerVision::remove_background(Mat img){
    Mat dest_lab;
    cvtColor(img, dest_lab, CV_BGR2Lab);
    vector<Mat> channels_lab;
    split(dest_lab, channels_lab);
    Mat pot_thresh1;
    inRange(channels_lab[2],0,120,pot_thresh1);
    Mat pot_thresh2;
    inRange(channels_lab[2],135,200,pot_thresh2);
    Mat pot_or;
    bitwise_or(pot_thresh1,pot_thresh2,pot_or);
    Mat pot_dilate;
    dilate(pot_or, pot_dilate, Mat(), Point(-1, -1), 2, 1, 1);
    Mat pot_erode;
    erode(pot_dilate,pot_erode, Mat(), Point(-1, -1), 3, 1, 1);
    Mat pot_roi;
    vector<Point> cc_pot = keep_roi(pot_erode,Point(300,100),Point(1000,650),pot_roi);
    return pot_roi;
}

vector<Point> ComputerVision::get_cc(Mat img){
    Mat temp;
    vector<Point> cc_pot = keep_roi(img,Point(300,100),Point(1000,650),temp);
    return cc_pot;
}
