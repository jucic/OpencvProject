// swap.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
using namespace std;
//void swap(int &a, int &b) {
//	int t = a;
//	a = b;
//	b = t;
//}
//int main() {
//	int x = 5, y = 10;
//	int a;
//	cout << "x = " << x << " y = " << y << endl;
//	swap(x, y);
//	cout << "x = " << x << " y = " << y << endl;
//	cin >> a;
//	return 0;
//}


//#include <iomanip>
//using namespace std;
//void fiddle(int in1, int &in2)
//{
//	in1 = in1 + 100;
//	in2 = in2 + 100;
//	cout << "The values are ";
//	cout << setw(5) << in1;
//	cout << setw(5) << in2 <<endl;
//}
//int main() {
//	int v1 = 7, v2 = 12;
//	cout << "The values are ";
//	cout << setw(5) << v1;
//	cout << setw(5) << v2 << endl;
//	fiddle(v1, v2);
//	cout << "The values are ";
//	cout << setw(5) << v1;
//	cout << setw(5) << v2 << endl;
//	int a; cin >> a;
//	return 0;
//}


#include <iostream>
#include <iomanip>
using namespace std;
int getVolume(int length, int width = 2, int height = 3);
int main() {
	const int X = 10, Y = 12, Z = 15;
	cout << "Some box data is ";
	cout << getVolume(X, Y, Z) << endl;
	cout << "Some box data is ";
	cout << getVolume(X, Y) << endl;
	cout << "Some box data is ";
	cout << getVolume(X) << endl;
	int a; cin >> a;
	return 0;
}
int getVolume(int length, int width/* = 2 */, int height/* = 3 */)
{
	cout << setw(5) << length << setw(5) << width << setw(5) <<
		height << '\t';
	return length * width * height;
}