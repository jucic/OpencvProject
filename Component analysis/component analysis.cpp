//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include "stdio.h"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture camera0(0);
	camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 320);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 240);

	VideoCapture camera1(1);
	camera1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera1.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	camera1.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 1280);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 720);

	camera1.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera1.set(CAP_PROP_FRAME_WIDTH, 1280);
	camera1.set(CAP_PROP_FRAME_HEIGHT, 720);

	while (true) 
	{
		//grab and retrieve each frames of the video sequentially
		Mat frame0,grey0,dst0;
		camera0 >> frame0;

		Mat frame1,grey1,dst1;
		camera1 >> frame1;
		//cout << frame1.size();

		if (frame1.empty() || frame0.empty()) continue;

		cvtColor(frame0, grey0, cv::COLOR_RGB2GRAY);
		cvtColor(frame1, grey1, cv::COLOR_RGB2GRAY);

		cv::GaussianBlur(grey0, grey0, Size(5,5), 0, 0);
		cv::GaussianBlur(grey1, grey1, Size(5, 5), 0, 0);

		adaptiveThreshold(grey0, dst0, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 601, -40);//在两种情况下，自适应阈值T(x, y)。通过计算每个像素周围bxb大小像素块的加权均值并减去常量C得到。其中，b由blockSize给出，大小必须为奇数；如果使用平均的方法，则所有像素周围的权值相同；如果使用高斯的方法，则（x,y）周围的像素的权值则根据其到中心点的距离通过高斯方程得到。
		adaptiveThreshold(grey1, dst1, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 601, -40);

		Mat labels0, stats0, centroids0, labels1, stats1, centroids1;//stats0组成: x,y,width,height和面积

		int64 t = getTickCount();
		int i, nccomps0,nccomps1; 
		nccomps0 = cv::connectedComponentsWithStats(dst0, labels0, stats0, centroids0);
		nccomps1 = cv::connectedComponentsWithStats(dst1, labels1, stats1, centroids1);
		t = getTickCount() - t;
		printf("Time elapsed: %fms\n", t * 1000 / getTickFrequency());

		vector<pair<cv::Point, long long>> center_l;
		for (int i = 1; i < stats0.rows; i++)
		{
			if (stats0.at<int>(i, 4) > 700 && stats0.at<int>(i, 4) < 70000)
			{
				center_l.push_back(pair<cv::Point, long long>(Point(stats0.at<int>(i, 0),stats0.at<int>(i, 1)), stats0.at<int>(i, 4)));
			}
		}
		cout << "totally " << center_l.size() << " object" << endl;

		//cout << "Total Connected Components Detected: " << nccomps0 << endl;
		vector<cv::Vec3b> colors(nccomps0 + 1);
		colors[0] = Vec3b(0, 0, 0); // background pixels remain black.
		for (i = 1; i < nccomps0; i++) 
		{
			colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
			if (stats0.at<int>(i, cv::CC_STAT_AREA) < 700|| stats0.at<int>(i, cv::CC_STAT_AREA) > 70000)
				colors[i] = Vec3b(0, 0, 0); // small regions are painted with black too.
		}
		Mat img_color = Mat::zeros(labels0.size(), CV_8UC3);
		for (int y = 0; y < img_color.rows; y++)
			for (int x = 0; x < img_color.cols; x++)
			{
				int label = labels0.at<int>(y, x);
				CV_Assert(0 <= label && label <= nccomps0);
				img_color.at<cv::Vec3b>(y, x) = colors[label];
			}
		cv::imshow("Labeled map", img_color);

		//int64 t = getTickCount();
		//int nccomps0 = cv::connectedComponentsWithStats(dst0, labels0, stats0, centroids0);
		//int nccomps1 = cv::connectedComponentsWithStats(dst1, labels1, stats1, centroids1);
		//t = getTickCount() - t;
		//printf("Time elapsed: %fms\n", t * 1000 / getTickFrequency());

		//namedWindow("Videoleft", WINDOW_KEEPRATIO);//time expensive
		//namedWindow("Videoright", WINDOW_KEEPRATIO);
		imshow("Videoleft", frame0);
		imshow("Videoright", frame1);

		imshow("Dstleft", dst0);
		imshow("Dstright", dst1);

		//imshow("connected component analysis", labels0);

		//cout << labels.size() << endl;
		//cout << "Total Connected Components Detected: " << nccomps0 << endl;

		int c = waitKey(4);
	}
}