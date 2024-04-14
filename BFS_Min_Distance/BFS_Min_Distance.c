#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10

typedef char vextype;
typedef int Arcvaluetype;

// 边节点结构体
typedef struct ArcNode
{
	int adjvex;             // 相邻顶点的索引
	struct ArcNode* NextArc;// 指向下一个邻接点的指针
	Arcvaluetype arcValue;  // 边的权值
}ArcNode;

// 顶点节点结构体
typedef struct
{
	vextype data;           // 顶点数据
	ArcNode* firstArc;      // 指向第一个邻接点的指针
}vexNode, AdjList[MAXSIZE];

// 图结构体
typedef struct
{
	AdjList vertices;       // 邻接表数组
	int vnum, arcnum;        // 顶点数和边数
}ALGraph;

typedef vextype Elemtype;

typedef struct LNode
{
	Elemtype data;      // 数据域
	struct LNode* next; // 指针域，指向下一个节点
} LNode;

typedef struct
{
	LNode* front; // 队头指针
	LNode* rear;  // 队尾指针
} LQueue;          // 链式队列结构体

void IniLQueue(LQueue* LQ)
{
	LQ->front = NULL; // 初始化队头指针
	LQ->rear = NULL;  // 初始化队尾指针
}

int isempty(LQueue* LQ)
{
	if (LQ->front == NULL) // 如果队头指针为空
	{
		return 1; // 队列为空
	}
	return 0; // 队列非空
}

int EnQueue(LQueue* LQ, Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode)); // 分配新节点的内存空间
	if (p == NULL)
	{
		perror("EnQueue:"); // 输出错误信息
		printf("申请空间失败\n"); // 输出提示信息
		return 0; // 返回失败
	}
	if (LQ->front == NULL) // 如果队列为空
	{
		LQ->front = p; // 新节点成为队头节点
		LQ->rear = p;  // 新节点成为队尾节点
	}
	p->data = e;    // 将元素赋值给新节点的数据域
	p->next = NULL; // 新节点的next指针置空
	LQ->rear->next = p; // 将新节点挂载到队尾节点后
	LQ->rear = p;       // 更新队尾指针为新节点

	return 1; // 返回成功
}

int deQueue(LQueue* LQ, Elemtype* e)
{
	if (isempty(LQ)) // 如果队列为空
	{
		printf("队空\n"); // 输出提示信息
		return 0; // 返回失败
	}
	LNode* p = LQ->front; // 保存队头节点的地址
	*e = p->data;          // 将队头节点的数据赋值给*e
	LQ->front = LQ->front->next; // 更新队头指针为原队头节点的下一个节点
	if (LQ->front == LQ->rear) 
	{
		LQ->front = NULL;
		LQ->rear = NULL;
	}
	free(p);               // 释放原队头节点的内存空间
	p = NULL;              // 将原队头节点置空
	return 1;              // 返回成功
}

int GetElem(LQueue* LQ, Elemtype* e)
{
	if (isempty(LQ)) // 如果队列为空
	{
		printf("队空\n"); // 输出提示信息
		return 0; // 返回失败
	}
	*e = LQ->front->data; // 获取队头节点的数据
	return 1;              // 返回成功
}

//-----------------------------------------------------------------
// 获取顶点在顶点集合中的索引
int Getindex(ALGraph* adj, vextype x) {
	for (int i = 0; i < MAXSIZE; i++) {
		if (adj->vertices[i].data == x) {
			return i; // 返回顶点在顶点集合中的索引
		}
	}
	printf("不存在该顶点\n");
	return -1; // 顶点不存在，返回-1
}

// 初始化图
void IniALGraph(ALGraph* alg)
{
	alg->arcnum = alg->vnum = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		alg->vertices[i].firstArc = NULL;
		alg->vertices[i].data = '#';
	}
}

// 打印顶点x的所有邻居顶点
void Neighbor(ALGraph* alg, vextype x)
{
	int t = Getindex(alg, x);
	if (alg == NULL || t < 0)
	{
		return;
	}
	ArcNode* p = alg->vertices[t].firstArc;
	while (p)
	{
		int f = p->adjvex;
		p = p->NextArc;
		printf("%c-%c\n", x, alg->vertices[f].data);
	}
}

// 判断顶点x和顶点y是否相邻
int Adjacent(ALGraph* alg, vextype x, vextype y, int b)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return 0;
	}
	if (b == 1)
	{
		// 对于无向图，需同时判断x到y和y到x的边是否存在
		ArcNode* p = alg->vertices[t].firstArc;
		while (p && p->adjvex != e)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return 0;
		}
		p = alg->vertices[e].firstArc;
		while (p && p->adjvex != t)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return 0;
		}
	}
	else if (b == 0)
	{
		// 对于有向图，仅需判断x到y的边是否存在
		ArcNode* p = alg->vertices[t].firstArc;
		while (p && p->adjvex != e)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return 0;
		}
	}
	return 1;
}

