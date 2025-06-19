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
	Status DeleteElem(int i, ElemType& e);
	void removeDuplicates();
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
		cout << elems[i] << " ";
	}
	cout << endl;
}

template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType& e)
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else {
		e = elems[i - 1];	     // 用e返回被删除元素的值
		for (int j = i; j < length; j++)// 被删除元素之后的元素依次左移一个位置 
			elems[j - 1] = elems[j];
		length--;				// 删除后顺序表元素个数减1
		return SUCCESS;	  
	}
}

/*1.(3) 在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，
  并删除其他所有重复的元素，使表中所有元素的值均不相同。*/
template<class ElemType>
void SeqList<ElemType>::removeDuplicates()
//功能：遍历查找重复的值并进行数据的删除
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++ )
		//从i后面的第一个元素开始遍历，寻找重复的值并删除
		{
			if (elems[j] == elems[i])
			{
				int deleted_num;
				DeleteElem(j, deleted_num);
			}
		}
	}
}
#endif