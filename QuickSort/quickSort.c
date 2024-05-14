#include<stdio.h>

int partition(int arr[], int low, int high)
{
	int pivot = arr[low];//子表第一个元素做枢轴
	while (low < high)//左右指针确认位置
	{
		while (low < high && arr[high] >= pivot)//比枢轴小的放左边
			high--;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivot)//比枢轴大的放右边
			low++;
		arr[high] = arr[low];
	}
	arr[low] = pivot;//low==high就是枢轴位置
	return low;//返回枢轴位置，左边小，右边大
}
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivotpos = partition(arr, low, high);//以枢轴位置为基准拆分表
		quickSort(arr, low, pivotpos - 1);//处理左表
		quickSort(arr, pivotpos + 1, high);//处理右表
	}
}
int main()
{
	int arr1[] = { 42,14,1,314,14,551,3,4,3,144 };
	quickSort(arr1,0,8);
	return 0;
}