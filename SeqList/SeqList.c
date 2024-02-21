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
		sl->data[i] = 0;
	}
	sl->len = 0;
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
	printf("data[%d]=%d\n",index,sl->data[index]);
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
int InsertSeqList(SL*sl){//�����

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
	if (sl->len== ININUM) 
	{
			printf("�洢����\n");
			return 0;
	}
		for (int i = ININUM-1; i > n; i--)
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
		
	for (int i = n; i < sl->len-1; i++) 
	{
		sl->data[i] = sl->data[i + 1];

	}
	printf("ɾ���ɹ�\n");
	sl->len--;
	My_Print(sl);
	return 1;
}
int main() 
{
	SL sl;
	IniSeqList(&sl);
	int input;
	
	do 
	{
		printf("------0.exit  1.insert   2.delete  3.find\n��ѡ��");
		scanf_s("%d", &input);
		switch (input)
		{
		case 0:
			break;
		case 1:
			InsertSeqList(&sl);
			break;
		case 2:
			DeleteSeList(&sl);
			break;
		case 3:
			FindSqeListNums(&sl);
			break;
		default:
			printf("�������");
			break;
		}
		
		
	} while (input);
	
	
	return 0;

}