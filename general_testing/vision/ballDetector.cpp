#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int hmin = 37, smin = 106, vmin = 123;
int hmax = 53, smax = 208, vmax = 255;

int main()
{
    Mat img = imread("images/view1.jpg");
    Mat imgHSV, imgMask, imgResize, imgDilate;

    resize(img, imgResize, Size(), .25, .25);

    cvtColor(imgResize, imgHSV, COLOR_BGR2HSV);

    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);

    inRange(imgHSV, lower, upper, imgMask);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgMask, imgDilate, kernel);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(imgResize, contours, -1, Scalar(255, 0, 255), 1);

    for (vector<Point> &contour : contours)
    {
        Moments m = moments(contour);
        double xCenter = m.m10 / m.m00;
        double yCenter = m.m01 / m.m00;

        stringstream point;
        point << "(" << xCenter << ", " << yCenter << ")";
        string text = point.str();

        putText(imgResize, text, Point((int)xCenter, (int)yCenter), FONT_HERSHEY_DUPLEX, .3, Scalar(255, 255, 255), .2);
        cout << xCenter << ", " << yCenter << endl;
    }

    imshow("mask", imgMask);
    imshow("dilated masked", imgDilate);
    imshow("original", imgResize);
    waitKey(0);
}