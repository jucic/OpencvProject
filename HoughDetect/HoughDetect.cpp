//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//      ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

//-----------------------------------�������ռ��������֡�---------------------------------------  
//      ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;

//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  

//int main()
//{
//	//��1������ԭʼͼ��Mat��������     
//	Mat srcImage = imread("C:\\eye2.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
//	Mat midImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���  
//
//	if (srcImage.empty()) return -1;
//
//	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ  
//	Canny(srcImage, midImage, 50, 200, 3);//����һ��canny��Ե���  
//	cvtColor(midImage, dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ  
//
//											  //��3�����л����߱任  
//	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������  
//	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
//
//	if (lines.size() == 0) return -1;
//	//��4��������ͼ�л��Ƴ�ÿ���߶�  
//	for (int i = 0; i < lines.size(); i++)
//	{
//		Vec4i l = lines[i];
//		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
//	}
//
//	//��5����ʾԭʼͼ    
//	imshow("��ԭʼͼ��", srcImage);
//
//	//��6����Ե�����ͼ   
//	imshow("����Ե�����ͼ��", midImage);
//
//	//��7����ʾЧ��ͼ    
//	imshow("��Ч��ͼ��", dstImage);
//
//	waitKey(0);
//
//	return 0;
//}

//int main()
//{
//	//��1������ԭʼͼ��Mat��������     
//	Mat srcImage = imread("C:\\eye2.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
//	Mat midImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���  
//
//						   //��2�����б�Ե����ת��Ϊ�Ҷ�ͼ  
//	Canny(srcImage, midImage, 50, 200, 3);//����һ��canny��Ե���  
//	cvtColor(midImage, dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ  
//
//	//��3�����л����߱任  
//	vector<Vec2f> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������  
//	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
//
//	if (lines.size() == 0) return -1;
//
//	//��4��������ͼ�л��Ƴ�ÿ���߶�  
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		float rho = lines[i][0], theta = lines[i][1];
//		Point pt1, pt2;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
//	}
//
//	//��5����ʾԭʼͼ    
//	imshow("��ԭʼͼ��", srcImage);
//
//	//��6����Ե�����ͼ   
//	imshow("����Ե�����ͼ��", midImage);
//
//	//��7����ʾЧ��ͼ    
//	imshow("��Ч��ͼ��", dstImage);
//
//	waitKey(0);
//
//	return 0;
//}


int main()
{
	//��1������ԭʼͼ��Mat��������     
	Mat srcImage = imread("C:\\eye2.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ  
	Mat midImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���  

	//��2����ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);

	//��3��תΪ�Ҷ�ͼ������ͼ��ƽ��  
	cvtColor(srcImage, midImage, CV_BGR2GRAY);//ת����Ե�����ͼΪ�Ҷ�ͼ  
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
	
	//��4�����л���Բ�任  
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
	cout << circles.size() << endl;

	//��5��������ͼ�л��Ƴ�Բ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		cout << radius << endl;
		//����Բ��  
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����  
		circle(srcImage, center, radius, Scalar(255, 0, 0), 3, 8, 0);
	}

	//��6����ʾЧ��ͼ
	//namedWindow("��Ч��ͼ��", CV_WINDOW_AUTOSIZE);
	imshow("��Ч��ͼ��", srcImage);

	waitKey(0);

	return 0;
}

//int main()
//{
//	//��������ͷ
//	VideoCapture capture;
//	capture.open(0);
//
//
//	Mat edges;  //����ת���ĻҶ�ͼ
//	if (!capture.isOpened())
//		return -1;
//	namedWindow("��Ч��ͼ��", CV_WINDOW_NORMAL);
//	while (1)
//	{
//		Mat frame;
//		capture >> frame;
//		if (!frame.data)
//			return -1;
//		cvtColor(frame, edges, CV_BGR2GRAY);
//		//��˹�˲�
//		GaussianBlur(edges, edges, Size(7, 7), 2, 2);
//		vector<Vec3f> circles;
//		//����Բ
//		HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 100);
//		for (size_t i = 0; i < circles.size(); i++)
//		{
//			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//			int radius = cvRound(circles[i][2]);
//			//����Բ��  
//			circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
//			//����Բ����  
//			circle(frame, center, radius, Scalar(155, 50, 255), 3, 8, 0);
//		}
//
//
//		imshow("��Ч��ͼ��", frame);
//
//
//		waitKey(30);
//
//	}
//
//	return 0;
//}