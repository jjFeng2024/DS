#include "SeqList.h"	// 顺序表类
#include <iostream>
using namespace std;

int main()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	SeqList<int> S1(a,10,10);
	S1.Print();		//初始的顺序表
	S1.Reverse();
	S1.Print();		//逆转后的顺序表

	return 0;
}
