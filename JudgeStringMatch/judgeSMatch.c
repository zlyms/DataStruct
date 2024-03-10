#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct LNode
{
	Elemtype data;
	struct LNode* next;
}LNode,*Linklist;
void IniLinkList(Linklist*L) 
{
	*L = NULL;
}
int Puch(Linklist* L,Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL) 
	{
		perror("Puch:");
		printf("ÄÚ´æÉêÇëÊ§°Ü\n");
		return 0;
	}

	p->data = e;
	p->next =*L;
	*L = p;
	return 1;
}
int isEmpity(Linklist L)
{
	if (L == NULL) 
	{
		printf("¿ÕÕ»\n");
		return 1;
	}
	return 0;
}
int Pop(Linklist *L, Elemtype *e)
{
	LNode* p = *L;
	if (isEmpity(p)) 
	{
		return 0;
	}
	*L = (*L)->next;
	*e = p->data;
	free(p);
	return 1;

}
int main() 
{
	Linklist L;
	Elemtype topE;
	IniLinkList(&L);
	char arr[] = "XSSX";
	int i = 0;
	while (arr[i]) 
	{
		Puch(&L,arr[i]);
		i++;
	}
	i = 0;
	while (Pop(&L, &topE)&&topE == arr[i]) 
	{
		i++;
	}
	printf("%d\n",i);
	printf("%c\n", topE);
	return 0;
}