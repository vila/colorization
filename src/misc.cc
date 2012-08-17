#include "misc.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

#include <iostream>

/* Note that this is actually not yuv but ycbcr TODO: rename stuff */
wxColour convert_yuv2rgb(int y, int u, int v) {
    // this is el terrible, TODO: rewrite when im not so lazy
    cv::Mat m(1,1,CV_8UC3,cv::Scalar(y,u,v));
    cv::cvtColor(m,m,CV_YCrCb2RGB);
    auto r = m.at<cv::Vec3b>(0,0);
    return wxColour(r[0],r[1],r[2]);
}
