#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct LNode
{
	Elemtype e;
	struct LNode* next;
}LNode,*LinkStack;
void IniLStack(LinkStack* LS)
{
	LNode * p = *LS;
	p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL) 
	{
		perror("IniLStack:");
		printf("�ڴ�����ʧ��\n");
		return;
	}
	p->next = NULL;
	*LS = p;
	return 1;
}
int isemptyStack(LinkStack LS)
{
	if (LS->next == NULL) 
	{
		printf("��ջ\n");
		return 1;
	}
	return 0;
}
int Puch(LinkStack LS,char c)
{

	LNode* p = (LNode*)malloc(sizeof(LNode));
	if (p==NULL) 
	{
		perror("Puch:");
		printf("�ڴ�����ʧ��\n");
		return 0;
	}
	p->e = c;
	p->next = LS->next;
	LS->next = p;
	return 1;
}
int Pop(LinkStack LS, char* c)
{
	if (isemptyStack(LS)) 
	{
		printf("��ջʧ��\n");
		return 0;
	}
	LNode* p = LS->next;
	*c = p->e;
	LS->next = p->next;
	free(p);
	p = NULL;
}
int BracktMatch(char arr[],int len)
{
	LinkStack LS;
	IniLStack(&LS);
	for (int i = 0; i < len; i++) 
	{
		if (arr[i] == '{' || arr[i] == '[' || arr[i] == '(') 
		{
			Puch(LS, arr[i]);
		}
		else if (isemptyStack(LS)) 
		{
			printf("�����ŵ���");
			return 0;
		}
		else 
		{	
			char topStack;
			Pop(LS, &topStack);
			if (arr[i] == '}' && topStack != '{')
				return 0;
			if (arr[i] == '[' && topStack != ']')
				return 0;
			if (arr[i] == ')' && topStack != '(')
			{
				printf("��ƥ��\n");
				return 0;
			}
				
		}

	}
	if (isemptyStack==0) 
	{
		printf("�����ŵ���\n");
		return 1;
	}

}
int main() 
{
	char arr[] = "()()()()()[){}";
	int len = sizeof(arr) / sizeof(arr[0]) - 1;
	BracktMatch(arr,len);
}