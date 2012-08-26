#ifndef CHAMBOLLE_H
#define CHAMBOLLE_H

#include <opencv2/opencv.hpp>

void grad(const cv::Mat &src, cv::Mat &dst1, cv::Mat &dst2);
void div(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);

void chambolle(const cv::Mat &g, cv::Mat &dst, double theta, const cv::Mat &weight, int iterations);

#endif /* CHAMBOLLE_H */
