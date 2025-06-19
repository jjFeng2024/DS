#include "Assistance.h"   // 辅助软件包
#include <iostream>
#include "SeqList.h"
using namespace std;

int main()
{
    cout << "请输入3个数，分别对应题中的N,K,M" << endl;
    int n, k, m;
    cin >> n >> k >> m;

    int* resumes = new int[n];  // 动态分配数组存储简历编号
    for (int i = 0; i < n; i++) 
    {
        resumes[i] = i + 1;
    }

    SeqList<int> list(resumes, n, n);
    list.Select(n, k, m);

    delete[] resumes;  // 释放动态分配的内存
    return 0;
}
