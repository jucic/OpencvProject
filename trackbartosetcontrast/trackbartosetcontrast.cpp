#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
using namespace cv;
using namespace std;

Mat srcimg,dstimg;
int contrast=80;
int brightness=80;

static void ContrastAndBright(int, void*)
{
	//三个for循环，执行运算 new_image(i,j) =a*image(i,j) + b  
	for (int y = 0; y < srcimg.rows; y++)
	{
		for (int x = 0; x < srcimg.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				dstimg.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((contrast*0.01)*(srcimg.at<Vec3b>(y, x)[c]) + brightness);
			}
		}
	}

	imshow("processed picture", dstimg);

}

int main()
{
	system("color5F");

	srcimg = imread("C:\\eye2.jpg");
	if (srcimg.empty()) { printf("shit\n"); return -1;}

	dstimg = Mat::zeros(srcimg.size(), srcimg.type());

	namedWindow("original picture", 1);
	imshow("original picture", srcimg);

	namedWindow("processed picture", 1);
	createTrackbar("contrast", "processed picture", &contrast, 300, ContrastAndBright);
	createTrackbar("brightness", "processed picture", &brightness, 200, ContrastAndBright);

	ContrastAndBright(contrast, 0);//应该是更新当前trackbar的值
	ContrastAndBright(brightness, 0);

	cout << endl << "\t嗯。好了，请调整滚动条观察图像效果~\n\n"
		<< "\t按下“q”键时，程序退出~!\n"
		<< "\n\n\t\t\t\tby浅墨";

	//按下“q”键时，程序退出  
	while (char(waitKey(1)) != 'q') {}
	return 0;
}