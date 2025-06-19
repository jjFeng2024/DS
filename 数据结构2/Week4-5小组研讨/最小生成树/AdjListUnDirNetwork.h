#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "AdjListUnDirNetworkArc.h"			// 网络邻接表的边结点类
#include "AdjListUnDirNetworkVex.h"			// 网络邻接表的顶点结点类
#include "Assistance.h"                    //辅助头文件
#include <algorithm>

// 有向网的邻接表类
template <class ElemType, class WeightType>
class AdjListUnDirNetwork
{
protected:
// 邻接表的数据成员:
	int vexNum, vexMaxNum, arcNum;					// 顶点数目、允许的顶点最大数目和边数
	AdjListNetWorkVex<ElemType, WeightType> *vexTable;	// 顶点表
	mutable Status *tag;					        // 标志数组				
	WeightType infinity;	                       // 无穷大的值 
	bool hasCircle;                                //判断是否有环
	int* colour;                                  //动态分配访问标记数组（0=未访问, 1=访问中, 2=已访问）
public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListUnDirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 以数组es[]为顶点数据,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,
        // infinit表示无穷大,边数为0构造有向网
	AdjListUnDirNetwork(int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 构造允许的顶点最大数目为vertexMaxNum,infinit表示无穷大,边数为0的有向网
	~AdjListUnDirNetwork();						 // 析构函数
	void Clear();			                     // 清空有向网			 
	bool IsEmpty();                              // 判断有向网是否为空 
	int GetOrder(ElemType &d) const;             // 求顶点的序号	
	Status GetElem(int v, ElemType &d) const;    // 求顶点的元素值	
	Status SetElem(int v, const ElemType &d);    // 设置顶点的元素值
	WeightType GetInfinity() const;				 // 取无穷大的值			 
	int GetVexNum() const;						 // 求有向网的顶点个数			 
	int GetArcNum() const;						 // 求有向网的边数个数			 
	int FirstAdjVex(int v) const;				 // 求有向网中顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		 // 求有向网中顶点v1的相对于v2的下一个邻接点			 
	void InsertVex(const ElemType &d);			 // 插入元素值为d的顶点		 
	void InsertArc(int v1, int v2, WeightType w);// 插入从顶点为v1到v2、权为w的边			 
	void DeleteVex(const ElemType &d);			 // 删除元素值为d的顶点			 
	void DeleteArc(int v1, int v2);			     // 删除从顶点为v1到v2的边			 
	WeightType GetWeight(int v1, int v2) const;	 // 求从顶点为v1到v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);// 设置从顶点为v1到v2的边的权值
	Status GetTag(int v) const;				     // 求顶点v的标志		 
	void SetTag(int v, Status tag) const;	     // 设置顶点v的标志为tag	
	bool HasCircle()const;                       //DFS判断是否有环
	bool IsConnected() const;                          //判断是否连通 防止生成树影响连通性
	void GenerateAndPrintMSTByCycleBreaking();  //破圈法生成最小生成树
	AdjListUnDirNetwork(const AdjListUnDirNetwork<ElemType, WeightType> &copy);	// 复制构造函数
	AdjListUnDirNetwork<ElemType, WeightType> &operator =
		(const AdjListUnDirNetwork<ElemType, WeightType> &copy); // 重载赋值运算符 
    void Display();	// 显示有向网邻接表 
};

// 有向网的邻接表类的实现部分
template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(ElemType es[],
       int vertexNum, int vertexMaxNum, WeightType infinit)
// 操作结果：构造顶点数据为es[],顶点数为numVex,顶点个数为vertexNum,infinit表示无穷大,边数为0的有向网
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
    	throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	arcNum = 0;
	infinity = infinit;
	
	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
 
