#include <iostream>
#include "Assistance.h"
#include "LinkList.h"
#include "Node.h"

int main()
{
	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
	LinkList<int> DL(a, 10);
	cout << "ԭ����Ϊ��";
	DL.Print();
	cout << endl;
	DL.reverseList();
	cout << "��ת�������Ϊ��";
	DL.Print();
}