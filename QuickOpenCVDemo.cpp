#include "QuickOpenCVDemo.h"
#include <iostream>

using namespace std;
using namespace cv;

QuickOpenCVDemo::QuickOpenCVDemo()
{
    cout << "Construct QuickOpenCVDemo\n";
}

QuickOpenCVDemo::~QuickOpenCVDemo()
{
    cout << "Deconstruct QuickOpenCVDemo\n";
}

void QuickOpenCVDemo::colorSpaceTransfer(Mat& image)
{
    cout << "color space transfer\n";
    Mat gray, hsv;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    cvtColor(image, hsv, COLOR_RGB2HSV);
    // H 0-180, S:0-255, V:0-255
    // H��ɫ�ȣ���S�����Ͷȣ���V�����ȣ�

    imshow("Gray", gray);
    imshow("hsv", hsv);
    imwrite("E:\\Code\\OpenCVImages\\han_dmi_gray.jpg",gray);
    imwrite("E:\\Code\\OpenCVImages\\han_dmi_hsv.jpg", hsv);

    //waitKey(0);
}

void QuickOpenCVDemo::matCreation(Mat& image)
{
    Mat cloneMat, copyMat;
    cloneMat = image.clone();
    image.copyTo(copyMat);

    // create zero image
    Mat zeroImage = Mat::zeros(Size(3, 3), CV_8UC3);
    cout << zeroImage << endl;
    cout << "Width:" << zeroImage.cols << "\nHeight:" 
        << zeroImage.rows << "\nChannel:" << zeroImage.channels() << endl;
    
    cout << "=============================================================\n";
    // Mat::ones��������ͨ����ͼ���ϣ�ֻ���0ͨ����ֵΪ1��
    // 1,2ͨ������0��
    Mat onesImage = Mat::ones(Size(3, 3), CV_8UC3);
    cout << onesImage << endl;
    cout << "Width: " << onesImage.cols << "\n Height:"
        << onesImage.rows << "\nChannel: " << onesImage.channels() << endl;
    
    cout << "=============================================================\n";
    // Scalar()����ֱ�Ӹ�����ͨ����ֵ��
    onesImage = Scalar(2, 2, 255);
    cout << onesImage << endl;
    cout << "Width: " << onesImage.cols << "\n Height:"
        << onesImage.rows << "\nChannel: " << onesImage.channels() << endl;
    //imshow("onesImage", onesImage);

    cout << "=============================================================\n";
    Mat kernel = (Mat_<char>(3, 3) << 
        0,-1,0,
        -1,5,-1,
        0,-1,0 );
    cout << "kernel:\n" << kernel << endl;
}

void QuickOpenCVDemo::pixelVisit(Mat& image)
{
    cout << "pixel visit\n";
    int width = image.cols;
    int height = image.rows;
    int channel = image.channels();
    cout << "width: " << width << "\nheight: " << height
        << "\nchannel: " << channel;

    // �������ص㣬��ÿ��������ֵ��ת��255 - pixel��
    for (int col = 0;  col < width;  col++)
    {
        for (int row = 0; row < height; row++)
        {
            if (channel == 1)// ��ͨ���Ҷ�ͼ
            {
                uint8_t pixelValue = image.at<uint8_t>(row, col);
                image.at<uint8_t>(row, col) = 255 - pixelValue;
            }

            if (channel == 3)// ��ͨ��BGR
            {
                Vec3b bgr = image.at<Vec3b>(row, col);
                for (int i = 0; i < channel; i++)
                {
                    image.at<Vec3b>(row, col)[i] = 255 - bgr[i];
                }
            }
        }
    }

    imshow("���ض�д��ʾ", image);
}


void QuickOpenCVDemo::pixelOperators(cv::Mat& image)
{
    Mat subtractionImage = image - Scalar(100, 100, 100);// ����ͨ��ÿ�����ؼ�100��
    Mat addtionImage = image + Scalar(20, 20, 20);// ����ͨ��ÿ�����ؼ�20��
    Mat multiplyImage;
    Mat divideImage;
    Mat tmp = Mat::zeros(image.size(), image.type());
    tmp = Scalar(2, 2, 2);
    multiply(image, tmp, multiplyImage);
    add(image, tmp, addtionImage);
    subtract(image, tmp, subtractionImage);
    divide(image, tmp, divideImage);

    imshow("����", subtractionImage);
    imshow("�ӷ�", addtionImage);
    imshow("�˷�", multiplyImage);
    imshow("����", divideImage);

}

void QuickOpenCVDemo::onChangeLight(int pos, void* userdata)
{
    Mat* imagePtr = reinterpret_cast<Mat*>(userdata);
    Mat tmp = Mat::zeros(imagePtr->size(), imagePtr->type());
    Mat dest = Mat::zeros(imagePtr->size(), imagePtr->type());
    tmp = Scalar(pos, pos, pos);
    add(*imagePtr, tmp, dest);
    imshow("������Աȶȵ���", dest);
}

void QuickOpenCVDemo::onChangeDark(int pos, void* userdata)
{
    Mat* imagePtr = reinterpret_cast<Mat*>(userdata);
    Mat tmp = Mat::zeros(imagePtr->size(), imagePtr->type());
    Mat dest = Mat::zeros(imagePtr->size(), imagePtr->type());
    tmp = Scalar(pos, pos, pos);
    subtract(*imagePtr, tmp, dest);
    imshow("������Աȶȵ���", dest);
}

void QuickOpenCVDemo::onChangeContrast(int pos, void* userdata)
{
    Mat image = *reinterpret_cast<Mat*>(userdata);
    Mat tmp = Mat::zeros(image.size(), image.type());
    Mat dest = Mat::zeros(image.size(), image.type());
    addWeighted(image, pos, tmp, 0.0, 0, dest);
    imshow("������Աȶȵ���", dest);
}

void QuickOpenCVDemo::trackingBar(Mat& image)
{
    namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
    int maxLight = 100;
    int lightness = 1;
    createTrackbar("����", "������Աȶȵ���", NULL, maxLight, onChangeLight, reinterpret_cast<void *>(&image));
    setTrackbarPos("����", "������Աȶȵ���", 0);

    // ����û���ƶ�ʱ��Ҫ�ֶ�����һ�λص���������Ȼ�ʼ����ʾͼƬ
    onChangeLight(lightness, reinterpret_cast<void*>(&image));

    createTrackbar("����", "������Աȶȵ���", NULL, maxLight, onChangeDark, reinterpret_cast<void*>(&image));
    setTrackbarPos("����", "������Աȶȵ���", 0);

    int contrastMax = 5;
    createTrackbar("�Աȶ�", "������Աȶȵ���", NULL, contrastMax, onChangeContrast, reinterpret_cast<void*>(&image));
    setTrackbarPos("�Աȶ�", "������Աȶȵ���", 1);

}

void QuickOpenCVDemo::keyOperators(cv::Mat& image)
{
    Mat dest = Mat::zeros(image.size(), image.type());
    Mat tmp = Mat::zeros(image.size(), image.type());
    tmp = Scalar(100, 100, 100);
    while (true)
    {
        int c = waitKey(20);
        // c ��ASCII�룬27 = ESC (escape)
        // 49 = ����1
        // 50 = ����2
        // 51 = ����3
        switch (c)
        {
        case 27:
            cout << "Esc\n";
            return;
        case 49:
            cvtColor(image, dest, COLOR_BGR2GRAY);
            break;
        case 50:
            cvtColor(image, dest, COLOR_BGR2HSV);
            break;
        case 51:
            add(image, tmp, dest);
        default:
            break;
        }
        imshow("������Ӧ", dest);
    }
}