	for (int v = 0; v < vexNum; v++)  {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstarc = NULL;
	}
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(int vertexMaxNum, WeightType infinit)
// 操作结果：构造顶点最大数目为vertexMaxNum,infinit表示无穷大的空有向网
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infinit;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::~AdjListUnDirNetwork()
// 操作结果：释放邻接表有向网所占用空间
{
    Clear();                                // 释放边结点
	delete []tag;							// 释放标志
	delete []vexTable;						// 释放邻接表
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::Clear()
// 操作结果：释放所有的边结点，并把有向网的顶点数和边数设置为0.			 
{
	AdjListNetworkArc<WeightType> *p;
	for (int v = 0; v < vexNum; v++)	{	// 释放边结点
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
			vexTable[v].firstarc = p->nextarc;
			delete p;
			p = vexTable[v].firstarc;
        }	
	}
    vexNum = 0;
	arcNum = 0;	
}

template <class ElemType, class WeightType>
bool AdjListUnDirNetwork<ElemType, WeightType>::IsEmpty()
// 操作结果：如果有向网为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetOrder(ElemType &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时返回-1. 
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
           break;
           
	if (v < 0 || v >= vexNum)
		return -1;	// 顶点d不存在,返回-1
	else
		return v;	// 顶点d不存在,返回它的序号 
}	

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
//	通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// 元素不存在
	else	{
		d = vexTable[v].data;		// 将顶点v的元素值赋给d
		return ENTRY_FOUND;			// 元素存在
	}
}	

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// 位置错
	else	{
		vexTable[v].data = d;		// 顶点元素
		return SUCCESS;				// 成功
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUnDirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大的值 
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetArcNum() const
// 操作结果：返回边数个数
{
	return arcNum;
}		 

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常

	if (vexTable[v].firstarc == NULL)
	   return -1;              // 不存在邻接点
	else
	   return vexTable[v].firstarc->adjVex;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	AdjListNetworkArc<WeightType> *p;
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常
	
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2)
	    p = p->nextarc;

	if (p == NULL || p->nextarc == NULL)
		return -1;                   // 不存在下一个邻接点
	else
		return p->nextarc->adjVex;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::InsertVex(const ElemType &d)
// 操作结果：在顶点表的表尾插入元素值为d的顶点。			 
{
	if (vexNum == vexMaxNum)
       throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

	vexTable[vexNum].data = d;
	vexTable[vexNum].firstarc = NULL;
	tag[vexNum] = UNVISITED;
    vexNum++;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");// 抛出异常
	if (w == infinity)
       throw Error("w不能为无空大!");// 抛出异常

	AdjListNetworkArc<WeightType> *p, *q;
	p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new AdjListNetworkArc<WeightType>(v2, w, p);
	arcNum++;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &d)
// 操作结果：删除元素值为d的顶点			 
{
    int v;
    AdjListNetworkArc<WeightType> *p, *q;
    for (v = 0; v < vexNum; v++)
       if	(vexTable[v].data == d)
           break;
	if (v == vexNum)
       throw Error("图中不存在要删除的顶点!");	// 抛出异常

    for (int u = 0; u < vexNum; u++)           // 删除到达d的弧 
       if (u != v) 
          DeleteArc(u, v); 
          
	p = vexTable[v].firstarc;                  // 删除从d出发的弧 
	while (p != NULL) {
        vexTable[v].firstarc = p->nextarc;
        delete p;    
	    p = vexTable[v].firstarc;
		arcNum--;
	}

    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = NULL;
    tag[v] = tag[vexNum];

    for (int u = 0; u < vexNum; u++)         
       if (u != v) {
	      p = vexTable[u].firstarc;
	      while (p != NULL) {
             if (p->adjVex == vexNum)
                p->adjVex = v;
             p = p->nextarc;
          }
       }   
}



