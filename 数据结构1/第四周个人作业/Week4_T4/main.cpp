#include "SeqStack.h"

int main()
{
	SeqStack<int> S(8);		//����ջ 
	S.Push(0, 1);
	S.Push(0, 2);
	S.Push(0, 3);
	S.Push(0, 4);
	S.Push(1, 5);
	S.Push(1, 6);
	S.Push(1, 7);
	S.Push(1, 8);
	S.Print();				//��ӡԭ�ȵ�ջ
	S.ShowTop();			//���ԭ������ջ��ջ��Ԫ��
	
	cout << "ɾȥStack1��ջ��Ԫ�غ��ջΪ��" << endl;
	S.Pop(0, 0);
	S.Print();
	
	cout << "ɾȥStack2��ջ��Ԫ�غ��ջΪ��" << endl;
	S.Pop(1, 0);
	S.Print();
	return 0;
}