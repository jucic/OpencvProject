// StereoCamera.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<iostream>
#include "stdio.h"

using namespace cv;
using namespace std;

int main()
{

	VideoCapture camera0(0);
	//camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 320);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 240);

	union {
		char    c[5];
		int     i;
	} myfourcc;
	myfourcc.i = camera0.get(CV_CAP_PROP_FOURCC);
	myfourcc.c[4] = '\0';
	std::cout << "4cc0:" << myfourcc.c << std::endl;

	//unsigned f = (unsigned)camera0.get(CAP_PROP_FOURCC);
	//char fourcc2[] = {
	//	(char)f, // First character is lowest bits
	//	(char)(f >> 8), // Next character is bits 8-15
	//	(char)(f >> 16), // Next character is bits 16-23
	//	(char)(f >> 24), // Last character is bits 24-31
	//	'\0' // and don't forget to terminate
	//};
	//cout << camera0.get(CAP_PROP_FRAME_WIDTH) << endl;
	//cout << fourcc2 << endl;

	//if (!camera0.isOpened()) return 1;



	VideoCapture camera1(1);
	//camera1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera1.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	camera1.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	union {
		char    c[5];
		int     i;
	} myfourcc2;
	myfourcc2.i = camera1.get(CV_CAP_PROP_FOURCC);
	myfourcc2.c[4] = '\0';
	std::cout << "4cc1:" << myfourcc2.c << std::endl;

	//if (!camera1.isOpened()) return 1;

	camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 640);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 480);

	camera1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera1.set(CAP_PROP_FRAME_WIDTH, 640);
	camera1.set(CAP_PROP_FRAME_HEIGHT, 480);

	while (true) {
		//grab and retrieve each frames of the video sequentially
		Mat3b frame0;
		camera0 >> frame0;
		imshow("Video0", frame0);

		Mat3b frame1;
		camera1 >> frame1;
		imshow("Video1", frame1);

		//wait for 40 milliseconds
		int c = waitKey(40);

		//exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27)
		if (27 == char(c)) break;
	}

	return 0;
}