// 插入顶点
void InsertVertex(ALGraph* alg, vextype x)
{
	if (alg == NULL)
	{
		return;
	}
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (alg->vertices[i].data == '#')
		{
			alg->vertices[i].data = x;
			alg->vnum++;
			return;
		}
	}
}

// 删除顶点
void Deletevertex(ALGraph* alg, vextype x)
{
	if (alg == NULL)
	{
		return;
	}
	int k = Getindex(alg, x);
	ArcNode* pre = NULL;
	while (alg->vertices[k].firstArc)
	{
		int f = alg->vertices[k].firstArc->adjvex;
		ArcNode* p = alg->vertices[f].firstArc;
		while (p != NULL && p->adjvex != k)
		{
			pre = p;
			p = p->NextArc;
		}
		if (p != NULL && pre != NULL)
		{
			pre->NextArc = p->NextArc;
			free(p);
			p = NULL;
		}
		if (p != NULL && pre == NULL)
		{
			alg->vertices[f].firstArc = NULL;
			free(p);
			p = NULL;
		}
		if (alg->vertices[k].firstArc != NULL)
		{
			pre = alg->vertices[k].firstArc;
			alg->vertices[k].firstArc = alg->vertices[k].firstArc->NextArc;
			free(pre);
			pre = NULL;
		}

	}
	alg->vertices[k].data = '#';
	alg->vnum--;
}

// 添加边
void Addedge(ALGraph* alg, vextype x, vextype y, int b)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return;
	}
	if (b == 1)
	{
		// 添加x到y和y到x的边，用于无向图
		ArcNode* ptr = (ArcNode*)malloc(sizeof(ArcNode));

		if (alg->vertices[t].firstArc && ptr)
		{
			ptr->adjvex = e;
			ptr->NextArc = alg->vertices[t].firstArc;
			alg->vertices[t].firstArc = ptr;
		}
		else if (alg->vertices[t].firstArc == NULL && ptr)
		{
			ptr->adjvex = e;
			alg->vertices[t].firstArc = ptr;
			ptr->NextArc = NULL;
		}


		ptr = (ArcNode*)malloc(sizeof(ArcNode));

		if (alg->vertices[e].firstArc && ptr)
		{
			ptr->adjvex = t;
			ptr->NextArc = alg->vertices[e].firstArc;
			alg->vertices[e].firstArc = ptr;
		}
		else if (alg->vertices[e].firstArc == NULL && ptr)
		{
			ptr->adjvex = t;
			alg->vertices[e].firstArc = ptr;
			ptr->NextArc = NULL;
		}
		alg->arcnum++;
	}
	if (b == 0)
	{
		// 添加x到y的边，用于有向图
		ArcNode* ptr = (ArcNode*)malloc(sizeof(ArcNode));

		if (alg->vertices[t].firstArc && ptr)
		{
			ptr->adjvex = e;
			ptr->NextArc = alg->vertices[t].firstArc->NextArc;
			alg->vertices[t].firstArc = ptr;
		}
		else if (alg->vertices[t].firstArc == NULL && ptr)
		{
			alg->vertices[t].firstArc = ptr;
			ptr->NextArc = NULL;
		}
		alg->arcnum++;
	}
}
//删除入边
int RemoveEnEdge(ALGraph* alg, vextype x, vextype y)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return 0;
	}
	ArcNode* pre = NULL;
	ArcNode* p = alg->vertices[e].firstArc;
	while (p && p->adjvex != t)
	{
		p = p->NextArc;
	}
	if (p && pre)
	{
		pre->NextArc = p->NextArc;
		free(p);
		p = NULL;
	}
	else if (p && pre == NULL)
	{
		alg->vertices[e].firstArc = NULL;
		free(p);
	}
	return 1;
}
//删除出边
int RemoveExEdge(ALGraph* alg, vextype x, vextype y)
{
	return RemoveEnEdge(alg, y, x);
}

// 删除边
void RemoveEdge(ALGraph* alg, vextype x, vextype y, int b)
{
	if (b == 1)
	{
		// 对于无向图，需同时删除x到y和y到x的边
		int flag = RemoveEnEdge(alg, x, y);
		RemoveExEdge(alg, x, y);
		if (flag)
		{
			alg->arcnum--;
		}
	}
	else if (b == 0)
	{
		// 对于有向图，仅需删除x到y的边
		int flag = RemoveExEdge(alg, x, y);
		if (flag)
		{
			alg->arcnum--;
		}
	}
}

