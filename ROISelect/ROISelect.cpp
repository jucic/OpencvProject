// ROISelect.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

bool draw;
Mat src;//原始图像  
Mat roi;//ROI图像
Point cursor;//初始坐标   
Rect rect;//标记ROI的矩形框

void onMouse(int event, int x, int y, int flags, void *param)
{
	Mat img = src.clone();
	switch (event)
	{
		//按下鼠标左键
	case CV_EVENT_LBUTTONDOWN:
		//点击鼠标图像时，清除之前ROI图像的显示窗口  
		cvDestroyWindow("ROI");
		//存放起始坐标  
		cursor = Point(x, y);
		//初始化起始矩形框  
		rect = Rect(x, y, 0, 0);
		draw = true;
		break;

		//松开鼠标左键      
	case CV_EVENT_LBUTTONUP:
		if (rect.height > 0 && rect.width > 0)
		{
			//将img中的矩形区域复制给roi，并显示在SignROI窗口 
			roi = img(Rect(rect.x, rect.y, rect.width, rect.height));
			rectangle(img, rect, Scalar(0, 255, 0), 2);
			namedWindow("SignROI");
			imshow("SignROI", img);

			//将画过矩形框的图像用原图像还原  
			src.copyTo(img);
			imshow("SrcImage", img);

			//显示ROI图像
			namedWindow("ROI");
			imshow("ROI", roi);
			waitKey(0);
		}
		draw = false;
		break;

		//移动光标
	case CV_EVENT_MOUSEMOVE:
		if (draw)
		{
			//用MIN得到左上点作为矩形框的起始坐标，如果不加这个，画矩形时只能向一个方向进行  
			rect.x = MIN(x, cursor.x);
			rect.y = MIN(y, cursor.y);
			rect.width = abs(cursor.x - x);
			rect.height = abs(cursor.y - y);
			//防止矩形区域超出图像的范围  
			rect &= Rect(0, 0, src.cols, src.rows);
		}
		break;
	}
}

int main()
{
	src = imread("C:\\eye2.jpg");
	if (src.data == 0)
	{
		cout << "error, the src image is not built!" << endl;
		return -1;
	}
	namedWindow("SrcImage");
	imshow("SrcImage", src);
	setMouseCallback("SrcImage", onMouse, NULL);
	waitKey();
	return 0;
}

