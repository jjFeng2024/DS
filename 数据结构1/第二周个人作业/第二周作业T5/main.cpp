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
	cout << "原链表为：";
	L.Print();
	L.InsertElem(3,8);
	L.InsertElem(5,4);
	cout << "插入的元素为：8，4" << endl << "插入的位置为：0前，9前" << endl;
	L.Print();
	cout << "删除第3个结点后的链表为：";
	int e;
	L.DeleteElem(3,e);
	L.Print();
	return 0;
}