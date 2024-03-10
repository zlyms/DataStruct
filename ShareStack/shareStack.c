#include<stdio.h>
#define MAXSIZE 10
typedef int Elemtype;
typedef  struct 
{
	int top1;
	int top2;
	Elemtype data[MAXSIZE];
}ShareStack;
//����ջ
void IniStack(ShareStack*SS)//��ʼ������ջ��ջ��ָ��ָ�����һ��Ԫ�صĺ�һλ��ջ��ָ��ָ��ǰջ�����һ��Ԫ��
{
	SS->top1 = -1;
	SS->top2 = MAXSIZE-1;
}
int StackOverflow(ShareStack* SS)//�жϹ���ջ�Ƿ����
{
	if (SS->top1 == SS->top2) 
	{
		printf("ջ��\n");
		return 1;
	}
	return 0;
}
int isEmpityStack(int top)//�жϹ���ջ��һ���Ƿ��
{
	if (top==-1||top==MAXSIZE-1) 
	{
		printf("����\n");
		return 1;
	}
	return 0;
}
int Puch1(ShareStack* SS,Elemtype e)//��top1�Ƕ�ʼѹջ
{
	if (StackOverflow(SS))
	{
		return 0;
	}
	SS->data[(++SS->top1)] = e;//ָ��ջ��Ԫ�غ�һ��λ��Ȼ����ֵ
	return 1;
}
int Pop1(ShareStack* SS, Elemtype *e)//��top1�Ƕ˳�
{
	if (isEmpityStack(SS->top1)) 
	{
		return 0;
	}
	*e = SS->data[SS->top1--];//��ջ��Ԫ�س�ջ��ָ����һ��λ��
	return 1;
}
int Puch2(ShareStack* SS, Elemtype e)//��top2�Ƕ˿�ʼѹջ
{
	if (StackOverflow(SS)) 
	{
		return 0;
	}
	SS->data[SS->top2--] = e;//ָ�����һ��Ԫ�صĺ�һλ
	return 1;
}
int Pop2(ShareStack* SS, Elemtype* e)//��top2�Ƕ˿�ʼ��ջ
{
	if (isEmpityStack(SS->top2)) 
	{
		return 0;
	}
	*e = SS->data[++(SS->top2)];//ָ���ջԪ��
	return 1;
}
int main() 
{
	ShareStack SS;
	Elemtype topElem;
	IniStack(&SS);
	//Puch1(&SS, 1);
	//Puch1(&SS, 2);
	//Puch1(&SS, 3);
	//Puch1(&SS, 3);
	Puch1(&SS, 4);
	//Puch2(&SS, 5);
	//Puch2(&SS, 6);
	//Puch2(&SS, 7);
	//Puch2(&SS, 8);
	Puch2(&SS, 9);
	Pop1(&SS, &topElem);
	Pop1(&SS, &topElem);
	Pop2(&SS, &topElem);
	Pop2(&SS, &topElem);
	return 0;
}