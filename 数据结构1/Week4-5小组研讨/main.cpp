#include "SeqStack.h"	// 循环队列类
#include "Assistance.h"

void test1()
{
	SeqStack<int> ar;	//辅助轨道栈
	int x, d, n, No=1;	//d表示输入的目标车厢编号；No表示当前主轨道左边最前面的车厢编号，初始值为 1

	cout << "请输入车厢数：" << endl;
	cin >> n;
    cout << "请输入" << n << "节车厢的出站顺序：" << endl;
	
    for (int i = 1; i <= n ; i++)
    {
        //一共输入n个数据，表示目标车厢的编号
        cin >> d;
        while (ar.Top(x) == SUCCESS && x == d) 
        {
           //看辅助轨道栈内是否有元素，如果有并且和输入的车厢编号相等，则直接出栈
           cout << "第" << x << "号车厢从辅助轨道进入主轨道右边" << endl;
           ar.Pop(x);
        }
        if (No <= d) 
        {
           while (No <= n && No < d) 
           {
              //输入的编号大于当前主轨道上第一个车厢对应的编号，则No号车厢入栈
              cout << "第" << No << "号车厢从主轨道左边进入辅助轨道" << endl;
              ar.Push(No++);
           }
           if (No == d) 
           {
              //输入的编号恰好等于主轨道上第一个对应的编号，则直接输出
              cout << "第" << No << "号车厢从主轨道左边进入主轨道右边" << endl;
              No++;
           }
        }
        else
        {
            // 如果当前目标编号小于主轨道编号且不在辅助轨道中，则调度失败
            if (ar.Top(x) != SUCCESS || x != d)
            {
                cout << "调度失败：无法将车厢 " << d << " 安排出站！" << endl;
                return;
            }
        }
    }
    if (ar.IsEmpty())
        cout << "调度完成!" << endl;
    else
        cout << "调度无法完成!" << endl;
    system("PAUSE");
    return;
}

void test2()
{
    SeqStack<int> ar;
    int x, d, n, No[100], j = 0;    //使用j遍历顺序数组No[j]
    cout << "请输入车厢数：";
    cin >> n;
   
    for (j = 0; j < n; j++)
        No[j] = j + 1;              //No预设右边主轨道的顺序
    cout << "请输入" << n << "节车厢的顺序：";
    
    for (int i = 1; i <= n; i++)
    {
        //一共输入n个数据，以表示车厢编号
        cin >> d;
        while (ar.Top(x) == SUCCESS && x == No[j])
        {
            //看辅助轨道栈内是否有元素，如果有并且和对应顺序排列的车厢编号相等，则出栈
            cout << "第" << x << "号车厢从辅助轨道进入主轨道右边。" << endl;
            ar.Pop(x);
            j++;
        }
        if (No[j] <= d)
        {
            while (No[j] <= n && No[j] < d)
            {
                //输入的编号大于当前主轨道上第一个车厢对应的编号，则d号车厢入栈
                cout << "第" << d << "号车厢从主轨道左边进入辅助轨道" << endl;
                ar.Push(d);
                break;
            }
            if (No[j] == d)
            {
                //输入的编号等于当前主轨道上第一个车厢对应的编号，则直接输出
                cout << "第" << d << "号车厢从主轨道左边进入主轨道右边" << endl;
                j++;
            }
        }
        if (i == n && !ar.IsEmpty())
        {
            //防止出现最后一位已输出完毕但栈内仍有剩余车厢的情况
            while (ar.Top(x) == SUCCESS && x == No[j])
            {
                cout << "第" << x << "号车厢从辅助轨道进入主轨道右边" << endl;
                ar.Pop(x);
                j++;
            }
        }
    }
    if (ar.IsEmpty())
        cout << "调度完成!" << endl;
    else
        cout << "调度无法完成!" << endl;
    system("PAUSE");
    return;
}

int main()
{
    //test1();
    test2();
    return 0;
}
