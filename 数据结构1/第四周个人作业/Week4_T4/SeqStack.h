#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__

#include<iostream> 
#include "Assistance.h"
using namespace std;

template<class ElemType>
class SeqStack
{
protected:
	int top1, top2;
	int maxSize;
	int* a;			//将两个顺序栈存放在同一个数组的头端和尾端 
public:
	SeqStack(int size = DEFAULT_SIZE);  //构造函数
	bool IsEmpty1() const;				//判断是否为空
	bool IsEmpty2() const;
	void Clear();
	Status Push(ElemType t, const ElemType d);			//入栈
	Status Pop(const ElemType& t, ElemType d);				//出栈 
	void ShowTop(); 						//显示堆区最上面的元素 
	void Print() const;
};

template<class ElemType>
SeqStack<ElemType>::SeqStack(int size)
{
	maxSize = size;
	a = new int[size];
	top1 = 0;
	top2 = size - 1;
}

template<class ElemType>
bool SeqStack<ElemType>::IsEmpty1() const
{
	if (top1 == 0) 
		return true;
	return false;
}

template<class ElemType>
bool SeqStack<ElemType>::IsEmpty2() const
{
	if (top2 == maxSize - 1) 
		return true;
	return false;
}

template<class ElemType>
void SeqStack<ElemType>::Clear()
{
	top1 = 0;
	top2 = maxSize - 1;
}

//Push方法用于向栈中添加元素，根据t的值决定是添加到栈顶还是栈底
template<class ElemType>
Status SeqStack<ElemType>::Push(ElemType t, const ElemType d)
//t是一个标识符，用于决定是向栈顶添加（t=0）还是向栈底方向添加（t=1）
//d是要添加到栈中的元素
{
	if (top1 > top2) cout << "Stack is full!" << endl;
	// 如果t为0，表示向栈顶添加元素。
	if (t == 0)
	{
		a[top1] = d;		// 将元素d添加到top1指向的位置
		top1++;				// 更新top1，指向下一个空位置
	}
	else if (t == 1)
	{
		a[top2] = d;		// 将元素d添加到top2指向的位置
		top2--;				// 更新top2，指向下一个“空”位置
	}
	return SUCCESS;
}

// Pop方法用于从栈中弹出元素，根据t的值决定是从栈顶还是栈底（以倒序方式理解）弹出
template<class ElemType>
Status SeqStack<ElemType>::Pop(const ElemType& t, ElemType d)
//t是一个标识符，用于决定是从栈顶（t=0）还是栈底方向（t=1）弹出元素
//d是用于接收弹出的元素值
{
	// 如果t为0，表示从栈顶弹出元素。
	if (t == 0)
	{
		if (!IsEmpty1())
		{
			d = a[top1];	// 将栈顶元素赋值给d
			top1--;			// 更新top1，指向新的栈顶
		}
	}

	// 如果t为1，表示从栈底方向弹出元素
	if (t == 1)
	{
		if (!IsEmpty2())
		{
			d = a[top2];
			top2++;
		}
	}
	return SUCCESS;
}

template<class ElemType>
void SeqStack<ElemType>::ShowTop()
{
	cout << "Stack1的栈顶元素为:" << a[top1 - 1] << endl;
	cout << "Stack2的栈顶元素为:" << a[top2 + 1] << endl;
}

template<class ElemType>
void SeqStack<ElemType>::Print() const
{
	cout << "Stack1:";
	for (int i = 0; i < top1; i++) cout << a[i] << " ";
	cout << endl << "Stack2:";
	for (int i = maxSize - 1; i > top2; i--) cout << a[i] << " ";
	cout << endl;
}


#endif