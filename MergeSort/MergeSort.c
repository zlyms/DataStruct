#include<stdio.h>
#include<stdlib.h>
//将有序表合并
void merge(int A[], int low, int high, int mid)
{
	int* B = (int*)malloc(10 * sizeof(int));//辅助表
	int k, j, i;
	for (k = 0; k <= high; k++)
	{
		B[k] = A[k];//将所以元素拷入B表
	}
	for (i = low, k = i, j = mid + 1; i <= mid && j <= high; k++)
	{//左表low~mid,右表mid+1~high
		if (B[i] >= B[j])//左表当前位置大
			A[k] = B[i++];
		else
			A[k] = B[j++];//右表当前位置大
	}
	//清空多余部分
	while (i <= mid)
		A[k++] = B[i++];
	while (j <= high)
		A[k++] = B[j++];
	free(B);
	B = NULL;
}
void mergeSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;//从中间分为两个表
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, high, mid);//递归合并有序表
	}
}
int main()
{
	int arr1[] = { 42,14,1,314,14,551,3,4,3,144 };
	mergeSort(arr1, 0, 9);
	return 0;
}