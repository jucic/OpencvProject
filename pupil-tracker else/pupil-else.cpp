#include "algo.h"
#include<iostream>
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture camera0(0);
	camera0.set(CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
	camera0.set(CAP_PROP_FRAME_WIDTH, 640);
	camera0.set(CAP_PROP_FRAME_HEIGHT, 480);

	while (true)
	{
		Mat frame0,grey;
		camera0 >> frame0;

		if (frame0.empty())
		{
			cout << "no image" << endl;
			continue;
		}

		int64 t = getTickCount();
		cvtColor(frame0, grey, COLOR_BGR2GRAY);
		RotatedRect pupil = ELSE::run(grey);
		t = getTickCount() - t;
		printf("Time elapsed: %fms\n", t * 1000 / getTickFrequency());

		circle(grey, pupil.center,3,Scalar(255,255,255),3,8,0);

		Point2f vertices[4];
		pupil.points(vertices);
		for (int i = 0; i < 4; i++)
			line(grey, vertices[i], vertices[(i + 1) % 4], Scalar(255, 255, 255));

		Rect brect = pupil.boundingRect();
		rectangle(grey, brect, Scalar(255, 0, 0));

		ellipse(grey, pupil, Scalar(255, 255, 255));

		//rotatedRectangleIntersection(grey, pupil, Scalar(255, 255, 255),);

		imshow("grey", grey);
		waitKey(30);
	}
}
