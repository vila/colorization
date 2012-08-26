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

void imagesc(const std::string &window, const cv::Mat &m) {
    double min_val, max_val;
    cv::minMaxLoc(m, &min_val, &max_val);

    cv::Mat scaled_m = (m - min_val) / (max_val - min_val);

    if(m.rows < 512 && m.cols < 512) {
        double scale = 2;
        while(scale * m.rows < 512)
            scale *= 2;

        cv::resize(scaled_m, scaled_m, cv::Size(), scale, scale, cv::INTER_NEAREST);
    }

    std::cout << "imagesc: " << window << " min: " << min_val << " max: " << max_val << "\n";
    cv::imshow(window.c_str(), scaled_m);   
}
