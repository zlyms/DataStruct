#include<stdio.h>
#define MAXSIZENUM 10
typedef char vextype;
typedef struct Edgetype
{
	int ivex;
	int jvex;
	struct Edgetype* iLink;
	struct Edgetype* jLink;
}Edgetype;
typedef struct
{
	vextype data;
	Edgetype* firstedge;
}VNode, Adjlist[MAXSIZENUM];
typedef struct
{
	Adjlist vertices;
	int vnum, arcnum;
}AML;
void IniAdjMulList(AML* aml)
{
	if (aml == NULL)
		return;
	for (int i = 0; i < MAXSIZENUM; i++)
	{
		aml->vertices[i].data = '#'; // ��ʼ����������
		aml->vertices[i].firstedge = NULL;
	}
	aml->vnum = aml->arcnum = 0;
}
void addvex() {}//��ʮ����������
void addedge() {}//�ѱ߽ڵ�ͷ��������ڵ��firstedge����������ָ��ı߽ڵ�ֱ𸳸��¼���Ľڵ�
void removeedge() {}//��ilink��jlink�ֱ𸳸�x->first��y->first.Ȼ��free
void Deletevertex() {}//����removeedgeɾ����������x�Ľڵ㣬vnum--���ڵ���#
int main()
{
	AML aml;
	IniAdjMulList(&aml);

	return 0;
}