template <class ElemType, class WeightType>
bool AdjListUnDirNetwork<ElemType, WeightType>::HasCircle()const {
	if (vexNum == 0) return false;

	// 1. 动态分配访问标记数组（0=未访问, 1=访问中, 2=已访问）
	int* color = new int[vexNum]();
	bool hasCircle = false;

	// 2. 定义递归函数（直接嵌套在HasCycle内）
	class DFS {
	public:
		DFS(int* color, bool& hasCircle, const AdjListUnDirNetwork<ElemType, WeightType>* graph)
			: color(color), hasCircle(hasCircle), graph(graph) {}

		void run(int u, int parent) {
			color[u] = 1; // 标记为"访问中"

			// 遍历u的所有邻接边
			for (AdjListNetworkArc<WeightType>* p = graph->vexTable[u].firstarc; p != NULL; p = p->nextarc) {
				int v = p->adjVex;

				// 情况1：发现回边且不是父节点 → 存在环
				if (color[v] == 1 && v != parent) {
					hasCircle = true;
					return;
				}
				// 情况2：遇到未访问顶点 → 递归处理
				else if (color[v] == 0) {
					run(v, u);
					if (hasCircle) return;
				}
			}

			color[u] = 2; // 标记为"已访问"
		}

	private:
		int* color;
		bool& hasCircle;
		const AdjListUnDirNetwork<ElemType, WeightType>* graph;
	};

	// 3. 执行DFS
	DFS dfs(color, hasCircle, this);
	for (int v = 0; v < vexNum; ++v) {
		if (color[v] == 0) {
			dfs.run(v, -1); // -1表示无父节点
			if (hasCircle) break;
		}
	}

	delete[] color; // 释放内存
	return hasCircle;
}
template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
       Error("v1不能等于v2!");		// 抛出异常

	AdjListNetworkArc<WeightType> *p;
	AdjListNetworkArc<WeightType>* q=NULL;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) {
        q = p;
        p = p->nextarc;
    }
    if (p != NULL) {
	    if (vexTable[v1].firstarc == p)
            vexTable[v1].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;    
		arcNum--;
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUnDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常

	AdjListNetworkArc<WeightType> *p;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) 
       p = p->nextarc;
    if (p != NULL)
	   return p->weight;			// 返回权值
	else
	   return infinity;				// 返回权值为infinity，表示边不存在
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");        // 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	    // 抛出异常
	if (v1 == v2)
       throw Error("v1不能等于v2!");    // 抛出异常
	if (w == infinity)
       throw Error("w不能为无空大!");   // 抛出异常

	AdjListNetworkArc<WeightType> *p;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2)
       p = p->nextarc;
    if (p != NULL)
	   p->weight = w;		            // 修改权值
}


