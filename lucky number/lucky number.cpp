// lucky number.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include <stdio.h>
#include<iostream>
#include <time.h>

using namespace std;

int main()
{
	int a;
	int number = 0;
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		number = rand() % 52 + 1;
		cout << number << endl;
	}
   // cout << "Congratulations to the number " <<number<<" player"<<endl;
	cout << "Thank u for ur support" << endl;
	cin >>a;
    return 0;
}

