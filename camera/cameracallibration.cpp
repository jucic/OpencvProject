#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//void main()	//������ͷ����Ԥ���ĳ���  
//{
//	VideoCapture cap(0);//0,1,2��������ͷ��0����Ĭ������ͷ��Ҳ����д·�����Լ������ϱ������Ƶ  
//	while (true)
//	{
//		Mat frame;//����һ֡  
//		cap >> frame;//��ȡһ֡ͼ�񱣴���frame��  
//					 //�½�һ��û��ͼ��Ĵ���  ����Ϊ123 namedWindow("123",0);  
//		namedWindow("123", 0);//0 ���ڿ��϶�����С 1�����϶�  
//		imshow("123", frame);//��ʾͼ��  123����������    
//		waitKey(30);//waitKey()�����Ĺ����ǲ���ˢ��ͼ��Ƶ��ʱ��Ϊdelay����λΪms��  
//	}
//}

//void main()	//��ȡһ����ɫͼƬת��Ϊ��ɫͼƬ 
//{ 
//	//Mat imggray=imread("123.png",0);//��ȡһ������Ϊ123.png��ͼƬ 0Ϊ�Ҷ�ͼ 1Ϊ��ɫͼ  
//Mat imggray = imread("C:\\eye2.jpg", 1);
//	cvtColor(imggray, imggray, CV_RGB2GRAY);//ת��ͼ�� ��һ��Ϊԭͼ�񣬵ڶ���Ϊ���ͼ�񣬵�����Ϊת��������RGBתΪ��ɫ��  
//	//Mat imggray = Mat::ones(1000, 1000, CV_64FC1);//onesȫ����1
//	imshow("123", imggray);//��ʾͼƬ  
//
//	cout << (int)imggray.at<uchar>(1, 1) << endl;
//	waitKey(0);//waitKey()�����Ĺ����ǲ���ˢ��ͼ��Ƶ��ʱ��Ϊdelay����λΪms��  
//	system("pause");//��ͣ�����ֹ����ִ������Զ��˳�  
//}

//void main()//ʹ��opencv������������
//{
//	//Mat imggray=imread("123.png",0);//��ȡһ������Ϊ123��ͼƬ 0Ϊ�Ҷ�ͼ 1Ϊ��ɫͼ  
//	//Mat image=Mat(5,5,CV_64FC1);//����һ��5��5�е�ͼ�񣨾���  ��������һ����̬�������ò����ı䣩��ά���飩  ������һ������  
//	//Mat image=Mat::zeros(5,5,CV_64FC1);//zerosȫ����0  
//	//Mat image=Mat::ones(5,5,CV_64FC1);//onesȫ����1  
//	Mat image = Mat::eye(100, 100, CV_64FC1);//eye ���Ϊ��λ����  
//	Mat imgone = Mat::ones(100, 100, CV_64FC1);//ones ȫ�����Ϊ1  
//	Mat sum = image + imgone;//��������  ����ֱ��+ - * /   ���  
//	cout << sum << endl;//ֱ���������  
//	imshow("123", sum);//��ʾͼƬ  
//	//cout<<image.at<double>(0,0);  
//	//cout<<image<<endl;  
//	system("pause");//��ͣ�����ֹ�����Զ��˳�  
//}

//void main()
//{
//	Mat image = Mat::eye(5, 5, CV_64FC1);//eye ��λ����  
//	image.t();//t ת�þ��� (�˴���һ��ѷ�����)  
//	cout << image << endl;//ֱ���������  
//	system("pause");//��ͣ�����ֹ�����Զ��˳�  
//}

void main()//дһ��ͼ����� �ֶ���  
{
	VideoCapture cap(0);
	namedWindow("123", 0);
	while (true)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, frame, CV_RGB2GRAY);
		cout << "row��" << frame.rows << "cols��" << frame.cols << endl;//����Լ�����ͷ����ȡ���к���  
		Mat dimg = Mat(frame.rows, frame.cols - 2, CV_8UC1);//////����һ��ͼ��  
		for (int i = 0; i<frame.rows; i++)//��ѭ��  
		{
			for (int j = 1; j<frame.cols - 1; j++)//��ѭ��  
			{
				dimg.at<uchar>(i, j - 1) = frame.at<uchar>(i, j - 1) - frame.at<uchar>(i, j + 1);//���½���ͼ������ӱ任���ͼ��  
			}
		}
		imshow("123", dimg);
		waitKey(10);
	}
}