#include<stdio.h>
#define CAPACITY 10
typedef int Elemtype;
typedef struct stack 
{
	Elemtype data[CAPACITY];
	int top;
}SQLstack;
void IniStack(SQLstack*s)
{
	s->top = -1;
}
int Puch(SQLstack* s, Elemtype e)
{
	if (s->top == CAPACITY-1) 
	{
		printf("Õ»ÇøÒÑÂú\n");
		return 0;
	}
	s->data[++(s->top)] = e;
	return 1;
}
Elemtype Pop(SQLstack* s)
{
	if (s->top==-1) 
	{
		printf("¿ÕÕ»\n");
		return 0;
	}
	Elemtype e = s->data[s->top--];
	return e;
}
Elemtype Getelement(SQLstack* s)
{
	if (s->top == -1)
	{
		printf("¿ÕÕ»\n");
		return 0;
	}
	return s->data[s->top];
}
int main() 
{
	SQLstack s;
	IniStack(&s);
	int i=0;
	while (Puch(&s, i++))
	{
		;
	}
	i = 5;
    Elemtype ret = Pop(&s);
	printf("%d\n", ret);
	printf("%d\n", Getelement(&s));
	return 0;
}