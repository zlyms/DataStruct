#include<stdio.h>
//������kΪ��������
void rootAdjust(int arr[], int k, int len)
{
	arr[0] = arr[k];//a[0]��¼��Ҫ������λ�õ�ֵ
	int i;
	for (i = k * 2; i <= len; i *= 2)
	{
		if (i < len && arr[i] < arr[i + 1])
			i++;
		if (arr[0] >= arr[i])//��>�����������
			break;
		else
		{
			arr[k] = arr[i];//����Ҹ��ǵ�ǰλ��
			k = i;//�µĿ�ȱλ��
		}
	}
	arr[k] = arr[0];
}
//��������ѣ�ͨ�����ն˽ڵ����
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
//����Ԫ�طŶѵף������������С�����ѵ��������ϸ�
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
//ɾ���öѵ�Ԫ�ش��汻ɾ��Ԫ�أ������������С�����ѵ��������³�
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
	i--;//��ȡ�ѵ�Ԫ���±�
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