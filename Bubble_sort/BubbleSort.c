#include<stdio.h>
void swap(int *a,int *b) 
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void BubbleSort(int arr[],int size)
{
	for (int i = 0; i < size; i++) 
	{
		int flag = 0;
		for (int j = size-1; j > i; j--) 
		{
			if (arr[j] < arr[j - 1]) 
			{
				swap(&arr[j], &arr[j-1]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
int main() 
{
	int arr1[] = { 42,8,1,314,14,551,3,4,144 };
	BubbleSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	return 0;
}