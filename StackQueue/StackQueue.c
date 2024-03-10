#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct LNode
{
	struct LNode* next;
	Elemtype data;
}LNode;
typedef struct
{
	LNode* front;
}LSstack;
void IniStack(LSstack* LS)
{
	LS->front = NULL;
}
int isStackEmpity(LSstack* LS)
{
	if (LS->front == NULL)
	{
		printf("Õ»¿Õ\n");
		return 1;
	}
	return 0;
}
int Puch(LSstack* LS, Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL)
	{
		perror("Puch:");
		printf("¿Õ¼äÉêÇëÊ§°Ü\n");
		return 0;
	}
	p->next = LS->front;
	p->data = e;
	LS->front = p;
	return 1;
}
int Pop(LSstack* LS, Elemtype* e)
{
	if (isStackEmpity(LS))
	{
		return 0;
	}
	LNode* p = LS->front;
	LS->front = LS->front->next;
	*e = p->data;
	free(p);
	return 1;
}
int isempityQueue(LSstack* LS1,LSstack *LS2) 
{
	if (LS1->front == NULL && LS2->front == NULL) 
	{
		printf("¶Ó¿Õ\n");
		return 1;
	}
	return 0;
}
int enQueue(LSstack*LS1,Elemtype e) 
{
	Puch(LS1, e);
}
int deQueue(LSstack*LS1,LSstack*LS2,Elemtype* e) 
{
	Elemtype data;
	if (isempityQueue(LS1,LS2))
	{
		return 0;
	}
	while (Pop(LS1, &data))
	{
		Puch(LS2, data);
	}
    Pop(LS2,e);
}
int main(){
	LSstack LS1;
	LSstack LS2;
	Elemtype QH;
	IniStack(&LS1);
	IniStack(&LS2);
	enQueue(&LS1, 1);
	enQueue(&LS1, 2);	
	enQueue(&LS1, 3);
	deQueue(&LS1, &LS2, &QH);
	printf("%d\n",QH);
	return 0;
}