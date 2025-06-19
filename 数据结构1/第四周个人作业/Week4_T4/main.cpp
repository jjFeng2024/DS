#include "SeqStack.h"

int main()
{
	SeqStack<int> S(8);		//创建栈 
	S.Push(0, 1);
	S.Push(0, 2);
	S.Push(0, 3);
	S.Push(0, 4);
	S.Push(1, 5);
	S.Push(1, 6);
	S.Push(1, 7);
	S.Push(1, 8);
	S.Print();				//打印原先的栈
	S.ShowTop();			//输出原先两个栈的栈顶元素
	
	cout << "删去Stack1的栈顶元素后的栈为：" << endl;
	S.Pop(0, 0);
	S.Print();
	
	cout << "删去Stack2的栈顶元素后的栈为：" << endl;
	S.Pop(1, 0);
	S.Print();
	return 0;
}