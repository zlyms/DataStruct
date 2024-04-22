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
		for (int j = 0; j < CAPACITY; j++)
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
int binarySearch(SStable*ss,ELemtype key)
{
	if (ss == NULL) 
	{
		return;
	}
	int high = ss->size-1;
	int low = 0;
	int mid = (high + low) / 2;
	while (high >=low) 
	{
		if (ss->elem[mid] > key) 
		{
			high = mid - 1;
		}
		else if (ss->elem[mid] == key)
		{
			return mid;
		}
		else 
		{
			low = mid + 1;
		}
		mid =(high + low) / 2;
	}
	return -1;
}
int main()
{
	SStable ss;
	iniSStable(&ss);
	ELemtype arr[CAPACITY] = { 9,13,24,25,41,53,61,74,81,96 };
	AddElement(&ss, arr);
	binarySearch(&ss,96);
	//My_print(&ss);
}