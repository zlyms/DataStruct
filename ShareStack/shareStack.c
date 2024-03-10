#include<stdio.h>
#define MAXSIZE 10
typedef int Elemtype;
typedef  struct 
{
	int top1;
	int top2;
	Elemtype data[MAXSIZE];
}ShareStack;
//共享栈
void IniStack(ShareStack*SS)//初始化共享栈，栈顶指针指向最后一个元素的后一位，栈底指针指向当前栈中最后一个元素
{
	SS->top1 = -1;
	SS->top2 = MAXSIZE-1;
}
int StackOverflow(ShareStack* SS)//判断共享栈是否溢出
{
	if (SS->top1 == SS->top2) 
	{
		printf("栈满\n");
		return 1;
	}
	return 0;
}
int isEmpityStack(int top)//判断共享栈的一端是否空
{
	if (top==-1||top==MAXSIZE-1) 
	{
		printf("下溢\n");
		return 1;
	}
	return 0;
}
int Puch1(ShareStack* SS,Elemtype e)//从top1那端始压栈
{
	if (StackOverflow(SS))
	{
		return 0;
	}
	SS->data[(++SS->top1)] = e;//指向栈顶元素后一个位置然后填值
	return 1;
}
int Pop1(ShareStack* SS, Elemtype *e)//从top1那端出
{
	if (isEmpityStack(SS->top1)) 
	{
		return 0;
	}
	*e = SS->data[SS->top1--];//把栈顶元素出栈后指向下一个位置
	return 1;
}
int Puch2(ShareStack* SS, Elemtype e)//从top2那端开始压栈
{
	if (StackOverflow(SS)) 
	{
		return 0;
	}
	SS->data[SS->top2--] = e;//指向最后一个元素的后一位
	return 1;
}
int Pop2(ShareStack* SS, Elemtype* e)//从top2那端开始出栈
{
	if (isEmpityStack(SS->top2)) 
	{
		return 0;
	}
	*e = SS->data[++(SS->top2)];//指向出栈元素
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