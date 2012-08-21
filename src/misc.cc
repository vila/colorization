#include "misc.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

wxColour ycbcr2rgb(const cv::Scalar &ycbcr) {
    // this is el terrible, TODO: rewrite when im not so lazy
    cv::Mat m(1,1,CV_8UC3,ycbcr);
    cv::cvtColor(m,m,CV_YCrCb2RGB);
    auto r = m.at<cv::Vec3b>(0,0);
    return wxColour(r[0],r[1],r[2]);
}


bool ends_with(const std::string &str, const std::string &with, bool ignore_case) {
    if(str.length() < with.length())
        return false;

    int offset = str.length() - with.length();   

    if(ignore_case)
        return equal(begin(str)+offset, end(str), begin(with),
                     [](char a, char b){return ::toupper(a) == ::toupper(b); });
    else
        return equal(begin(str)+offset, end(str), begin(with));
}
