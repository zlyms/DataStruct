#include<stdio.h>
#include<stdlib.h>

#define MAXSIZENUM 10 // ���嶥���������

typedef char vextype; // ���嶥����������
typedef int arcValuetype; // ����ߵ�Ȩֵ��������

// �߽��Ķ���
typedef struct EdgeNode
{
	int tailvex; // �ߵ�β����������
	int headvex; // �ߵ�ͷ����������
	struct EdgeNode* hlink; // ָ��ͬһͷ���������һ����
	struct EdgeNode* tlink; // ָ��ͬһβ���������һ����
	arcValuetype arcValue; // �ߵ�Ȩֵ
} EdgeNode;

// ����ṹ��Ķ���
typedef struct
{
	vextype data; // ��������
	EdgeNode* firstin; // ָ���Ըö���Ϊͷ���ĵ�һ����
	EdgeNode* firstout; // ָ���Ըö���Ϊβ���ĵ�һ����
} vexNode, AdjList[MAXSIZENUM]; // �ڽӱ����Ͷ���

// ͼ�ṹ��Ķ���
typedef struct
{
	AdjList vertices; // ��������
	int vnum, arcnum; // ���������ͱ�����
} OrthList;

// ��ʼ��ͼ�ĺ���
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
		orl->vertices[i].data = '#'; // ��ʼ����������
	}
}

// ��ȡ�����ڶ��㼯���е�����
int Getindex(OrthList* orl, vextype x) {
	for (int i = 0; i < MAXSIZENUM; i++) {
		if (orl->vertices[i].data == x) {
			return i; // ���ض����ڶ��㼯���е�����
		}
	}
	printf("�����ڸö���\n");
	return -1; // ���㲻���ڣ�����-1
}

// ��ͼ�в��붥��
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
			orl->vertices[i].data = x; // ���붥������
			orl->vnum++; // ����������1
			return;
		}
	}
}

// ��ͼ����ӱ�
void AddEdge(OrthList* orl, vextype x, vextype y)
{
	int t = Getindex(orl, x); // ��ȡ�ߵ�β����������
	int e = Getindex(orl, y); // ��ȡ�ߵ�ͷ����������
	if (orl == NULL || t < 0 || e < 0)
	{
		return;
	}
	EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode)); // �����µı߽��
	if (p == NULL)
	{
		perror("AddEdge");
		return;
	}
	p->headvex = e; // ���ñߵ�ͷ����������
	p->tailvex = t; // ���ñߵ�β����������

	// ���߽�����ͷ������ı�������
	p->hlink = orl->vertices[e].firstin;
	orl->vertices[e].firstin = p;

	// ���߽�����β������ı�������
	p->tlink = orl->vertices[t].firstout;
	orl->vertices[t].firstout = p;
	orl->arcnum++; // ��������1
}

// ��ͼ��ɾ����
void RemoveEdge(OrthList* orl, vextype x, vextype y)
{
	int t = Getindex(orl, x); // ��ȡ�ߵ�β����������
	int e = Getindex(orl, y); // ��ȡ�ߵ�ͷ����������
	if (orl == NULL || t < 0 || e < 0)
	{
		return;
	}
	// �޸���ı߽ڵ㻡β��ͬ�Ľڵ�
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

	// �޸���ı߽ڵ㻡ͷ��ͬ�Ľڵ�
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
	free(p); // �ͷ��ڴ�
	p = NULL;
	orl->arcnum--; // ��������1
}

// ��ͼ��ɾ������
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

// ������
int main()
{
	OrthList orl;
	IniOrthList(&orl); // ��ʼ��ͼ

	// ��ͼ�в��붥��
	InsertVertex(&orl, 'A');
	InsertVertex(&orl, 'B');
	InsertVertex(&orl, 'C');
	InsertVertex(&orl, 'D');

	// ��ͼ����ӱ�
	AddEdge(&orl, 'A', 'B');
	AddEdge(&orl, 'A', 'C');
	AddEdge(&orl, 'C', 'D');
	AddEdge(&orl, 'C', 'A');
	AddEdge(&orl, 'D', 'C');
	AddEdge(&orl, 'D', 'B');
	AddEdge(&orl, 'D', 'A');

	// ɾ������'A'
	Deletevertex(&orl, 'A');

	return 1;
}
