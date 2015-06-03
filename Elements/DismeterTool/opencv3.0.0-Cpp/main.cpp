#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	int Threshold = 140;
	int DBlur = 8;
	Mat src;
    Mat img;
    vector<vector<Point> > contours;
	Point2f center1;
	Point2f center2;
	vector<Vec4i> hierarchy;
	float radius1;
	float radius2;
	namedWindow("image");
	createTrackbar("Threshold", "image", &Threshold, 255, 0);
	createTrackbar("DBlur", "image", &DBlur, 15, 0);
	while (1)
	{
		int key = waitKey(30) & 0xFF;
		if (key == 27)
			break;
		Threshold = getTrackbarPos("Threshold", "image");
		DBlur = getTrackbarPos("DBlur", "image");
        src = imread("./temp/1.bmp", 1);
		cvtColor(src, img, COLOR_RGB2GRAY);
		threshold(img, img, Threshold, 255, THRESH_BINARY);
		medianBlur(img, img, (2 * DBlur + 1));
		findContours(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
		

		if (contours.size()>=3)
		{
			minEnclosingCircle(contours[0], center1, radius1);
			minEnclosingCircle(contours[2], center2, radius2);
			center1 = Point2i(center1);
			center2 = Point2i(center2);
			circle(src, center1, radius1, CV_RGB(0, 0, 255), 2);
			circle(src, center2, radius2, CV_RGB(0, 130, 0), 2);

            float r = radius1 / radius2*125.0;
			char text[255];
            sprintf(text, "r = %.2f um", r);

			putText(src, text, Point(110, 110), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0, 0, 255), 2);
            putText(src, "R = 125 um", Point(110, 80), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0, 130, 0), 2);
			putText(src, "Press ESC To Exit", Point(400, 550), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255,0, 0), 2);
			imshow("image", src);
		}
           imwrite("./temp/result1.png",src);
	}
	return 0;
}
