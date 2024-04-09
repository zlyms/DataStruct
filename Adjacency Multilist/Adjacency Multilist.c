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
		aml->vertices[i].data = '#'; // 初始化顶点数据
		aml->vertices[i].firstedge = NULL;
	}
	aml->vnum = aml->arcnum = 0;
}
void addvex() {}//与十字链表无异
void addedge() {}//把边节点头插进两个节点的firstedge，把它们所指向的边节点分别赋给新加入的节点
void removeedge() {}//把ilink，jlink分别赋给x->first，y->first.然后free
void Deletevertex() {}//调用removeedge删除所有依附x的节点，vnum--，节点置#
int main()
{
	AML aml;
	IniAdjMulList(&aml);

	return 0;
}