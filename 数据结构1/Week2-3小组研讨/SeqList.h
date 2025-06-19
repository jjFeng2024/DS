#pragma once
#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#include <iostream>
#include "Assistance.h"  // 假设 Assistance.h 定义了 Status、RANGE_ERROR、SUCCESS 等
using namespace std;

template <class ElemType>
class SeqList {
protected:
    int length;            // 顺序表当前长度
    int maxLength;         // 顺序表最大容量
    ElemType* elems;       // 存储元素的数组

public:
    SeqList(int size);                             // 构造空表
    SeqList(ElemType v[], int n, int size);        // 根据数组构造顺序表
    virtual ~SeqList();                            // 析构函数
    bool IsEmpty() const;                          // 判断是否为空
    Status DeleteElem(int i, ElemType& e);         // 删除第i个元素
    void Select(int n, int k, int m);              // 面试选择逻辑
};

// 构造空表
template <class ElemType>
SeqList<ElemType>::SeqList(int size) {
    elems = new ElemType[size];
    maxLength = size;
    length = 0;
}

// 根据数组构造顺序表
template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size) {
    elems = new ElemType[size];
    maxLength = size;
    length = n;
    for (int i = 0; i < length; i++) {
        elems[i] = v[i];
    }
}

// 析构函数
template <class ElemType>
SeqList<ElemType>::~SeqList() {
    delete[] elems;
}

// 判断顺序表是否为空
template <class ElemType>
bool SeqList<ElemType>::IsEmpty() const {
    return length == 0;
}

// 删除第i个元素（1-based索引）
template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType& e) {
    if (i < 1 || i > length)
        return RANGE_ERROR;
    e = elems[i - 1];  // 取出被删除的元素
    for (int j = i; j < length; j++) {
        elems[j - 1] = elems[j];  // 后续元素前移
    }
    length--;  // 长度减一
    return SUCCESS;
}

// 简历选择逻辑
template <class ElemType>
void SeqList<ElemType>::Select(int n, int k, int m) {
    int cur_IndexX = 0;        // X的起始位置（数组索引从0开始）
    int cur_IndexY = n - 1;    // Y的起始位置

    while (length > 0) {
        // 计算X的选择位置（逆时针走K步）
        if (cur_IndexY < 0)
        {
            cur_IndexY += length;
        }
        cur_IndexX = (cur_IndexX + k - 1) % length;
        ElemType x_selected = elems[cur_IndexX];

        // 计算Y的选择位置（顺时针走M步）
        cur_IndexY = (cur_IndexY - m + 1 + length) % length;
        ElemType y_selected = elems[cur_IndexY];

        // 输出X和Y的选择结果
        if (cur_IndexX == cur_IndexY) {
            // 如果X和Y选择的是同一份简历
            cout << x_selected;
            DeleteElem(cur_IndexX + 1, x_selected);  // 删除该简历
        }
        else {
            // 如果X和Y选择不同简历
            cout << x_selected << ", " << y_selected;
            if (cur_IndexX < cur_IndexY) {
                DeleteElem(cur_IndexY + 1, y_selected);  // 先删除Y的位置
                DeleteElem(cur_IndexX + 1, x_selected);  // 再删除X的位置
            }
            else {
                DeleteElem(cur_IndexX + 1, x_selected);  // 先删除X的位置
                DeleteElem(cur_IndexY + 1, y_selected);  // 再删除Y的位置
            }
        }

        if (length > 0) {
            cout << "; ";  // 输出分隔符
        }

        // 删除后需要调整X和Y的索引位置，对应题目中的“走到下一份简历前”
        // 若X的当前索引等于Y的当前索引，则将Y的索引往前一位。
        if (cur_IndexX == cur_IndexY) {
            cur_IndexY--;
            goto flag;
        }
        // 若X的当前索引小于Y的当前索引，则将Y的索引往前两位。
        if (cur_IndexX < cur_IndexY) {
            cur_IndexY-=2;
            goto flag;
        }
        // 若X的当前索引大于Y的当前索引，则将X和Y的索引各往前一位。
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
