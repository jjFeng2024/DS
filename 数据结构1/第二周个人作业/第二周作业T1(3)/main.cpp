/*��һ��˳��������һ������ֵ���ظ����֣������µ�һ������������ֵ��
  ��ɾ�����������ظ���Ԫ�أ�ʹ��������Ԫ�ص�ֵ������ͬ��*/

#include "Assistance.h"		// ���������
#include "SeqList.h"	// ˳�����
#include <iostream>
using namespace std;

int main()
{
	int a[]{ 0,1,1,2,3,4,4,5,5,6,7,7,8,9,9};
	SeqList<int> S1(a, 15, 15);
	
	cout << "ԭ˳���Ϊ��";
	S1.Print();
	cout << endl;

	S1.removeDuplicates();
	cout << "ɾ�����˳���Ϊ��";
	S1.Print();
	return 0;
}


