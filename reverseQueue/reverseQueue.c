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
	LNode* rear;
}LQueue;
typedef struct
{
   LNode * front;
}LSstack;
void IniQueue(LQueue*LQ)
{
	LQ->front = NULL;
	LQ->rear = NULL;
}
void IniStack(LSstack*LS)
{
	LS->front = NULL;
}
int isStackEmpity(LSstack*LS) 
{
	if (LS->front==NULL) 
	{
		printf("Õ»¿Õ\n");
		return 1;
	}
	return 0;
}
int Puch(LSstack*LS,Elemtype e) 
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
	LS->front=p;
	return 1;
}
int Pop(LSstack*LS,Elemtype*e) 
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
int enQueue(LQueue*LQ,Elemtype e)
{
	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL) 
	{
		perror("enQueue:");
		printf("¿Õ¼äÉêÇëÊ§°Ü\n");
		return 0;
	}
	if (LQ->front == NULL) 
	{
		LQ->front = p;
		LQ->rear = p;
	}
	p->data = e;
	LQ->rear ->next=p;
	p->next = NULL;
	LQ->rear = p;
	return 1;
}
int isQueueEmpity(LQueue *LQ) 
{
	if (LQ->front == NULL) 
	{
		printf("¶Ó¿Õ\n");
		return 1;
	}
	return 0;
}
int deQueue(LQueue*LQ,Elemtype*e) 
{
	if (isQueueEmpity(LQ)) 
	{
		LQ->rear = NULL;
		return 0;
	}
	LNode*p=LQ->front;
	LQ->front = LQ->front->next;
	*e = p->data;
	free(p);
	return 1;
}
int reverseElem(LQueue *LQ,LSstack*LS) 
{
	Elemtype queueHead;
	while (deQueue(LQ, &queueHead)) 
	{
		Puch(LS, queueHead);
	}
}
int main() 
{
	LSstack LS;
	LQueue LQ;
	IniStack(&LS);
	Elemtype topE;
	IniQueue(&LQ);
	enQueue(&LQ, 1);
	enQueue(&LQ, 2);
	enQueue(&LQ, 3);
	enQueue(&LQ, 4);
	enQueue(&LQ, 5);
	//deQueue(&LQ,&topE);
	reverseElem(&LQ, &LS);
	while (Pop(&LS, &topE)) 
	{
		printf("%d\n", topE);
	}
	return 0;
}