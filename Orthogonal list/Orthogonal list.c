#include<stdio.h>
#include<stdlib.h>

#define MAXSIZENUM 10 // 定义顶点最大数量

typedef char vextype; // 定义顶点数据类型
typedef int arcValuetype; // 定义边的权值数据类型

// 边结点的定义
typedef struct EdgeNode
{
	int tailvex; // 边的尾部顶点索引
	int headvex; // 边的头部顶点索引
	struct EdgeNode* hlink; // 指向同一头部顶点的下一条边
	struct EdgeNode* tlink; // 指向同一尾部顶点的下一条边
	arcValuetype arcValue; // 边的权值
} EdgeNode;

// 顶点结构体的定义
typedef struct
{
	vextype data; // 顶点数据
	EdgeNode* firstin; // 指向以该顶点为头部的第一条边
	EdgeNode* firstout; // 指向以该顶点为尾部的第一条边
} vexNode, AdjList[MAXSIZENUM]; // 邻接表类型定义

// 图结构体的定义
typedef struct
{
	AdjList vertices; // 顶点数组
	int vnum, arcnum; // 顶点数量和边数量
} OrthList;

// 初始化图的函数
void IniOrthList(OrthList* orl)
{
	if (orl == NULL)
		return;
	orl->vnum = 0;
	orl->arcnum = 0;
	for (int i = 0; i < MAXSIZENUM; i++)
	{
		orl->vertices[i].firstin = NULL;
		orl->vertices[i].firstout = NULL;
		orl->vertices[i].data = '#'; // 初始化顶点数据
	}
}

// 获取顶点在顶点集合中的索引
int Getindex(OrthList* orl, vextype x) {
	for (int i = 0; i < MAXSIZENUM; i++) {
		if (orl->vertices[i].data == x) {
			return i; // 返回顶点在顶点集合中的索引
		}
	}
	printf("不存在该顶点\n");
	return -1; // 顶点不存在，返回-1
}

// 向图中插入顶点
void InsertVertex(OrthList* orl, vextype x)
{
	if (orl == NULL)
	{
		return;
	}
	for (int i = 0; i < MAXSIZENUM; i++)
	{
		if (orl->vertices[i].data == '#')
		{
			orl->vertices[i].data = x; // 插入顶点数据
			orl->vnum++; // 顶点数量加1
			return;
		}
	}
}

// 向图中添加边
void AddEdge(OrthList* orl, vextype x, vextype y)
{
	int t = Getindex(orl, x); // 获取边的尾部顶点索引
	int e = Getindex(orl, y); // 获取边的头部顶点索引
	if (orl == NULL || t < 0 || e < 0)
	{
		return;
	}
	EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode)); // 创建新的边结点
	if (p == NULL)
	{
		perror("AddEdge");
		return;
	}
	p->headvex = e; // 设置边的头部顶点索引
	p->tailvex = t; // 设置边的尾部顶点索引

	// 将边结点插入头部顶点的边链表中
	p->hlink = orl->vertices[e].firstin;
	orl->vertices[e].firstin = p;

	// 将边结点插入尾部顶点的边链表中
	p->tlink = orl->vertices[t].firstout;
	orl->vertices[t].firstout = p;
	orl->arcnum++; // 边数量加1
}

// 从图中删除边
void RemoveEdge(OrthList* orl, vextype x, vextype y)
{
	int t = Getindex(orl, x); // 获取边的尾部顶点索引
	int e = Getindex(orl, y); // 获取边的头部顶点索引
	if (orl == NULL || t < 0 || e < 0)
	{
		return;
	}
	// 修改与改边节点弧尾相同的节点
	EdgeNode* p = orl->vertices[t].firstout;
	EdgeNode* pre = NULL;
	while (p && (p->headvex != e || p->tailvex != t))
	{
		pre = p;
		p = p->tlink;
	}
	if (p == NULL)
	{
		return;
	}
	if (p && pre)
	{
		pre->tlink = p->tlink;
	}
	if (p && pre == NULL)
	{
		orl->vertices[t].firstout = p->tlink;
	}

	// 修改与改边节点弧头相同的节点
	p = orl->vertices[e].firstin;
	pre = NULL;
	while (p && (p->headvex != e || p->tailvex != t))
	{
		pre = p;
		p = p->hlink;
	}
	if (p && pre)
	{
		pre->hlink = p->hlink;
	}
	if (p && pre == NULL)
	{
		orl->vertices[e].firstin = p->hlink;
	}
	free(p); // 释放内存
	p = NULL;
	orl->arcnum--; // 边数量减1
}

// 从图中删除顶点
void Deletevertex(OrthList* orl, vextype x)
{
	int t = Getindex(orl, x);
	if (orl == NULL || t < 0)
	{
		return;
	}
	EdgeNode* p = orl->vertices[t].firstout;
	while (p)
	{
		vextype y = orl->vertices[p->headvex].data;
		p = p->tlink;
		RemoveEdge(orl, x, y);
	}
	p = orl->vertices[t].firstin;
	while (p)
	{
		vextype y = orl->vertices[p->tailvex].data;
		p = p->hlink;
		RemoveEdge(orl, y, x);
	}
	orl->vnum--;
	orl->vertices[t].data = '#';
}

// 主函数
int main()
{
	OrthList orl;
	IniOrthList(&orl); // 初始化图

	// 向图中插入顶点
	InsertVertex(&orl, 'A');
	InsertVertex(&orl, 'B');
	InsertVertex(&orl, 'C');
	InsertVertex(&orl, 'D');

	// 向图中添加边
	AddEdge(&orl, 'A', 'B');
	AddEdge(&orl, 'A', 'C');
	AddEdge(&orl, 'C', 'D');
	AddEdge(&orl, 'C', 'A');
	AddEdge(&orl, 'D', 'C');
	AddEdge(&orl, 'D', 'B');
	AddEdge(&orl, 'D', 'A');

	// 删除顶点'A'
	Deletevertex(&orl, 'A');

	return 1;
}