// 获取顶点x的第一个邻居顶点
int FirstNeighbor(ALGraph* alg, vextype x)
{
	int t = Getindex(alg, x);
	if (alg == NULL || t < 0)
	{
		return -1;
	}
	if (alg->vertices[t].firstArc != NULL)
		return alg->vertices[t].firstArc->adjvex;
}

// 获取顶点y在顶点x之后的下一个邻居顶点
int NextNeighbor(ALGraph* alg, vextype x, vextype y)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return -1;
	}
	ArcNode* p = alg->vertices[t].firstArc;
	while (p && p->adjvex != e)
	{
		p = p->NextArc;
	}
	if (p && p->NextArc)
	{
		return p->NextArc->adjvex;
	}
	else
	{
		return -1;
	}
}

// 设置边的权值
void Set_edge_value(ALGraph* alg, vextype x, vextype y, int b, Arcvaluetype v)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return;
	}
	if (b == 0)
	{
		// 对于有向图，仅需设置x到y的边的权值
		ArcNode* p = alg->vertices[t].firstArc;
		while (p && p->adjvex != e)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return;
		}
		p->arcValue = v;
	}
	else if (b == 1)
	{
		// 对于无向图，需同时设置x到y和y到x的边的权值
		ArcNode* p = alg->vertices[t].firstArc;
		while (p && p->adjvex != e)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return;
		}
		p->arcValue = v;

		p = alg->vertices[e].firstArc;
		while (p && p->adjvex != t)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return;
		}
		p->arcValue = v;
	}
}

// 获取边的权值
int Get_edge_value(ALGraph* alg, vextype x, vextype y)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return 0;
	}
	ArcNode* p = alg->vertices[t].firstArc;
	while (p && p->adjvex != e)
	{
		p = p->NextArc;
	}
	if (p == NULL)
	{
		return 0;
	}
	return p->arcValue;
}
/*
 * 使用广度优先搜索计算从顶点 v 到图中其他顶点的最短距离及最短路径
 * 参数：
 *   - alg: 指向图的指针
 *   - lq: 指向队列的指针，用于辅助遍历
 *   - v: 开始遍历的顶点
 * 注意事项：
 *   - 图中为边权为1，否则无法得到正确的最短距离
 */
void BFS_Min_Distance(ALGraph* alg, LQueue* lq, vextype v)
{
	int t = Getindex(alg, v); // 获取顶点 v 在顶点集合中的索引
	int path[MAXSIZE] = { 0 }; // 记录最短路径的前驱顶点
	int dis[MAXSIZE] = { 0 }; // 记录最短距离
	for (int i = 0; i < MAXSIZE; i++)
	{
		dis[i] = 9999; // 初始化距离为一个较大的值，表示未知距离
		path[i] = -1; // 初始化路径为 -1，表示未知路径
	}
	dis[t] = 0; // 设置起始顶点到自身的距离为 0
	vextype y = v; // 初始化 y 为顶点 v
	vextype x = v; // 初始化 x 为顶点 v
	char visited[MAXSIZE] = { 0 }; // 初始化访问标志数组
	visited[t] = 1; // 将顶点 v 标记为已访问
	EnQueue(lq, v); // 将顶点 v 入队列

	while (isempty(lq) == 0) // 当队列非空时循环执行
	{
		deQueue(lq, &x); // 出队列一个顶点 x
		int u = Getindex(alg, x); // 获取顶点 x 在顶点集合中的索引
		for (int w = FirstNeighbor(alg, x); w >= 0; w = NextNeighbor(alg, x, y)) // 遍历顶点 x 的邻接顶点
		{
			y = alg->vertices[w].data; // 获取邻接顶点的数据
			if (visited[w] == 0) // 如果邻接顶点尚未访问过
			{
				visited[w] = 1; // 标记该顶点为已访问
				dis[w] = dis[u] + 1; // 更新从顶点 v 到顶点 w 的最短距离
				path[w] = u; // 记录从顶点 v 到顶点 w 的最短路径的前驱顶点
				EnQueue(lq, y); // 将该顶点入队列
			}
		}
	}
}


int main()
{
	LQueue LQ;    // 声明链式队列变量
	IniLQueue(&LQ); // 初始化队列
	ALGraph alg;
	IniALGraph(&alg);
	InsertVertex(&alg, 'A');
	InsertVertex(&alg, 'B');
	InsertVertex(&alg, 'C');
	InsertVertex(&alg, 'D');
	InsertVertex(&alg, 'E');
	Addedge(&alg, 'A', 'B', 1);
	Addedge(&alg, 'A', 'C', 1);
	Addedge(&alg, 'A', 'D', 1);
	Addedge(&alg, 'D', 'B', 1);
	Addedge(&alg, 'E', 'C', 1);
	BFS_Min_Distance(&alg, &LQ, 'E');
	return 0; // 返回成功
}
