#include "misc.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

#include <iostream>

wxColour ycbcr2rgb(const cv::Scalar &ycbcr) {
    // this is el terrible, TODO: rewrite when im not so lazy
    cv::Mat m(1,1,CV_8UC3,ycbcr);
    cv::cvtColor(m,m,CV_YCrCb2RGB);
    auto r = m.at<cv::Vec3b>(0,0);
    return wxColour(r[0],r[1],r[2]);
}
