#include "SeqList.h"	// ˳�����
#include <iostream>
using namespace std;

int main()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	SeqList<int> S1(a,10,10);
	S1.Print();		//��ʼ��˳���
	S1.Reverse();
	S1.Print();		//��ת���˳���

	return 0;
}
