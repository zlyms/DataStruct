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

// 获取顶点在顶点集合中的索引
int Getindex(ALGraph* adj, vextype x) {
	for (int i = 0; i < MAXSIZE; i++) {
		if (adj->vertices[i].data == x) {
			return i; // 返回顶点在顶点集合中的索引
		}
	}
	//printf("不存在该顶点\n");
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

// 判断顶点x和顶点y是否有边
int Adjacent(ALGraph* alg, vextype x, vextype y, int b)
{
	int t = Getindex(alg, x);
	int e = Getindex(alg, y);
	if (alg == NULL || t < 0 || e < 0)
	{
		return -1;
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
			return -1;
		}
		p = alg->vertices[e].firstArc;
		while (p && p->adjvex != t)
		{
			p = p->NextArc;
		}
		if (p == NULL)
		{
			return -1;
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
			return -1;
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
	if (b == 0 && Adjacent(alg, x, y, b) >= 0)
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
	else if (b == 1 && Adjacent(alg, x, y, b))
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
		return;
	}
	return p->arcValue;
}
char visited[MAXSIZE] = { 0 };
int JudgeVisted(char visted[],ALGraph*alg) 
{
	for (int i = 0; i < alg->vnum; i++) 
	{
		if (visted[i] == 0) 
		{
			return 1;
		}
	}
	return 0;
}
/*
 * 使用 Prim 算法计算图的最小生成树
 * 参数：
 *   - alg: 指向原图的指针
 *   - minTree: 指向最小生成树的指针
 *   - v: 起始顶点
 * 注意事项：
 *   - 此算法要求图是连通图
 */
void Prim(ALGraph* alg, ALGraph* minTree, vextype v)
{
	int t = Getindex(alg, v); // 获取起始顶点在顶点集合中的索引
	int m = 9999; // 初始化最小权值
	int index = 0; // 初始化最小权值对应的顶点索引
	InsertVertex(minTree, v); // 将起始顶点插入最小生成树
	visited[t] = 1; // 标记起始顶点为已访问
	while (JudgeVisted(visited, alg)) // 当存在未访问的顶点时循环执行
	{
		int flag = 0; // 标志变量，用于判断是否找到合适的边
		int x = 0; // 记录找到合适边的起始顶点索引
		for (int i = 0; i < alg->vnum; i++) // 遍历所有顶点
		{
			if (visited[i] == 1) // 如果顶点已访问
			{
				ArcNode* p = alg->vertices[i].firstArc; // 获取顶点 i 的第一个邻接顶点
				while (p) // 遍历顶点 i 的所有邻接顶点
				{
					if (p->arcValue < m && Adjacent(minTree, alg->vertices[i].data, alg->vertices[p->adjvex].data, 1) == -1 && visited[p->adjvex] == 0) // 如果找到权值更小且未访问过的边
					{
						index = p->adjvex; // 更新最小权值对应的顶点索引
						m = p->arcValue; // 更新最小权值
						flag = 1; // 更新标志变量为找到合适的边
						x = i; // 更新起始顶点索引
					}
					p = p->NextArc; // 继续查找下一个邻接顶点
				}
			}
		}
		if (flag) // 如果找到合适的边
		{
			InsertVertex(minTree, alg->vertices[index].data); // 将对应顶点插入最小生成树
			visited[index] = 1; // 标记该顶点为已访问
			Addedge(minTree, alg->vertices[x].data, alg->vertices[index].data, 1); // 在最小生成树中添加边
			Set_edge_value(minTree, alg->vertices[x].data, alg->vertices[index].data, 1, m); // 设置边的权值
		}
		m = 9999; // 重置最小权值
	}
}
*/

//1.建立表，表结构：边的两个顶点，x，y，权值
//2.对表升序排序
//3.每次从中选择最小的一条边，使用并查集判断是否属于同一集合。或者麻烦一点判断边的两顶点的边是否存在公共顶点
//4.是：取下一条边，否：加入树
void Kruskal(ALGraph*alg,ALGraph*minTree,vextype v)
{

}
int main()
{
	ALGraph alg;
	ALGraph minValueTree;
	IniALGraph(&alg);
	IniALGraph(&minValueTree);
	InsertVertex(&alg, 'A');
	InsertVertex(&alg, 'B');
	InsertVertex(&alg, 'C');
	InsertVertex(&alg, 'D');
	InsertVertex(&alg, 'E');
	InsertVertex(&alg, 'F');
	Addedge(&alg, 'A', 'B', 1);
	Addedge(&alg, 'A', 'C', 1);
	Addedge(&alg, 'A', 'F', 1);
	Addedge(&alg, 'B', 'F', 1);
	Addedge(&alg, 'C', 'F', 1);
	Addedge(&alg, 'B', 'D', 1);
	Addedge(&alg, 'C', 'E', 1);
	Addedge(&alg, 'D', 'F', 1);
	Addedge(&alg, 'E', 'F', 1);
	Addedge(&alg, 'D', 'E', 1);
	Set_edge_value(&alg, 'A', 'B', 1, 6);
	Set_edge_value(&alg, 'A', 'C', 1, 5);
	Set_edge_value(&alg, 'A', 'F', 1, 1);
	Set_edge_value(&alg, 'B', 'F', 1, 5);
	Set_edge_value(&alg, 'C', 'F', 1, 4);
	Set_edge_value(&alg, 'B', 'D', 1, 3);
	Set_edge_value(&alg, 'C', 'E', 1, 2);
	Set_edge_value(&alg, 'D', 'F', 1, 6);
	Set_edge_value(&alg, 'E', 'F', 1, 4);
	Set_edge_value(&alg, 'D', 'E', 1, 6);
	Prim(&alg, &minValueTree, 'A');
	return 0;
}
