#include<stdio.h>
#define ININUM 10
typedef struct //����˳���
{
	int data[ININUM];
	int len;
}SL;
void IniSeqList(SL* sl) //��ʼ��˳���
{
	for (int i = 0; i < ININUM; i++)
	{
		sl->data[i] = -1;
	}
	sl->len = 0;
}
void creatList(SL* sl) //��ʼ��˳���
{
	for (int i = 0; i < ININUM; i++)
	{
		sl->data[i] = i;
	}
	sl->len = ININUM;
}
void My_Print(SL* sl)//��ӡ��
{
	for (int i = 0; i < sl->len; i++)
	{
		printf("data[%d]=%d\n", i, sl->data[i]);
	}
}
void FindSqeListIndex(SL* sl) //���±�Ϊ��ʽ����
{
	int index = 0;
	printf("������Ҫ����Ԫ�ص��±�\n");
	scanf_s("%d", &index);
	if (index > sl->len - 1 || index < 0)
	{
		printf("�������\n");
		return;
	}
	printf("data[%d]=%d\n", index, sl->data[index]);
}
void FindSqeListNums(SL* sl) //��ֵ����
{
	int nums = 0;
	printf("������Ҫ����Ԫ�ص�ֵ\n");
	scanf_s("%d", &nums);
	for (int i = 0; i < sl->len; i++)
	{
		if (sl->data[i] == nums)
		{
			printf("data[%d]=%d\n", i, sl->data[i]);
		}
	}

}
int InsertSeqList(SL* sl) {//�����

	int n = 0;
	int x = 0;
	printf("��������Ҫ�����λ��:");
	scanf_s("%d", &n);
	printf("���������ֵ:");
	scanf_s("%d", &x);
	if (n < 0 || n >sl->len)
	{
		printf("����λ�ô���\n");
		return 0;
	}
	if (sl->len == ININUM)
	{
		printf("�洢����\n");
		return 0;
	}
	for (int i = ININUM - 1; i > n; i--)
	{
		sl->data[i] = sl->data[i - 1];
	}
	sl->data[n] = x;
	printf("����ɹ�\n");
	sl->len++;
	My_Print(sl);
	return 1;

}

int DeleteSeList(SL* sl) //ɾ����
{
	int n = 0;
	printf("��������Ҫɾ����λ��:");
	scanf_s("%d", &n);
	if (n < 0 || n > sl->len)
	{
		return 0;
		printf("�������\n");
	}

	for (int i = n; i < sl->len - 1; i++)
	{
		sl->data[i] = sl->data[i + 1];

	}
	printf("ɾ���ɹ�\n");
	sl->len--;
	My_Print(sl);
	return 1;
}
// ��ת˳���
void reverseSQL(SL* sl)
{
	int i = 0; // ������ʼ����
	int j = ININUM - 1; // ����ĩβ����
	int temp; // ��ʱ���������ڽ���Ԫ��ֵ
	while (i < j)  // ѭ��ֱ�� i ���ڵ��� j
	{
		temp = sl->data[i]; // ����Ԫ��ֵ
		sl->data[i] = sl->data[j];
		sl->data[j] = temp;
		i++; // ����ƶ���ʼ����
		j--; // ��ǰ�ƶ�ĩβ����
	}
}

// ��˳����е���������һ��˳����У�ż��������һ��˳�����
int devide(SL* sl1, SL* sl2, SL* sl3)
{
	if (sl1->len == 0)  // �ж�˳��� sl1 �Ƿ�Ϊ��
	{
		return 0; // ���Ϊ�գ���ֱ�ӷ���
	}
	int i, j, k; // ѭ������
	for (i = 0, j = 0, k = 0; i < sl1->len; i++) // ����˳��� sl1
	{
		sl1->data[i] % 2 == 1 ? (sl2->data[j] = sl1->data[i], j++, sl2->len++) : (sl3->data[k] = sl1->data[i], k++, sl3->len++); // ������ż�Խ�Ԫ�ط��벻ͬ��˳�����
	}
	return 1; // �����ɹ����� 1
}

// ����������˳���ϲ���һ������˳���
int unionlist(SL* sl1, SL* sl2, SL* sl3)
{
	int i, j, k; // ѭ������
	for (i = 0, j = 0, k = 0; i < sl1->len || j < sl2->len; )
	{
		if (sl1->data[i] > sl2->data[j] && sl1->data[i] != -1) // ��� sl1 �е�Ԫ�ش��� sl2 �е�Ԫ���Ҳ�Ϊ -1
		{
			sl3->data[k] = sl1->data[i]; // �� sl1 �е�Ԫ�ط��� sl3
			i++; // �ƶ� sl1 ������
			k++; // �ƶ� sl3 ������
			sl3->len++; // ���� sl3 �ĳ���
		}
		else if (sl1->data[i] < sl2->data[j] && sl2->data[j] != -1) // ��� sl1 �е�Ԫ��С�� sl2 �е�Ԫ���Ҳ�Ϊ -1
		{
			sl3->data[k] = sl2->data[j]; // �� sl2 �е�Ԫ�ط��� sl3
			j++; // �ƶ� sl2 ������
			k++; // �ƶ� sl3 ������
			sl3->len++; // ���� sl3 �ĳ���
		}
	}
	return 1; // �����ɹ����� 1
}

// ��˳����е���������ǰ�棬ż�����ں���
void LeftoddRighteven(SL* sl)
{
	int i = 0; // ������ʼ����
	int j = sl->len - 1; // ����ĩβ����
	int temp; // ��ʱ���������ڽ���Ԫ��ֵ
	while (i < j)  // ѭ��ֱ�� i ���ڵ��� j
	{
		if (sl->data[i] % 2 == 1 && sl->data[j] % 2 == 0) // �����ʼ������ӦԪ��Ϊ������ĩβ������ӦԪ��Ϊż��
		{
			i++; // ����ƶ���ʼ����
			j--; // ��ǰ�ƶ�ĩβ����
		}
		else if (sl->data[i] % 2 == 0 && sl->data[j] % 2 == 1) // �����ʼ������ӦԪ��Ϊż����ĩβ������ӦԪ��Ϊ����
		{
			temp = sl->data[i]; // ����Ԫ��ֵ
			sl->data[i] = sl->data[j];
			sl->data[j] = temp;
			i++; // ����ƶ���ʼ����
			j--; // ��ǰ�ƶ�ĩβ����
		}
		else if (sl->data[i] % 2 == 0 && sl->data[j] % 2 == 0) // �����ʼ������ӦԪ��Ϊż����ĩβ������ӦԪ��ҲΪż��
		{
			j--; // ��ǰ�ƶ�ĩβ����
		}
		else // �������
		{
			i++; // ����ƶ���ʼ����
		}
	}
}

int main()
{
	SL sl1;
	SL sl2;
	SL sl3;
	SL sl4;
	creatList(&sl1);
	IniSeqList(&sl2);
	IniSeqList(&sl3);
	IniSeqList(&sl4);
	reverseSQL(&sl1);
//	My_Print(&sl1);
	devide(&sl1, &sl2, &sl3);
	/*My_Print(&sl2);
	printf("\n");
	My_Print(&sl3);*/
	unionlist(&sl2, &sl3,&sl4);
	LeftoddRighteven(&sl4);
	My_Print(&sl4);
	return 0;

}