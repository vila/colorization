#include "chambolle.hh"
#include "gtest/gtest.h"
#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;

void test_chambolle(cv::Mat &input, cv::Mat &expected, double theta) {
    cv::Mat weight = cv::Mat::ones(input.rows, input.cols, CV_64FC1);

    // make sure input and expected are [0,1] and 64bit floating points images
    input.convertTo(input, CV_64FC1, 1.0/255.0);
    expected.convertTo(expected, CV_64FC1, 1.0/255.0);


    cv::Mat output(input.rows, input.cols, CV_64FC1);
    chambolle(input, output, theta, weight, 1000);

    double max_diff = cv::norm(output - expected, cv::NORM_INF);

    std::cout << "\\theta = " << theta << "\t ||expected - output||_inf = " << max_diff <<"\n";
    ASSERT_LT(max_diff, 0.01);
}


TEST(Chambolle, Lena_0_1) {
    cv::Mat input = cv::imread("test/data/lena_input.bmp", 0);
    cv::Mat expected = cv::imread("test/data/lena_expected_0.1.bmp", 0);
    test_chambolle(input, expected, 0.1);
}

TEST(Chambolle, Lena_0_01) {
    cv::Mat input = cv::imread("test/data/lena_input.bmp", 0);
    cv::Mat expected = cv::imread("test/data/lena_expected_0.01.bmp", 0);
    test_chambolle(input, expected, 0.01);
}

TEST(Chambolle, Lena_0_5) {
    cv::Mat input = cv::imread("test/data/lena_input.bmp", 0);
    cv::Mat expected = cv::imread("test/data/lena_expected_0.5.bmp", 0);
    test_chambolle(input, expected, 0.5);
}


