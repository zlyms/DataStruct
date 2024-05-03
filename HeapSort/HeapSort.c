#include<stdio.h>
//调整以k为根的子树
void rootAdjust(int arr[], int k, int len)
{
	arr[0] = arr[k];//a[0]记录需要调整的位置的值
	int i;
	for (i = k * 2; i <= len; i *= 2)
	{
		if (i < len && arr[i] < arr[i + 1])
			i++;
		if (arr[0] >= arr[i])//根>左右无需调整
			break;
		else
		{
			arr[k] = arr[i];//左或右覆盖当前位置
			k = i;//新的空缺位置
		}
	}
	arr[k] = arr[0];
}
//创建大根堆，通过分终端节点访问
void CreateHeap(int arr[], int size)
{
	for (int i = size / 2; i > 0; i--)
	{
		rootAdjust(arr, i, size);
	}
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void HeapSort(int arr[], int size)
{
	CreateHeap(arr, size);
	for (int i = size; i > 1; i--)
	{
		swap(&arr[1], &arr[i]);
		rootAdjust(arr, 1, i - 1);
	}
}
//插入元素放堆底，并让他满足大（小）根堆的条件—上浮
void insert(int arr[], int x, int len)
{
	int i;
	for (i = 1; i <= len; i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = x;
			break;
		}
	}
	arr[0] = arr[i];
	for (int j = i / 2; j > 0; j /= 2)
	{
		if (arr[0] <= arr[j])
			break;
		else
		{
			arr[i] = arr[j];
			i = j;
		}
	}
	arr[i] = arr[0];

}
//删除让堆底元素代替被删除元素，并让他满足大（小）根堆的条件—下沉
void Delete(int arr[], int k, int len)
{
	int i;
	for (i = 1; i <= len; i++)
	{
		if (arr[i] == 0)
			break;
	}
	if (i == k) 
	{
		arr[i] = 0;
		return;
	}	
	if (i == 1)
		return;
	i--;//获取堆底元素下标
	arr[0] = arr[i];
	arr[i] = 0;
	int j;
	for (j = k * 2; j <= len - 1; j *= 2)
	{
		if (j < len && arr[j] < arr[j + 1])
			j++;
		if (arr[0] >= arr[j])
			break;
		else
		{
			arr[k] = arr[j];
			i = j;
		}
	}
	arr[k] = arr[0];
}
int main()
{
	int arr1[] = { 0,42,8,1,314,14,551,3,4,144,0,0 };
	//HeapSort(arr1, 9);
	CreateHeap(arr1, 9);
	insert(arr1, 15, 10);
	Delete(arr1, 2, 10);
	return 0;
}