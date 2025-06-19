#pragma once
#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#include <iostream>
#include "Assistance.h"  // ���� Assistance.h ������ Status��RANGE_ERROR��SUCCESS ��
using namespace std;

template <class ElemType>
class SeqList {
protected:
    int length;            // ˳���ǰ����
    int maxLength;         // ˳����������
    ElemType* elems;       // �洢Ԫ�ص�����

public:
    SeqList(int size);                             // ����ձ�
    SeqList(ElemType v[], int n, int size);        // �������鹹��˳���
    virtual ~SeqList();                            // ��������
    bool IsEmpty() const;                          // �ж��Ƿ�Ϊ��
    Status DeleteElem(int i, ElemType& e);         // ɾ����i��Ԫ��
    void Select(int n, int k, int m);              // ����ѡ���߼�
};

// ����ձ�
template <class ElemType>
SeqList<ElemType>::SeqList(int size) {
    elems = new ElemType[size];
    maxLength = size;
    length = 0;
}

// �������鹹��˳���
template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size) {
    elems = new ElemType[size];
    maxLength = size;
    length = n;
    for (int i = 0; i < length; i++) {
        elems[i] = v[i];
    }
}

// ��������
template <class ElemType>
SeqList<ElemType>::~SeqList() {
    delete[] elems;
}

// �ж�˳����Ƿ�Ϊ��
template <class ElemType>
bool SeqList<ElemType>::IsEmpty() const {
    return length == 0;
}

// ɾ����i��Ԫ�أ�1-based������
template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType& e) {
    if (i < 1 || i > length)
        return RANGE_ERROR;
    e = elems[i - 1];  // ȡ����ɾ����Ԫ��
    for (int j = i; j < length; j++) {
        elems[j - 1] = elems[j];  // ����Ԫ��ǰ��
    }
    length--;  // ���ȼ�һ
    return SUCCESS;
}

// ����ѡ���߼�
template <class ElemType>
void SeqList<ElemType>::Select(int n, int k, int m) {
    int cur_IndexX = 0;        // X����ʼλ�ã�����������0��ʼ��
    int cur_IndexY = n - 1;    // Y����ʼλ��

    while (length > 0) {
        // ����X��ѡ��λ�ã���ʱ����K����
        if (cur_IndexY < 0)
        {
            cur_IndexY += length;
        }
        cur_IndexX = (cur_IndexX + k - 1) % length;
        ElemType x_selected = elems[cur_IndexX];

        // ����Y��ѡ��λ�ã�˳ʱ����M����
        cur_IndexY = (cur_IndexY - m + 1 + length) % length;
        ElemType y_selected = elems[cur_IndexY];

        // ���X��Y��ѡ����
        if (cur_IndexX == cur_IndexY) {
            // ���X��Yѡ�����ͬһ�ݼ���
            cout << x_selected;
            DeleteElem(cur_IndexX + 1, x_selected);  // ɾ���ü���
        }
        else {
            // ���X��Yѡ��ͬ����
            cout << x_selected << ", " << y_selected;
            if (cur_IndexX < cur_IndexY) {
                DeleteElem(cur_IndexY + 1, y_selected);  // ��ɾ��Y��λ��
                DeleteElem(cur_IndexX + 1, x_selected);  // ��ɾ��X��λ��
            }
            else {
                DeleteElem(cur_IndexX + 1, x_selected);  // ��ɾ��X��λ��
                DeleteElem(cur_IndexY + 1, y_selected);  // ��ɾ��Y��λ��
            }
        }

        if (length > 0) {
            cout << "; ";  // ����ָ���
        }

        // ɾ������Ҫ����X��Y������λ�ã���Ӧ��Ŀ�еġ��ߵ���һ�ݼ���ǰ��
        // ��X�ĵ�ǰ��������Y�ĵ�ǰ��������Y��������ǰһλ��
        if (cur_IndexX == cur_IndexY) {
            cur_IndexY--;
            goto flag;
        }
        // ��X�ĵ�ǰ����С��Y�ĵ�ǰ��������Y��������ǰ��λ��
        if (cur_IndexX < cur_IndexY) {
            cur_IndexY-=2;
            goto flag;
        }
        // ��X�ĵ�ǰ��������Y�ĵ�ǰ��������X��Y����������ǰһλ��
        if (cur_IndexX > cur_IndexY) {
            cur_IndexX--;
            cur_IndexY--;
            goto flag;
        }
    flag:;
        
    }
    cout << endl;
}

#endif
