#pragma once
#include <opencv2/opencv.hpp>

class QuickOpenCVDemo
{
public:
    QuickOpenCVDemo();
    ~QuickOpenCVDemo();
    void colorSpaceTransfer(cv::Mat& image);
    void matCreation(cv::Mat &image);
    void pixelVisit(cv::Mat& image);
    void pixelOperators(cv::Mat& image);
    void trackingBar(cv::Mat& image);
    void keyOperators(cv::Mat& image);

private:
    static void onChangeLight(int pos, void* userdata);
    static void onChangeDark(int pos, void* userdata);
    static void onChangeContrast(int pos, void* userdata);
};

