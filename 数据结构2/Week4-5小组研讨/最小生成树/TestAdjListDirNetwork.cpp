#include "Assistance.h"					// 辅助软件包
#include "AdjListUnDirNetwork.h"		// 邻接表有向网

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D'};
		int m[4][4] = {         //方案1（有环）
			{infity, 2, 3, 4},
			{2, infity, 5, 6},
			{3, 5, infity, 7},
			{4, 6, 7, infity}
		};
	//	int m[4][4] = {
	//{infity, 2, 3, infity},  // 方案2（无环）
	//{2, infity, infity, infity},  
	//{3, infity, infity, infity},  
	//{infity, infity, infity, infity}  
	//	};
		char c = 'a', e, e1, e2;
		int n = 4, v, v1, v2, w;

		AdjListUnDirNetwork<char, int> net(vexs, n);

		for (int v = 0; v < n; v++)
			for (int u = 0; u < n; u++)
				if (m[v][u] != infity) net.InsertArc(v, u, m[v][u]);

	    while (c != '0')	{
            cout << endl << "1. 无向网清空.";
            cout << endl << "2. 显示无向网.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
            cout << endl << "9. 设置指定边的权.";
			cout << endl << "a. 判断图中是否有环";
			cout << endl << "b. 破圈法生成最小生成树";
		    cout << endl << "0. 退出";
		    cout << endl << "选择功能(0~10):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
			        net.Clear();
				    break;
			    case '2':
                    if (net.IsEmpty())
                        cout << "该无向网为空。" << endl;
                    else 
			            net.Display();
				    break;
			    case '3':
			        cout << endl << "输入顶点序号（无向网的顶点序号从0开始）:";
			        cin >> v;
		            net.GetElem(v, e);
		            cout << "序号为" << v << "的顶点为" << e;
			        break;
			    case '4':
			        cout << endl << "输入顶点序号（无向网的顶点序号从0开始）:";
			        cin >> v;
			        cout << endl << "输入" << v <<"号顶点的值:";
			        cin >> e;
		            net.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "输入被删除顶点的值:";
			        cin >> e;
		            net.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "输入插入顶点的值:";
			        cin >> e;
		            net.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "输入与被删除边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.InsertArc(v1, v2, w);
			        break;
			    case '9':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.SetWeight(v1, v2, w);
			        break;
				case'a':
					if (net.HasCircle())
						cout << "图中有环" << endl;
					else
						cout << "图中无环" << endl;
					break;
				case'b':
					net.GenerateAndPrintMSTByCycleBreaking();
					break;
       	      }
         }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}
	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

