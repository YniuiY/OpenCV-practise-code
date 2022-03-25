#include "QuickOpenCVDemo.h"
#include <string>

using namespace std;
using namespace cv;

int main()
{
    const string imagePath("E:\\Code\\OpenCVImages\\han_dmi.jpg");
    //const string imagePath("E:\\Code\\OpenCVImages\\eatChecken.png");
    Mat image = imread(imagePath);
    if (image.empty())
    {
        cout << "image is empty\n";
        return -1;
    }
    

    namedWindow("บบ DM-i", WINDOW_FREERATIO);
    imshow("บบ DM-i", image);

    QuickOpenCVDemo quickDemo;
    //quickDemo.colorSpaceTransfer(image);
    //quickDemo.matCreation(image);
    //quickDemo.pixelVisit(image);
    //quickDemo.pixelOperators(image);
    //quickDemo.trackingBar(image);
    //quickDemo.keyOperators(image);

    waitKey(0);
    destroyWindow("บบ DM-i");

    return 0;
}