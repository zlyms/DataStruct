#include<stdio.h>
#define MAXSIZE 10
typedef int Elemtype;
typedef struct LNode
{
	Elemtype data[MAXSIZE];
	int tap;
	int front;
	int rear;
}CLQ;
void InicycleQueue(CLQ* cq)
{
	cq->front = 2;
	cq->rear = 2;
	cq->tap = 0;
}
int enQueue(CLQ* cq,Elemtype e)
{
	if (cq->rear == cq->front && cq->tap == 1) 
	{
		printf("¶ÓÂú\n");
		return 0;
	}
	cq->data[cq->rear] = e;
	cq->rear = (cq->rear + 1)%MAXSIZE;
	cq->tap = 1;
	return 1;
}
int deQueue(CLQ* cq, Elemtype* e)
{
	if (cq->rear == cq->front && cq->tap == 0) 
	{
		printf("¶Ó¿Õ\n");
		return 0;
	}
	*e = cq->data[cq->front];
	cq->front = (cq->front + 1) % MAXSIZE;
	cq->tap = 0;
	return 1;
}
int main()
{
	CLQ cq;
	Elemtype e;
	InicycleQueue(&cq);
	enQueue(&cq, 1);

	deQueue(&cq, &e);
	deQueue(&cq, &e);
	printf("%d\n", e);
	return 0;
}