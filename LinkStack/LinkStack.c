#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct LNode
{
	struct LNode* next;
	  Elemtype data;
}*LinkStack,LNode;
void IniStack(LinkStack*L)
{
	*L = NULL;
}
int Puch(LinkStack *L, Elemtype e)
{
		LNode* p = (LNode*)malloc(sizeof(LNode));
		if (p==NULL)
		{
			perror("Puch:");
			printf("¿Õ¼äÉêÇëÊ§°Ü\n");
			return 0;
		}
		p->next = *L;
		p->data = e;
		*L = p;
		return 1;
}
int Pop(LinkStack* L) 
{
	if (*L == NULL) 
	{
		printf("¿ÕÕ»\n");
		return 0;
	}
	LNode* p = *L;
	*L = (*L)->next;
	free(p);
	return 1;
}
LNode* GetElem(LinkStack* L)
{
	if (*L == NULL)
	{
		printf("¿ÕÕ»\n");
		return NULL;
	}
	return *L;
}
int main() 
{
	LinkStack L;
	IniStack(&L);
	Puch(&L, 3);
	Puch(&L, 4);
	Puch(&L, 5);
	Puch(&L, 6);
	Puch(&L, 7);
	Pop(&L);
	LNode* p = L;
	//while (p!=NULL) 
	//{
	//	printf("%d\n", p->data);
	//	p = p->next;
	//	
	//}
	printf("%d\n", p->data);
	return 0;
}