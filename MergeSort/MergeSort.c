#include<stdio.h>
#include<stdlib.h>
//�������ϲ�
void merge(int A[], int low, int high, int mid)
{
	int* B = (int*)malloc(10 * sizeof(int));//������
	int k, j, i;
	for (k = 0; k <= high; k++)
	{
		B[k] = A[k];//������Ԫ�ؿ���B��
	}
	for (i = low, k = i, j = mid + 1; i <= mid && j <= high; k++)
	{//���low~mid,�ұ�mid+1~high
		if (B[i] >= B[j])//���ǰλ�ô�
			A[k] = B[i++];
		else
			A[k] = B[j++];//�ұ�ǰλ�ô�
	}
	//��ն��ಿ��
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
		int mid = (low + high) / 2;//���м��Ϊ������
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, high, mid);//�ݹ�ϲ������
	}
}
int main()
{
	int arr1[] = { 42,14,1,314,14,551,3,4,3,144 };
	mergeSort(arr1, 0, 9);
	return 0;
}