#include<stdio.h>
void SelectSort(int arr[], int size)
{
	int i, j,temp;
	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (arr[j] < arr[i]) 
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}	
		}
	}
}
int main()
{
	int arr1[] = { 42,8,1,314,14,14,551,3,4,144 };
	SelectSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	return 0;
}