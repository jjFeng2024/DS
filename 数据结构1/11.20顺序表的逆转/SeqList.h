#pragma once
#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__
#include <iostream>
using namespace std;

template <class ElemType>
class SeqList
{
protected:
	int length;			//顺序表当前的长度
	int maxLength;		//顺序表最大的容量
	ElemType* elems;	//元素储存空间的首地址

public:
	SeqList(int size = DEFAULT_SIZE);		//构造一个空的表
	SeqList(ElemType v[], int n, int size = DEFAULT_SIZE);	//构造函数，根据数组来进行构造
	virtual ~SeqList();
	void Clear();
	void Traverse(void (*Visit)(const ElemType&)) const;
	void Reverse();
	void Print();
};

template <class ElemType>
SeqList<ElemType>::SeqList(int size)
{
	elems = new ElemType[size];		//申请存储空间
	maxLength = size;				//将顺序表的最大容量设置成数组的size
	length = 0;						//设置顺序表当前长度为0
}

template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size)
{
	elems = new ElemType[size];		    // 申请存储空间
	maxLength = size;					// 将顺序表的最大容量设置成数组的size
	length = n;							// 设置顺序表的当前长度为n 
	for (int i = 0; i < length; i++)	// 将数组v中的元素依次存放到elems数组中 
		elems[i] = v[i];
}

template <class ElemType>
SeqList<ElemType>::~SeqList()
{
	delete[]elems;						// 释放存储空间
}

template <class ElemType>
void SeqList<ElemType>::Clear()
{
	length = 0;
}

template <class ElemType>
void SeqList<ElemType>::Traverse(void (*visit)(const ElemType&)) const
{
	for (int i = 0; i < length; i++)
		(*visit)(elems[i]);
}

template<class ElemType>
void SeqList<ElemType>::Reverse()
{
	ElemType temp;
	for (int i = 0; i < length / 2; i++)		// 交换元素
	{
		temp = elems[i];
		elems[i] = elems[length - 1 - i];
		elems[length - 1 - i] = temp;
	}
}

template<class ElemType>
void SeqList<ElemType>::Print()
{
	for (int i = 0; i < length; i++)
	{
		cout << elems[i] << " " ;
	}
	cout << endl;
}


#endif