#include<stdio.h>
void  InsertSort1(int arr[], int size)
{
	int temp;
	for (int i = 1; i < size; i++)
	{
		int j = i - 1;
		while (j >= 0 && arr[j] > arr[j+1])
		{
			temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
			j--;
		}
	}
}
//带哨兵-arr[0]
void  InsertSort2(int arr[], int size)
{
	for (int i = 2; i < size; i++)
	{
		if (arr[i] < arr[i - 1]) 
		{
			arr[0] = arr[i];//立哨兵
			int j = i - 1;
			for (;arr[0] <arr[j]; j--)
			{
				arr[j + 1] = arr[j];//后移腾出插入位置
			}
			arr[j+1] = arr[0];//插入
		}
	}
}
//二分查找插排
void  InsertSort3(int arr[] ,int size) 
{
	int low; int high; int mid;
	for (int i = 2; i < size; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			arr[0] = arr[i];
			high = i;
			low = 1;
			while (low<=high)//二分找插入位置
			{
				mid = (low + high) / 2;
				if (arr[mid] > arr[i])
					high = mid - 1;
				else if (arr[mid] <= arr[i])
					low = mid + 1;
			}
			int j = i - 1;
			for (; j >= low; j--)//从low到i的元素后移
				arr[j + 1] = arr[j];
			arr[j + 1] = arr[0];//插入
		}
	}
}
int main()
{
	int arr1[] = { 8,42,1,314,14,551,3,4,144 };
	int arr2[] = { 0,8,42,1,314,14,14,551,3,4,144 };
	InsertSort3(arr2, sizeof(arr2) / sizeof(arr1[0]));
	return 0;
}