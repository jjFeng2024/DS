#include "Assistance.h"   // ���������
#include <iostream>
#include "SeqList.h"
using namespace std;

int main()
{
    cout << "������3�������ֱ��Ӧ���е�N,K,M" << endl;
    int n, k, m;
    cin >> n >> k >> m;

    int* resumes = new int[n];  // ��̬��������洢�������
    for (int i = 0; i < n; i++) 
    {
        resumes[i] = i + 1;
    }

    SeqList<int> list(resumes, n, n);
    list.Select(n, k, m);

    delete[] resumes;  // �ͷŶ�̬������ڴ�
    return 0;
}
