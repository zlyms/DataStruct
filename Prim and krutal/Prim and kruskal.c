#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10

typedef char vextype;
typedef int Arcvaluetype;

// �߽ڵ�ṹ��
typedef struct ArcNode
{
	int adjvex;             // ���ڶ��������
	struct ArcNode* NextArc;// ָ����һ���ڽӵ��ָ��
	Arcvaluetype arcValue;  // �ߵ�Ȩֵ
}ArcNode;

// ����ڵ�ṹ��
typedef struct
{
	vextype data;           // ��������
	ArcNode* firstArc;      // ָ���һ���ڽӵ��ָ��
}vexNode, AdjList[MAXSIZE];

// ͼ�ṹ��
typedef struct
{
	AdjList vertices;       // �ڽӱ�����
	int vnum, arcnum;        // �������ͱ���
}ALGraph;

// ��ȡ�����ڶ��㼯���е�����
int Getindex(ALGraph* adj, vextype x) {
	for (int i = 0; i < MAXSIZE; i++) {
		if (adj->vertices[i].data == x) {
			return i; // ���ض����ڶ��㼯���е�����
		}
	}
	//printf("�����ڸö���\n");
	return -1; // ���㲻���ڣ�����-1
}

// ��ʼ��ͼ
void IniALGraph(ALGraph* alg)
{
	alg->arcnum = alg->vnum = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		alg->vertices[i].firstArc = NULL;
		alg->vertices[i].data = '#';
	}
}

// ��ӡ����x�������ھӶ���
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

// �ж϶���x�Ͷ���y�Ƿ��б�
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
		// ��������ͼ����ͬʱ�ж�x��y��y��x�ı��Ƿ����
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
		// ��������ͼ�������ж�x��y�ı��Ƿ����
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

// ���붥��
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

// ɾ������
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

// ��ӱ�
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
		// ���x��y��y��x�ıߣ���������ͼ
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
		// ���x��y�ıߣ���������ͼ
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
// ɾ����
void RemoveEdge(ALGraph* alg, vextype x, vextype y, int b)
{
	if (b == 1)
	{
		// ��������ͼ����ͬʱɾ��x��y��y��x�ı�
		int flag = RemoveEnEdge(alg, x, y);
		RemoveExEdge(alg, x, y);
		if (flag)
		{
			alg->arcnum--;
		}
	}
	else if (b == 0)
	{
		// ��������ͼ������ɾ��x��y�ı�
		int flag = RemoveExEdge(alg, x, y);
		if (flag)
		{
			alg->arcnum--;
		}
	}
}

// ��ȡ����x�ĵ�һ���ھӶ���
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

// ��ȡ����y�ڶ���x֮�����һ���ھӶ���
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

// ���ñߵ�Ȩֵ
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
		// ��������ͼ����������x��y�ıߵ�Ȩֵ
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
		// ��������ͼ����ͬʱ����x��y��y��x�ıߵ�Ȩֵ
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

// ��ȡ�ߵ�Ȩֵ
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
 * ʹ�� Prim �㷨����ͼ����С������
 * ������
 *   - alg: ָ��ԭͼ��ָ��
 *   - minTree: ָ����С��������ָ��
 *   - v: ��ʼ����
 * ע�����
 *   - ���㷨Ҫ��ͼ����ͨͼ
 */
void Prim(ALGraph* alg, ALGraph* minTree, vextype v)
{
	int t = Getindex(alg, v); // ��ȡ��ʼ�����ڶ��㼯���е�����
	int m = 9999; // ��ʼ����СȨֵ
	int index = 0; // ��ʼ����СȨֵ��Ӧ�Ķ�������
	InsertVertex(minTree, v); // ����ʼ���������С������
	visited[t] = 1; // �����ʼ����Ϊ�ѷ���
	while (JudgeVisted(visited, alg)) // ������δ���ʵĶ���ʱѭ��ִ��
	{
		int flag = 0; // ��־�����������ж��Ƿ��ҵ����ʵı�
		int x = 0; // ��¼�ҵ����ʱߵ���ʼ��������
		for (int i = 0; i < alg->vnum; i++) // �������ж���
		{
			if (visited[i] == 1) // ��������ѷ���
			{
				ArcNode* p = alg->vertices[i].firstArc; // ��ȡ���� i �ĵ�һ���ڽӶ���
				while (p) // �������� i �������ڽӶ���
				{
					if (p->arcValue < m && Adjacent(minTree, alg->vertices[i].data, alg->vertices[p->adjvex].data, 1) == -1 && visited[p->adjvex] == 0) // ����ҵ�Ȩֵ��С��δ���ʹ��ı�
					{
						index = p->adjvex; // ������СȨֵ��Ӧ�Ķ�������
						m = p->arcValue; // ������СȨֵ
						flag = 1; // ���±�־����Ϊ�ҵ����ʵı�
						x = i; // ������ʼ��������
					}
					p = p->NextArc; // ����������һ���ڽӶ���
				}
			}
		}
		if (flag) // ����ҵ����ʵı�
		{
			InsertVertex(minTree, alg->vertices[index].data); // ����Ӧ���������С������
			visited[index] = 1; // ��Ǹö���Ϊ�ѷ���
			Addedge(minTree, alg->vertices[x].data, alg->vertices[index].data, 1); // ����С����������ӱ�
			Set_edge_value(minTree, alg->vertices[x].data, alg->vertices[index].data, 1, m); // ���ñߵ�Ȩֵ
		}
		m = 9999; // ������СȨֵ
	}
}
*/

//1.��������ṹ���ߵ��������㣬x��y��Ȩֵ
//2.�Ա���������
//3.ÿ�δ���ѡ����С��һ���ߣ�ʹ�ò��鼯�ж��Ƿ�����ͬһ���ϡ������鷳һ���жϱߵ�������ı��Ƿ���ڹ�������
//4.�ǣ�ȡ��һ���ߣ��񣺼�����
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
