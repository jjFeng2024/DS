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
	int* a;			//������˳��ջ�����ͬһ�������ͷ�˺�β�� 
public:
	SeqStack(int size = DEFAULT_SIZE);  //���캯��
	bool IsEmpty1() const;				//�ж��Ƿ�Ϊ��
	bool IsEmpty2() const;
	void Clear();
	Status Push(ElemType t, const ElemType d);			//��ջ
	Status Pop(const ElemType& t, ElemType d);				//��ջ 
	void ShowTop(); 						//��ʾ�����������Ԫ�� 
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

//Push����������ջ�����Ԫ�أ�����t��ֵ��������ӵ�ջ������ջ��
template<class ElemType>
Status SeqStack<ElemType>::Push(ElemType t, const ElemType d)
//t��һ����ʶ�������ھ�������ջ����ӣ�t=0��������ջ�׷�����ӣ�t=1��
//d��Ҫ��ӵ�ջ�е�Ԫ��
{
	if (top1 > top2) cout << "Stack is full!" << endl;
	// ���tΪ0����ʾ��ջ�����Ԫ�ء�
	if (t == 0)
	{
		a[top1] = d;		// ��Ԫ��d��ӵ�top1ָ���λ��
		top1++;				// ����top1��ָ����һ����λ��
	}
	else if (t == 1)
	{
		a[top2] = d;		// ��Ԫ��d��ӵ�top2ָ���λ��
		top2--;				// ����top2��ָ����һ�����ա�λ��
	}
	return SUCCESS;
}

// Pop�������ڴ�ջ�е���Ԫ�أ�����t��ֵ�����Ǵ�ջ������ջ�ף��Ե���ʽ��⣩����
template<class ElemType>
Status SeqStack<ElemType>::Pop(const ElemType& t, ElemType d)
//t��һ����ʶ�������ھ����Ǵ�ջ����t=0������ջ�׷���t=1������Ԫ��
//d�����ڽ��յ�����Ԫ��ֵ
{
	// ���tΪ0����ʾ��ջ������Ԫ�ء�
	if (t == 0)
	{
		if (!IsEmpty1())
		{
			d = a[top1];	// ��ջ��Ԫ�ظ�ֵ��d
			top1--;			// ����top1��ָ���µ�ջ��
		}
	}

	// ���tΪ1����ʾ��ջ�׷��򵯳�Ԫ��
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
	cout << "Stack1��ջ��Ԫ��Ϊ:" << a[top1 - 1] << endl;
	cout << "Stack2��ջ��Ԫ��Ϊ:" << a[top2 + 1] << endl;
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