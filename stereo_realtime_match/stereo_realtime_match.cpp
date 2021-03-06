// StereoCamera.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/utility.hpp"

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

bool selectObject;
Rect selection;
Point origin;
Mat xyz;
Mat disp, disp8;

static void onMouse(int event, int x, int y, int, void*)
{
	if (selectObject)
	{
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);
	}

	switch (event)
	{
	case EVENT_LBUTTONDOWN:   //鼠标左按钮按下的事件
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;

		cout << origin << "disparity is: " << disp.at<short>(origin) << endl;
		cout << origin << "in world coordinate is: " << xyz.at<Vec3f>(origin) << endl;
		break;
	case EVENT_LBUTTONUP:    //鼠标左按钮释放的事件
		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			break;
	}
}

int main()
{

	VideoCapture camera0(0);
	camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 320);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 240);

	union {
		char    c[5];
		int     i;
	} myfourcc;
	myfourcc.i = camera0.get(CV_CAP_PROP_FOURCC);
	myfourcc.c[4] = '\0';
	std::cout << "4cc0:" << myfourcc.c << std::endl;

	//if (!camera0.isOpened()) return 1;



	VideoCapture camera1(1);
	camera1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
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


	std::string intrinsic_filename = "intrinsics.yml";
	std::string extrinsic_filename = "extrinsics.yml";

	int SADWindowSize=5, numberOfDisparities=256;//15,32//better:5,256//
	//bool no_display;
	float scale=1;

	Ptr<StereoBM> bm = StereoBM::create(16, 9);
	Ptr<StereoSGBM> sgbm = StereoSGBM::create(0, 16, 3);

	Mat img1, img2;

	Rect roi1, roi2;
	Mat Q;

	FileStorage fs(intrinsic_filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		printf("Failed to open file %s\n", intrinsic_filename.c_str());
		return -1;
	}

	Mat M1, D1, M2, D2;
	fs["M1"] >> M1;
	fs["D1"] >> D1;
	fs["M2"] >> M2;
	fs["D2"] >> D2;

	M1 *= scale;
	M2 *= scale;

	fs.open(extrinsic_filename, FileStorage::READ);
	if (!fs.isOpened())
	{
		printf("Failed to open file %s\n", extrinsic_filename.c_str());
		return -1;
	}

	Mat R, T, R1, P1, R2, P2;
	fs["R"] >> R;
	fs["T"] >> T;


	bm->setPreFilterCap(31);//31
	bm->setBlockSize(SADWindowSize > 0 ? SADWindowSize : 9);
	bm->setMinDisparity(0);
	bm->setTextureThreshold(10);//10
	bm->setUniquenessRatio(15);//15
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(32);
	bm->setDisp12MaxDiff(1);

	sgbm->setPreFilterCap(63);
	int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
	sgbm->setBlockSize(sgbmWinSize);


	sgbm->setMinDisparity(0);
	sgbm->setNumDisparities(numberOfDisparities);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleWindowSize(100);
	sgbm->setSpeckleRange(32);
	sgbm->setDisp12MaxDiff(1);
	sgbm->setMode(StereoSGBM::MODE_SGBM);

	namedWindow("disparity", 0);
	setMouseCallback("disparity", onMouse, 0);

	//Size img_size = img1.size();
	Size img_size(640,480);

	stereoRectify(M1, D1, M2, D2, img_size, R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, 0, img_size, &roi1, &roi2);


	cout << "roi1.size before" << roi1.size() << endl;
	cout << "roi2.size before" << roi2.size() << endl;

	Mat map11, map12, map21, map22;
	initUndistortRectifyMap(M1, D1, R1, P1, img_size, CV_16SC2, map11, map12);
	initUndistortRectifyMap(M2, D2, R2, P2, img_size, CV_16SC2, map21, map22);

	while (true) {
		//grab and retrieve each frames of the video sequentially
		Mat3b frame0;
		camera0 >> frame0;
		//imshow("Videoleft", frame0);

		Mat3b frame1;
		camera1 >> frame1;
		//imshow("Videoright", frame1);

		cvtColor(frame0, img1, COLOR_BGR2GRAY);
		cvtColor(frame1, img2, COLOR_BGR2GRAY);


		Mat img1r, img2r;
		remap(img1, img1r, map11, map12, INTER_LINEAR);
		remap(img2, img2r, map21, map22, INTER_LINEAR);

		img1 = img1r;
		img2 = img2r;

		imshow("remapleft", img1);
		imshow("remapright", img2);

		numberOfDisparities = numberOfDisparities > 0 ? numberOfDisparities : ((img_size.width / 8) + 15) & -16;

		bm->setROI1(roi1);
		bm->setROI2(roi2);
		bm->setNumDisparities(numberOfDisparities);

		int cn = img1.channels();

		sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
		sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);

		copyMakeBorder(img1, img1, 0, 0, numberOfDisparities, 0, IPL_BORDER_REPLICATE);
		copyMakeBorder(img2, img2, 0, 0, numberOfDisparities, 0, IPL_BORDER_REPLICATE);

		bm->compute(img1, img2, disp);
		//sgbm->compute(img1, img2, disp);
		//sgbm->compute(img1, img2, disp);
		//cout << disp.size() << " ";
		disp = disp.colRange(numberOfDisparities, img1.cols);

		//cout << disp.size() << " "<<disp8.size() << endl;

		disp.convertTo(disp8, CV_8U, 255 / (numberOfDisparities*16.));

		reprojectImageTo3D(disp, xyz, Q, true);
		xyz = xyz * 16;
		//Mat vdispRGB = disp8;
		//cvtColor(disp8, vdispRGB, COLOR_GRAY2BGR);

		imshow("disparity", disp8);

		//wait for 40 milliseconds
		int c = waitKey(1);

		//exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27)
		if (27 == char(c)) break;
	}

	return 0;
}

