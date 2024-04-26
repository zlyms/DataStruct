#include<stdio.h>
#include<stdlib.h>
#include <math.h>

typedef int Elemtype;
typedef struct
{
	Elemtype maxValue; // ��ǰ�������е����ֵ
	int high, low;     // ��ǰ�������������
}index;

typedef struct
{
	index* i;   // ��������ָ�룬���ڴ洢�ֿ��������Ϣ
	int num;    // �ֿ������
}bolckTable;

void iniblockTable(bolckTable* bl)
{
	if (bl == NULL)
	{
	}
	bl->num = 0; // ��ʼ���ֿ�������Ϊ0
}

void DivideListBlock(bolckTable* bl, Elemtype List[], int size)
{
	if (bl == NULL)
	{
		return;
	}

	int n = ceil(sqrt(size)); // ����ֿ������������ȡ��
	int l = floor(sqrt(size)); // ÿ��Ĵ�С������ȡ��
	index* ptr = (index*)malloc(sizeof(index) * n); // ��������������ڴ�ռ�
	if (ptr == NULL)
	{
		perror("DivideListBlock");
		return;
	}
	bl->i = ptr; // ����������ָ��ָ�������ڴ�ռ�
	bl->num = n; // ���·ֿ������

	int s = 0;
	for (int i = 0; i < bl->num; i++)
	{
		int max = -1111; // ��ʼ����ǰ����������ֵΪһ����С����
		for (int j = 0; j < l && s < size; j++, s++)
		{
			if (List[s] > max)
			{
				max = List[s]; // �ҳ���ǰ�������е����ֵ
			}
		}
		bl->i[i].maxValue = max; // ���µ�ǰ����������ֵ
		bl->i[i].high = (i + 1) * l - 1; // ���µ�ǰ�����������
		if (bl->i[i].high >= size)
		{
			bl->i[i].high = size - 1; // ���������Ա��ȣ���������Ϊ���Ա����һ��Ԫ�ص��±�
		}
		bl->i[i].low = i * l; // ���µ�ǰ�����������
	}
}


int SeqbBockSeach(bolckTable* bl, Elemtype x, Elemtype List[])
{
	if (bl == NULL)
	{
		return -1; // ���ֿ��Ϊ�գ��򷵻�-1��ʾδ�ҵ�Ŀ��Ԫ��
	}
	for (int i = 0; i < bl->num; i++)
	{
		int j = bl->i[i].low; // ������ʼλ��Ϊ��ǰ�����������
		while (bl->i[i].maxValue >= x && j <= bl->i[i].high)
		{
			if (List[j] == x) // ����ǰԪ�ص���Ŀ��Ԫ�أ��򷵻ص�ǰԪ�ص��±�
			{
				return j;
			}
			j++;
		}
	}
	return -1; // ���ڷֿ����δ�ҵ�Ŀ��Ԫ�أ��򷵻�-1��ʾδ�ҵ�
}

int BinaryaBlockSearch(bolckTable* bl, Elemtype x, Elemtype List[])
{
	if (bl == NULL)
	{
		return -1; // ���ֿ��Ϊ�գ��򷵻�-1��ʾδ�ҵ�Ŀ��Ԫ��
	}

	int h;
	int l;
	l = 0; h = bl->num - 1;
	int  mid = (h + l) / 2;

	// ��low > high ,lowͣ�ڸպ���С����x��λ����
	// ����low > high��ǰһ����low==mid==high
	// ��x<mid low+1,low>high>x
	// ��x>mid high-1,low������low=mid>x
	while (l < h)
	{
		if (bl->i[mid].maxValue < x)
		{
			l = mid + 1;
			mid = (l + h) / 2;
		}
		else if (bl->i[mid].maxValue > x)
		{
			h = mid - 1;
			mid = (l + h) / 2;
		}
		else
		{
			break;
		}
	}

	// ���ֲ��ҽ����󣬸����ҵ��Ŀ����˳�����
	for (int i = bl->i[l].low; i <= bl->i[l].high; i++)
	{
		if (List[i] == x)
		{
			return i; // ���ҵ�Ŀ��Ԫ�أ��򷵻����±�
		}
	}
	return -1; // ���ڷֿ����δ�ҵ�Ŀ��Ԫ�أ��򷵻�-1��ʾδ�ҵ�
}

int main()
{
	bolckTable bl;
	Elemtype List[10] = { 1,2,31,32,41,56,78,81,79,99 };
	DivideListBlock(&bl, List, sizeof(List) / sizeof(List[0]));
	BinaryaBlockSearch(&bl, 23, List);
	return 0;
}
