#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
int main(int argc, const char** argv)
{
	cv::Mat frame;
	// 可从摄像头输入视频流或直接播放视频文件
	cv::VideoCapture capture(0);
	//    cv::VideoCapture capture("vedio1.avi");
	double fps;
	char string[10];  // 用于存放帧率的字符串
	cv::namedWindow("Camera FPS");
	double t = 0;
	while (1)
	{
		t = (double)cv::getTickCount();
		//cvWaitKey(10);
		if (cv::waitKey(1) == 1) { break; }
		if (capture.isOpened())
		{
			capture >> frame;
			// getTickcount函数：返回从操作系统启动到当前所经过的毫秒数
			// getTickFrequency函数：返回每秒的计时周期数
			// t为该处代码执行所耗的时间,单位为秒,fps为其倒数
			t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
			fps = 1.0 / t;
			sprintf_s(string, "%.2f", fps);      // 帧率保留两位小数
			std::string fpsString("FPS:");
			fpsString += string;                    // 在"FPS:"后加入帧率数值字符串
			printf("fps: %.2f width:%d height:%d fps:%.2f\n", fps, frame.cols, frame.rows, capture.get(CV_CAP_PROP_FPS));
			// 将帧率信息写在输出帧上
			cv::putText(frame, // 图像矩阵
				fpsString,                  // string型文字内容
				cv::Point(5, 20),           // 文字坐标，以左上角为原点
				cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
				0.5, // 字体大小
				cv::Scalar(0, 0, 0));       // 字体颜色
			cv::imshow("Camera FPS", frame);
			
		}
		else
		{
			std::cout << "No Camera Input!" << std::endl;
			break;
		}
	}
}

