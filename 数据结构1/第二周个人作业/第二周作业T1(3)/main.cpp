/*在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，
  并删除其他所有重复的元素，使表中所有元素的值均不相同。*/

#include "Assistance.h"		// 辅助软件包
#include "SeqList.h"	// 顺序表类
#include <iostream>
using namespace std;

int main()
{
	int a[]{ 0,1,1,2,3,4,4,5,5,6,7,7,8,9,9};
	SeqList<int> S1(a, 15, 15);
	
	cout << "原顺序表为：";
	S1.Print();
	cout << endl;

	S1.removeDuplicates();
	cout << "删除后的顺序表为：";
	S1.Print();
	return 0;
}


