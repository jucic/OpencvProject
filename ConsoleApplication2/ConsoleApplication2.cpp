#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;
int main(int, char**)
{
	VideoCapture cap(0); // open the default camera

	if (!cap.isOpened())  // check if we succeeded
	{
		cout << "not_open" << endl;
		return -1;
	}

	unsigned f = (unsigned)cap.get(CAP_PROP_FOURCC);
	char fourcc[] = {
		(char)f, // First character is lowest bits
		(char)(f >> 8), // Next character is bits 8-15
		(char)(f >> 16), // Next character is bits 16-23
		(char)(f >> 24), // Last character is bits 24-31
		'\0' // and don't forget to terminate
	};
	cout << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
	cout << fourcc << endl;

	cap.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 720);

	f = (unsigned)cap.get(CAP_PROP_FOURCC);
	char fourcc2[] = {
		(char)f, // First character is lowest bits
		(char)(f >> 8), // Next character is bits 8-15
		(char)(f >> 16), // Next character is bits 16-23
		(char)(f >> 24), // Last character is bits 24-31
		'\0' // and don't forget to terminate
	};
	cout << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
	cout << fourcc2 << endl;

	//waitKey(1000);

	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		imshow("frame", frame);
		if (waitKey(30) >= 0) break;
	}

	return 0;
}
