#include "SeqStack.h"	// ѭ��������
#include "Assistance.h"

void test1()
{
	SeqStack<int> ar;	//�������ջ
	int x, d, n, No=1;	//d��ʾ�����Ŀ�공���ţ�No��ʾ��ǰ����������ǰ��ĳ����ţ���ʼֵΪ 1

	cout << "�����복������" << endl;
	cin >> n;
    cout << "������" << n << "�ڳ���ĳ�վ˳��" << endl;
	
    for (int i = 1; i <= n ; i++)
    {
        //һ������n�����ݣ���ʾĿ�공��ı��
        cin >> d;
        while (ar.Top(x) == SUCCESS && x == d) 
        {
           //���������ջ���Ƿ���Ԫ�أ�����в��Һ�����ĳ�������ȣ���ֱ�ӳ�ջ
           cout << "��" << x << "�ų���Ӹ����������������ұ�" << endl;
           ar.Pop(x);
        }
        if (No <= d) 
        {
           while (No <= n && No < d) 
           {
              //����ı�Ŵ��ڵ�ǰ������ϵ�һ�������Ӧ�ı�ţ���No�ų�����ջ
              cout << "��" << No << "�ų�����������߽��븨�����" << endl;
              ar.Push(No++);
           }
           if (No == d) 
           {
              //����ı��ǡ�õ���������ϵ�һ����Ӧ�ı�ţ���ֱ�����
              cout << "��" << No << "�ų�����������߽���������ұ�" << endl;
              No++;
           }
        }
        else
        {
            // �����ǰĿ����С�����������Ҳ��ڸ�������У������ʧ��
            if (ar.Top(x) != SUCCESS || x != d)
            {
                cout << "����ʧ�ܣ��޷������� " << d << " ���ų�վ��" << endl;
                return;
            }
        }
    }
    if (ar.IsEmpty())
        cout << "�������!" << endl;
    else
        cout << "�����޷����!" << endl;
    system("PAUSE");
    return;
}

void test2()
{
    SeqStack<int> ar;
    int x, d, n, No[100], j = 0;    //ʹ��j����˳������No[j]
    cout << "�����복������";
    cin >> n;
   
    for (j = 0; j < n; j++)
        No[j] = j + 1;              //NoԤ���ұ��������˳��
    cout << "������" << n << "�ڳ����˳��";
    
    for (int i = 1; i <= n; i++)
    {
        //һ������n�����ݣ��Ա�ʾ������
        cin >> d;
        while (ar.Top(x) == SUCCESS && x == No[j])
        {
            //���������ջ���Ƿ���Ԫ�أ�����в��ҺͶ�Ӧ˳�����еĳ�������ȣ����ջ
            cout << "��" << x << "�ų���Ӹ����������������ұߡ�" << endl;
            ar.Pop(x);
            j++;
        }
        if (No[j] <= d)
        {
            while (No[j] <= n && No[j] < d)
            {
                //����ı�Ŵ��ڵ�ǰ������ϵ�һ�������Ӧ�ı�ţ���d�ų�����ջ
                cout << "��" << d << "�ų�����������߽��븨�����" << endl;
                ar.Push(d);
                break;
            }
            if (No[j] == d)
            {
                //����ı�ŵ��ڵ�ǰ������ϵ�һ�������Ӧ�ı�ţ���ֱ�����
                cout << "��" << d << "�ų�����������߽���������ұ�" << endl;
                j++;
            }
        }
        if (i == n && !ar.IsEmpty())
        {
            //��ֹ�������һλ�������ϵ�ջ������ʣ�೵������
            while (ar.Top(x) == SUCCESS && x == No[j])
            {
                cout << "��" << x << "�ų���Ӹ����������������ұ�" << endl;
                ar.Pop(x);
                j++;
            }
        }
    }
    if (ar.IsEmpty())
        cout << "�������!" << endl;
    else
        cout << "�����޷����!" << endl;
    system("PAUSE");
    return;
}

int main()
{
    //test1();
    test2();
    return 0;
}
