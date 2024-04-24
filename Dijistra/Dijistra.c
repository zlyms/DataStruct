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

typedef vextype Elemtype;

typedef struct LNode
{
	Elemtype data;      // ������
	struct LNode* next; // ָ����ָ����һ���ڵ�
} LNode;

typedef struct
{
	LNode* front; // ��ͷָ��
	LNode* rear;  // ��βָ��
} LQueue;          // ��ʽ���нṹ��

void IniLQueue(LQueue* LQ)
{
	LQ->front = NULL; // ��ʼ����ͷָ��
	LQ->rear = NULL;  // ��ʼ����βָ��
}

int isempty(LQueue* LQ)
{
	if (LQ->front == NULL) // �����ͷָ��Ϊ��
	{
		return 1; // ����Ϊ��
	}
	return 0; // ���зǿ�
}

int EnQueue(LQueue* LQ, Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode)); // �����½ڵ���ڴ�ռ�
	if (p == NULL)
	{
		perror("EnQueue:"); // ���������Ϣ
		printf("����ռ�ʧ��\n"); // �����ʾ��Ϣ
		return 0; // ����ʧ��
	}
	if (LQ->front == NULL) // �������Ϊ��
	{
		LQ->front = p; // �½ڵ��Ϊ��ͷ�ڵ�
		LQ->rear = p;  // �½ڵ��Ϊ��β�ڵ�
	}
	p->data = e;    // ��Ԫ�ظ�ֵ���½ڵ��������
	p->next = NULL; // �½ڵ��nextָ���ÿ�
	LQ->rear->next = p; // ���½ڵ���ص���β�ڵ��
	LQ->rear = p;       // ���¶�βָ��Ϊ�½ڵ�

	return 1; // ���سɹ�
}

int deQueue(LQueue* LQ, Elemtype* e)
{
	if (isempty(LQ)) // �������Ϊ��
	{
		printf("�ӿ�\n"); // �����ʾ��Ϣ
		return 0; // ����ʧ��
	}
	LNode* p = LQ->front; // �����ͷ�ڵ�ĵ�ַ
	*e = p->data;          // ����ͷ�ڵ�����ݸ�ֵ��*e
	LQ->front = LQ->front->next; // ���¶�ͷָ��Ϊԭ��ͷ�ڵ����һ���ڵ�
	if (LQ->front == NULL)
	{
		LQ->front = NULL;
		LQ->rear = NULL;
	}
	free(p);               // �ͷ�ԭ��ͷ�ڵ���ڴ�ռ�
	p = NULL;              // ��ԭ��ͷ�ڵ��ÿ�
	return 1;              // ���سɹ�
}

int GetElem(LQueue* LQ, Elemtype* e)
{
	if (isempty(LQ)) // �������Ϊ��
	{
		printf("�ӿ�\n"); // �����ʾ��Ϣ
		return 0; // ����ʧ��
	}
	*e = LQ->front->data; // ��ȡ��ͷ�ڵ������
	return 1;              // ���سɹ�
}

//-----------------------------------------------------------------
// ��ȡ�����ڶ��㼯���е�����
int Getindex(ALGraph* adj, vextype x) {
	for (int i = 0; i < MAXSIZE; i++) {
		if (adj->vertices[i].data == x) {
			return i; // ���ض����ڶ��㼯���е�����
		}
	}
	printf("�����ڸö���\n");
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

// �ж϶���x�Ͷ���y�Ƿ�����
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
		// ��������ͼ����ͬʱ�ж�x��y��y��x�ı��Ƿ����
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
		// ��������ͼ�������ж�x��y�ı��Ƿ����
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
			ptr->NextArc = alg->vertices[t].firstArc;
			alg->vertices[t].firstArc = ptr;
		}
		else if (alg->vertices[t].firstArc == NULL && ptr)
		{
			ptr->adjvex = e;
			alg->vertices[t].firstArc = ptr;
			ptr->NextArc = NULL;
		}
		alg->arcnum++;
	}
}
//ɾ�����
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
//ɾ������
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
	if (b == 0)
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
	else if (b == 1)
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
		return 0;
	}
	return p->arcValue;
}
int JudgeVisted(char visted[], ALGraph* alg)
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
 * ʹ�� Dijkstra �㷨����Ӷ��� v ��ͼ�������������̾��뼰���·��
 * ������
 *   - alg: ָ��ͼ��ָ��
 *   - v: ��ʼ�����Ķ���
 * ע�����
 *   - �˺�������ͼ�в����ڸ�Ȩ�ߣ������޷��õ���ȷ����̾���
 */
void Dijistra(ALGraph* alg, vextype v)
{
	int t = Getindex(alg, v); // ��ȡ���� v �ڶ��㼯���е�����
	char final[MAXSIZE] = { 0 }; // ��¼��ȷ�����·���Ķ���
	int path[MAXSIZE] = { 0 }; // ��¼���·����ǰ������
	int dis[MAXSIZE] = { 0 }; // ��¼���㵽��ʼ���� v ����̾���
	for (int i = 0; i < MAXSIZE; i++)
	{
		path[i] = -1; // ��ʼ��·��Ϊ -1����ʾδ֪·��
		dis[i] = 9999; // ��ʼ������Ϊһ���ϴ��ֵ����ʾδ֪����
	}
	final[t] = 1; // ����ʼ������Ϊ��ȷ�����·��
	dis[t] = 0; // ������ʼ���㵽����ľ���Ϊ 0

	while (JudgeVisted(final, alg)) // ������δȷ�����·���Ķ���ʱѭ��ִ��
	{
		ArcNode* p = alg->vertices[t].firstArc; // ��ȡ���� t �ĵ�һ���ڽӶ���
		int x = 9999; // ���ڼ�¼���·������
		while (p)
		{
			if (p->arcValue + dis[t] < dis[p->adjvex] && final[p->adjvex] == 0) // ���ͨ������ t ���ﶥ�� p->adjvex ��·������
			{
				dis[p->adjvex] = p->arcValue + dis[t]; // ���´Ӷ��� v ������ p->adjvex ����̾���
				path[p->adjvex] = t; // ��¼�Ӷ��� v ������ p->adjvex �����·����ǰ������
			}
			p = p->NextArc; // ������һ���ڽӶ���
		}
		for (int i = 0; i < alg->vnum; i++)
		{
			if (dis[i] < x && final[i] == 0) // �ҵ�δȷ�����·���Ķ����о�����С�Ķ���
			{
				x = dis[i];
				t = i; // ���� t Ϊ������С�Ķ�������
			}
		}
		final[t] = 1; // ������ t ���Ϊ��ȷ�����·��
	}
}
int main()
{
	LQueue LQ;    // ������ʽ���б���
	IniLQueue(&LQ); // ��ʼ������
	ALGraph alg;
	IniALGraph(&alg);
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
	Dijistra(&alg, 'E');
	return 0; // ���سɹ�
}
