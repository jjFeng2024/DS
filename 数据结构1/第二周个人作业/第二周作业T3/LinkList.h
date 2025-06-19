#pragma once
#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"					// �����

template <class ElemType>
class LinkList {
protected:
    Node<ElemType>* head;  // ͷ���ָ��
    int length;            // ��������

public:
    LinkList();                              // �޲ι��캯��
    LinkList(ElemType v[], int n);           // �вι��캯��
    virtual ~LinkList();                     // ��������
    void reverseList();                      // ��ת���Ա�
    void Print() const;                      // ��ӡ����
};

// �޲ι��캯��
template<class ElemType>
LinkList<ElemType>::LinkList() {
    head = new Node<ElemType>();  // �����յ�ͷ���
    assert(head != nullptr);      // ���ͷ����Ƿ񴴽��ɹ�
    head->next = nullptr;
    length = 0;
}

// �вι��캯��
template<class ElemType>
LinkList<ElemType>::LinkList(ElemType v[], int n) {
    head = new Node<ElemType>();  // ����ͷ���
    assert(head != nullptr);      // ���ͷ����Ƿ񴴽��ɹ�
    Node<ElemType>* p = head;

    for (int i = 0; i < n; ++i) {
        p->next = new Node<ElemType>(v[i]);  // �����½ڵ㲢����
        assert(p->next != nullptr);          // ����½ڵ��Ƿ񴴽��ɹ�
        p = p->next;
    }
    length = n;
}

// ��������
template<class ElemType>
LinkList<ElemType>::~LinkList() {
    Node<ElemType>* p = head;
    while (p != nullptr) {
        Node<ElemType>* temp = p->next;
        delete p;
        p = temp;
    }
}

// ��ת���Ա�
template<class ElemType>
void LinkList<ElemType>::reverseList() 
{
    if (head == NULL || head->next == NULL) return;
    Node<ElemType>* prev = nullptr;     //���ýڵ��ǰһ���ڵ�
    Node<ElemType>* cur = head->next;   //��ǰ�ڵ�
    Node<ElemType>* next = nullptr;     // ��¼��һ���ڵ�

    while (cur != nullptr) 
    {
        next = cur->next;  // ������һ���ڵ�
        cur->next = prev;  // ��ת��ǰ�ڵ��ָ��
        prev = cur;        // �ƶ�prev����ǰ�ڵ�
        cur = next;        // cur�ƶ�����һ���ڵ�
    }

    head->next = prev;  // ����ͷ�ڵ��nextָ���µĵ�һ���ڵ�
}

// ��ӡ����
template<class ElemType>
void LinkList<ElemType>::Print() const {
    Node<ElemType>* p = head->next;  // ��ͷ���֮��ʼ����
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}


#endif