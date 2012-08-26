#include "chambolle.hh"

#include <opencv2/opencv.hpp>

#include <iostream>

void conv(const cv::Mat& src, cv::Mat &dst, cv::Mat &kernel) {
    cv::filter2D(src, dst, CV_64F, kernel, cv::Point(kernel.cols/2,kernel.rows/2),
                 0.0, cv::BORDER_REPLICATE);
}

void grad(const cv::Mat &src, cv::Mat &dst1, cv::Mat &dst2) {
    cv::Mat G1(1, 3, CV_64FC1);
    cv::Mat G2(3, 1, CV_64FC1);

    G1.at<double>(0,0) =  0.0;
    G1.at<double>(0,1) = -1.0;
    G1.at<double>(0,2) =  1.0;

    G2.at<double>(0,0) =  0.0;
    G2.at<double>(1,0) = -1.0;
    G2.at<double>(2,0) =  1.0;

    conv(src, dst1, G1);
    conv(src, dst2, G2);
}

void div(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst) {
    cv::Mat D1(1, 3, CV_64FC1);
    cv::Mat D2(3, 1, CV_64FC1);

    D1.at<double>(0,0) = -1.0;
    D1.at<double>(0,1) =  1.0;
    D1.at<double>(0,2) =  0.0;

    D2.at<double>(0,0) = -1.0;
    D2.at<double>(1,0) =  1.0;
    D2.at<double>(2,0) =  0.0;

    int m = src1.rows;
    int n = src1.cols;

    cv::Mat d1(m,n,CV_64FC1);
    cv::Mat d2(m,n,CV_64FC1);
    conv(src1, d1, D1);
    conv(src2, d2, D2);
    cv::add(d1,d2,dst);
}

void chambolle(const cv::Mat &g, cv::Mat &dst, double theta,
               const cv::Mat &weight, int iterations) {
    double tau = 1.0/4.0;

    int m = g.rows;
    int n = g.cols;

    cv::Mat p1 = cv::Mat::zeros(m,n,CV_64FC1);
    cv::Mat p2 = cv::Mat::zeros(m,n,CV_64FC1);
    
    cv::Mat d_g1(m,n,CV_64FC1);
    cv::Mat d_g2(m,n,CV_64FC1);
    grad(g / theta, d_g1, d_g2);

    cv::Mat d1(m,n,CV_64FC1);
    cv::Mat d2(m,n,CV_64FC1);
    cv::Mat div_p(m,n,CV_64FC1);
    cv::Mat nd(m,n,CV_64FC1);

    for(int iter = 0; iter < iterations; iter++) {
        div(p1, p2, div_p);
        grad(div_p, d1, d2);

        d1 -= d_g1;
        d2 -= d_g2;

        cv::magnitude(d1,d2,nd);
        nd = 1.0 + tau * nd / weight;

        p1 = (p1 + tau * d1) / nd;
        p2 = (p2 + tau * d2) / nd;
    }

    div(p1, p2, div_p);
    dst = g - theta * div_p;
}
