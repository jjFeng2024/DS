#include <iostream>
#include "Assistance.h"
#include "LinkList.h"
#include "Node.h"
using namespace std;


int main()
{
	int a[]={ 1,0,9 };
	int n = sizeof(a) / sizeof(a[0]);
	LinkList<int> L(a,n);
	cout << "ԭ����Ϊ��";
	L.Print();
	L.InsertElem(3,8);
	L.InsertElem(5,4);
	cout << "�����Ԫ��Ϊ��8��4" << endl << "�����λ��Ϊ��0ǰ��9ǰ" << endl;
	L.Print();
	cout << "ɾ����3�����������Ϊ��";
	int e;
	L.DeleteElem(3,e);
	L.Print();
	return 0;
}