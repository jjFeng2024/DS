#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"					// 结点类

template <class ElemType>
class LinkList {
protected:
    Node<ElemType>* head;  // 头结点指针
    int length;            // 单链表长度

public:
    LinkList();                              // 无参构造函数
    LinkList(ElemType v[], int n);           // 有参构造函数
    virtual ~LinkList();                     // 析构函数
    void reverseList();                      // 逆转线性表
    void Print() const;                      // 打印链表
};

// 无参构造函数
template<class ElemType>
LinkList<ElemType>::LinkList() {
    head = new Node<ElemType>();  // 创建空的头结点
    assert(head != nullptr);      // 检查头结点是否创建成功
    head->next = nullptr;
    length = 0;
}

// 有参构造函数
template<class ElemType>
LinkList<ElemType>::LinkList(ElemType v[], int n) {
    head = new Node<ElemType>();  // 创建头结点
    assert(head != nullptr);      // 检查头结点是否创建成功
    Node<ElemType>* p = head;

    for (int i = 0; i < n; ++i) {
        p->next = new Node<ElemType>(v[i]);  // 创建新节点并连接
        assert(p->next != nullptr);          // 检查新节点是否创建成功
        p = p->next;
    }
    length = n;
}

// 析构函数
template<class ElemType>
LinkList<ElemType>::~LinkList() {
    Node<ElemType>* p = head;
    while (p != nullptr) {
        Node<ElemType>* temp = p->next;
        delete p;
        p = temp;
    }
}

// 逆转线性表
template<class ElemType>
void LinkList<ElemType>::reverseList() 
{
    if (head == NULL || head->next == NULL) return;
    Node<ElemType>* prev = nullptr;     //逆置节点的前一个节点
    Node<ElemType>* cur = head->next;   //当前节点
    Node<ElemType>* next = nullptr;     // 记录下一个节点

    while (cur != nullptr) 
    {
        next = cur->next;  // 保存下一个节点
        cur->next = prev;  // 反转当前节点的指针
        prev = cur;        // 移动prev到当前节点
        cur = next;        // cur移动到下一个节点
    }

    head->next = prev;  // 更新头节点的next指向新的第一个节点
}

// 打印链表
template<class ElemType>
void LinkList<ElemType>::Print() const {
    Node<ElemType>* p = head->next;  // 从头结点之后开始遍历
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}


#endif