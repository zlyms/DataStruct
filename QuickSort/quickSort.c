#include<stdio.h>

int partition(int arr[], int low, int high)
{
	int pivot = arr[low];//�ӱ��һ��Ԫ��������
	while (low < high)//����ָ��ȷ��λ��
	{
		while (low < high && arr[high] >= pivot)//������С�ķ����
			high--;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivot)//�������ķ��ұ�
			low++;
		arr[high] = arr[low];
	}
	arr[low] = pivot;//low==high��������λ��
	return low;//��������λ�ã����С���ұߴ�
}
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pivotpos = partition(arr, low, high);//������λ��Ϊ��׼��ֱ�
		quickSort(arr, low, pivotpos - 1);//�������
		quickSort(arr, pivotpos + 1, high);//�����ұ�
	}
}
int main()
{
	int arr1[] = { 42,14,1,314,14,551,3,4,3,144 };
	quickSort(arr1,0,8);
	return 0;
}