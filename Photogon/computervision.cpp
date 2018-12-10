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
vector<double> get_shapes(vector<Point> cc,Mat mask){
    //-- Get measurements
    Moments mom = moments(mask,true);
    double area = mom.m00;
    vector<Point>hull;
    convexHull( Mat(cc), hull, false );
    double hull_verticies = hull.size();
    double hull_area = contourArea(Mat(hull));
    double solidity = area/hull_area;
    double perimeter = arcLength(Mat(cc),false);
    double cmx = mom.m10 / mom.m00;
    double cmy = mom.m01 / mom.m00;
    Rect boundRect = boundingRect( cc );
    double width = boundRect.width;
    double height = boundRect.height;
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
    double shapes[18] = {area,hull_area,solidity,perimeter,width,height,cmx,cmy,hull_verticies,ex,ey,emajor,eminor,angle,eccen,circ,round,ar};
    vector<double> shapes_v(shapes,shapes+18);
    return shapes_v;
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

    vector<Mat> bgr_planes;
    split(img,bgr_planes);
    int histSize = 256;
    float range[] = {0,256};
    const float* histRange = {range};
    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;

    calcHist( &bgr_planes[0], 1, 0, mask, b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, mask, g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, mask, r_hist, 1, &histSize, &histRange, uniform, accumulate );

    int hist_w = 321; int hist_h = 111;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    for( int i = 1; i < histSize; i++ )
    {
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                 Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                 Scalar( 255, 0, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                 Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                 Scalar( 0, 255, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                 Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                 Scalar( 0, 0, 255), 2, 8, 0  );
    }

    return histImage;

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

    return pot_erode;
}