template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::GenerateAndPrintMSTByCycleBreaking() {
	if (vexNum <= 1) {
        std::cout << "【提示】顶点数≤1，无需生成最小生成树。" << std::endl;
        return;
    }

    // --- 1. 统计边数 ---
    int edgeCount = 0;
    for (int u = 0; u < vexNum; ++u) {
        for (AdjListNetworkArc<WeightType>* p = vexTable[u].firstarc; p != nullptr; p = p->nextarc) {
            if (u < p->adjVex) edgeCount++;
        }
    }

    // --- 2. 动态分配边指针数组 ---
    AdjListNetworkArc<WeightType>** edges = new AdjListNetworkArc<WeightType>*[edgeCount];

    // --- 3. 填充边指针（按权重降序）---
    int index = 0;
    for (int u = 0; u < vexNum; ++u) {
        for (AdjListNetworkArc<WeightType>* p = vexTable[u].firstarc; p != nullptr; p = p->nextarc) {
            if (u < p->adjVex) edges[index++] = p;
        }
    }

    // --- 4. 降序排序（复用operator<）---
    std::sort(edges, edges + edgeCount, [](const auto& a, const auto& b) {
        return a->weight > b->weight;
    });

    // --- 5. 破圈主循环（关键修复）---
    for (int i = 0; i < edgeCount && arcNum > vexNum - 1; ++i) {
        int v = edges[i]->adjVex;
        int u = -1;
        // 查找边的起点u（实际项目建议优化此步骤）
        for (int k = 0; k < vexNum; ++k) {
            for (AdjListNetworkArc<WeightType>* p = vexTable[k].firstarc; p != nullptr; p = p->nextarc) {
                if (p == edges[i]) {
                    u = k;
                    break;
                }
            }
            if (u != -1) break;
        }
        if (u == -1) continue;

        // 临时删除边并检查连通性
        WeightType w = edges[i]->weight;
        DeleteArc(u, v);
        DeleteArc(v, u);
        arcNum--;

        if (!IsConnected()) { // 需实现连通性检查
            // 如果删除后不连通，则恢复该边
            InsertArc(u, v, w);
            InsertArc(v, u, w);
            arcNum++;
        }
    }

    // --- 6. 打印结果 ---
    std::cout << "\n=== 最小生成树结果 ===" << std::endl;
    if (arcNum == vexNum - 1) {
        std::cout << "边数: " << arcNum << "/" << vexNum - 1 << "（满足树条件）\n";
        std::cout << "边列表（顶点1-顶点2 : 权重）:\n";
        for (int u = 0; u < vexNum; ++u) {
            for (AdjListNetworkArc<WeightType>* p = vexTable[u].firstarc; p != nullptr; p = p->nextarc) {
                if (u < p->adjVex) {
                    std::cout << u << "-" << p->adjVex << " : " << p->weight << std::endl;
                }
            }
        }
    } else {
        std::cout << "【警告】破圈法实现有误，请检查代码！" << std::endl;
    }

    delete[] edges;
}

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
bool AdjListUnDirNetwork<ElemType, WeightType>:: IsConnected() const {
	if (vexNum == 0) return true; // 空图视为连通

	// 1. 初始化访问标记数组
	bool* visited = new bool[vexNum](); // 默认全false
	int visitedCount = 0;

	// 2. 递归DFS函数（Lambda表达式）
	auto dfs = [&](int u, auto&& self) -> void {
		visited[u] = true;
		visitedCount++;
		for (auto* p = vexTable[u].firstarc; p != nullptr; p = p->nextarc) {
			int v = p->adjVex;
			if (!visited[v]) {
				self(v, self); // 递归访问邻接点
			}
		}
		};

	// 3. 从顶点0开始遍历
	dfs(0, dfs);

	// 4. 检查是否访问所有顶点
	bool connected = (visitedCount == vexNum);
	delete[] visited;
	return connected;
}
template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(const AdjListUnDirNetwork<ElemType, WeightType> &copy)
// 操作结果：由有向网的邻接矩阵copy构造新有向网的邻接矩阵copy——复制构造函数
{
	AdjListNetworkArc<WeightType> *p, *q;
	infinity =copy.infinity;
	vexNum = copy.vexNum;
	vexMaxNum = copy.vexMaxNum;	
	arcNum = copy.arcNum;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	for (int v = 0; v < vexNum; v++)	{
		tag[v] = copy.tag[v];
		vexTable[v].data = copy.vexTable[v].data;
		vexTable[v].firstarc = NULL;
		p = copy.vexTable[v].firstarc;
		while (p != NULL) 
           if (vexTable[v].firstarc == NULL) {
              vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
              q = vexTable[v].firstarc;
              p = p->nextarc;
           }
           else {   
              q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
              q = q->nextarc;
              p = p->nextarc;
           }   
	}
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType> &AdjListUnDirNetwork<ElemType, WeightType>::operator =(const AdjListUnDirNetwork<ElemType, WeightType> &copy)
// 操作结果：将有向网的邻接矩阵copy赋值给当前有向网的邻接矩阵——赋值语句重载
{
	if (&copy != this)
	{
        Clear();                                    // 释放当前有向网边结点
	    delete []tag;								// 释放当前有向网标志数组 
	    delete []vexTable;							// 释放当前有向网顶点表 

	    AdjListNetworkArc<WeightType> *p, *q;
	    infinity =copy.infinity;
	    vexNum = copy.vexNum;
	    vexMaxNum = copy.vexMaxNum;	
	    arcNum = copy.arcNum;

	    tag = new Status[vexMaxNum];
	    vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	    for (int v = 0; v < vexNum; v++)	{
		   tag[v] = copy.tag[v];
		   vexTable[v].data = copy.vexTable[v].data;
		   vexTable[v].firstarc = NULL;
		   p = copy.vexTable[v].firstarc;
		   while (p != NULL) 
               if (vexTable[v].firstarc == NULL) {
                  vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
                  q = vexTable[v].firstarc;
                  p = p->nextarc;
               }
               else {   
                  q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
                  q = q->nextarc;
                  p = p->nextarc;
               }   
	   }
    }
	return *this;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::Display()
// 操作结果: 显示邻接矩阵有向网
{
	AdjListNetworkArc<WeightType> *p;
    cout << "有向网共有" << vexNum << "个顶点，" << arcNum << "条边。" << endl; 
	for (int v = 0; v < vexNum; v++)	{	// 显示第v个邻接链表
		cout << v << ":\t" << vexTable[v].data;				// 显示顶点号
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
        	cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextarc; 
		}
		cout << endl; 
	}
}

#endif
