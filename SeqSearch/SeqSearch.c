#include<stdio.h>
#include<stdlib.h>
#define CAPACITY 10
typedef int ELemtype;
typedef struct
{
	ELemtype* elem;
	int size;
}SStable;
void iniSStable(SStable* ss)
{
	ss->size = 0;
	ss->elem = (ELemtype*)malloc(sizeof(ELemtype) * CAPACITY);
	ss->elem[0] = 0;//из╠Ь
}
void AddElement(SStable* ss, ELemtype arr[CAPACITY])
{
	if (ss == NULL)
	{
		return;
	}
	if (ss->size >= CAPACITY)
	{
		int s = ss->size / CAPACITY + 1;
		ELemtype* ptr = (ELemtype*)realloc(ss->elem, sizeof(ELemtype) * CAPACITY * s);
		if (ptr == NULL)
		{
			perror("AddElement");
			return;
		}
		ss->elem = ptr;
		int i;
		int j;
		for (j = 0, i = ss->size; i < CAPACITY * s && j < CAPACITY; i++, j++)
		{
			ss->elem[i] = arr[j];
			ss->size++;
		}
	}
	else
	{
		for (int j = 1; j < CAPACITY; j++)
		{
			ss->elem[j] = arr[j];
			ss->size++;
		}
	}
}
void My_print(SStable* ss)
{
	if (ss == NULL)
	{
		return;
	}
	for (int i = 0; i < ss->size; i++)
	{
		if (i % 10 == 0 && i != 0)
		{
			printf("\n");
		}
		printf("%d ", ss->elem[i]);
	}
}
int SeqSearch(SStable* ss, ELemtype key)
{
	ss->elem[0] = key;
	for (int i = ss->size; ss->elem[i]!=key; i--)
	{
		return i;
	}
	return -1;
}
int main()
{
	SStable ss;
	iniSStable(&ss);
	ELemtype arr[CAPACITY] = { 9,13,24,13,41,13,41,34,11,56 };
	AddElement(&ss, arr);
	My_print(&ss);
	SeqSearch(&ss, 11);
}