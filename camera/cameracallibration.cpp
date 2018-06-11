#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//void main()	//打开摄像头进行预览的程序  
//{
//	VideoCapture cap(0);//0,1,2代表摄像头，0代表默认摄像头，也可以写路径，自己电脑上保存的视频  
//	while (true)
//	{
//		Mat frame;//创建一帧  
//		cap >> frame;//读取一帧图像保存在frame里  
//					 //新建一个没有图像的窗口  名称为123 namedWindow("123",0);  
//		namedWindow("123", 0);//0 窗口可拖动调大小 1不可拖动  
//		imshow("123", frame);//显示图像  123代表窗口名称    
//		waitKey(30);//waitKey()函数的功能是不断刷新图像，频率时间为delay，单位为ms。  
//	}
//}

//void main()	//读取一个彩色图片转换为灰色图片 
//{ 
//	//Mat imggray=imread("123.png",0);//读取一个名称为123.png的图片 0为灰度图 1为彩色图  
//Mat imggray = imread("C:\\eye2.jpg", 1);
//	cvtColor(imggray, imggray, CV_RGB2GRAY);//转换图像 第一个为原图像，第二个为输出图像，第三个为转换方法（RGB转为灰色）  
//	//Mat imggray = Mat::ones(1000, 1000, CV_64FC1);//ones全部置1
//	imshow("123", imggray);//显示图片  
//
//	cout << (int)imggray.at<uchar>(1, 1) << endl;
//	waitKey(0);//waitKey()函数的功能是不断刷新图像，频率时间为delay，单位为ms。  
//	system("pause");//暂停程序防止程序执行完毕自动退出  
//}

//void main()//使用opencv函数操作矩阵
//{
//	//Mat imggray=imread("123.png",0);//读取一个名称为123的图片 0为灰度图 1为彩色图  
//	//Mat image=Mat(5,5,CV_64FC1);//创建一个5行5列的图像（矩阵）  （创建了一个动态（可以用参数改变）二维数组）  创建了一个矩阵  
//	//Mat image=Mat::zeros(5,5,CV_64FC1);//zeros全部置0  
//	//Mat image=Mat::ones(5,5,CV_64FC1);//ones全部置1  
//	Mat image = Mat::eye(100, 100, CV_64FC1);//eye 填充为单位矩阵  
//	Mat imgone = Mat::ones(100, 100, CV_64FC1);//ones 全部填充为1  
//	Mat sum = image + imgone;//矩阵的相加  可以直接+ - * /   输出  
//	cout << sum << endl;//直接输出矩阵  
//	imshow("123", sum);//显示图片  
//	//cout<<image.at<double>(0,0);  
//	//cout<<image<<endl;  
//	system("pause");//暂停程序防止程序自动退出  
//}

//void main()
//{
//	Mat image = Mat::eye(5, 5, CV_64FC1);//eye 单位矩阵  
//	image.t();//t 转置矩阵 (此处有一大堆方法用)  
//	cout << image << endl;//直接输出矩阵  
//	system("pause");//暂停程序防止程序自动退出  
//}

void main()//写一个图像的求导 手动求导  
{
	VideoCapture cap(0);
	namedWindow("123", 0);
	while (true)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, frame, CV_RGB2GRAY);
		cout << "row行" << frame.rows << "cols列" << frame.cols << endl;//输出自己摄像头所读取的行和列  
		Mat dimg = Mat(frame.rows, frame.cols - 2, CV_8UC1);//////创建一个图像  
		for (int i = 0; i<frame.rows; i++)//行循环  
		{
			for (int j = 1; j<frame.cols - 1; j++)//列循环  
			{
				dimg.at<uchar>(i, j - 1) = frame.at<uchar>(i, j - 1) - frame.at<uchar>(i, j + 1);//像新建的图像中添加变换后的图像  
			}
		}
		imshow("123", dimg);
		waitKey(10);
	}
}