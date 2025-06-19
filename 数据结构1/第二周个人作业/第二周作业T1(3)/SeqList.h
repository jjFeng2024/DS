#pragma once
#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__
#include <iostream>
using namespace std;

template <class ElemType>
class SeqList
{
protected:
	int length;			//˳���ǰ�ĳ���
	int maxLength;		//˳�����������
	ElemType* elems;	//Ԫ�ش���ռ���׵�ַ

public:
	SeqList(int size = DEFAULT_SIZE);		//����һ���յı�
	SeqList(ElemType v[], int n, int size = DEFAULT_SIZE);	//���캯�����������������й���
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
	elems = new ElemType[size];		//����洢�ռ�
	maxLength = size;				//��˳��������������ó������size
	length = 0;						//����˳���ǰ����Ϊ0
}

template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size)
{
	elems = new ElemType[size];		    // ����洢�ռ�
	maxLength = size;					// ��˳��������������ó������size
	length = n;							// ����˳���ĵ�ǰ����Ϊn 
	for (int i = 0; i < length; i++)	// ������v�е�Ԫ�����δ�ŵ�elems������ 
		elems[i] = v[i];
}

template <class ElemType>
SeqList<ElemType>::~SeqList()
{
	delete[]elems;						// �ͷŴ洢�ռ�
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
	for (int i = 0; i < length / 2; i++)		// ����Ԫ��
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
		e = elems[i - 1];	     // ��e���ر�ɾ��Ԫ�ص�ֵ
		for (int j = i; j < length; j++)// ��ɾ��Ԫ��֮���Ԫ����������һ��λ�� 
			elems[j - 1] = elems[j];
		length--;				// ɾ����˳���Ԫ�ظ�����1
		return SUCCESS;	  
	}
}

/*1.(3) ��һ��˳��������һ������ֵ���ظ����֣������µ�һ������������ֵ��
  ��ɾ�����������ظ���Ԫ�أ�ʹ��������Ԫ�ص�ֵ������ͬ��*/
template<class ElemType>
void SeqList<ElemType>::removeDuplicates()
//���ܣ����������ظ���ֵ���������ݵ�ɾ��
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j < length; j++ )
		//��i����ĵ�һ��Ԫ�ؿ�ʼ������Ѱ���ظ���ֵ��ɾ��
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