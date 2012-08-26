#ifndef MISC_H
#define MISC_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <string>

wxColour ycbcr2rgb(const cv::Scalar &ycbcr);

bool ends_with(const std::string &str, const std::string &with, bool ignore_case = true);

// rescales float images to [0,1] and resizes them to atleast 512x512
void imagesc(const std::string &window, const cv::Mat &m);

#endif /* MISC_H */
