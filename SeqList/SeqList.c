#include<stdio.h>
#define ININUM 10
typedef struct //定义顺序表
{
	int data[ININUM];
	int len;
}SL;
void IniSeqList(SL* sl) //初始化顺序表
{
	for (int i = 0; i < ININUM; i++) 
	{
		sl->data[i] = 0;
	}
	sl->len = 0;
}
void My_Print(SL* sl)//打印表
{
	for (int i = 0; i < sl->len; i++)
	{
		printf("data[%d]=%d\n", i, sl->data[i]);
	}
}
void FindSqeListIndex(SL* sl) //以下标为方式查找
{
	int index = 0;
	printf("请输入要查找元素的下标\n");
	scanf_s("%d", &index);
	if (index > sl->len - 1 || index < 0) 
	{
		printf("输入错误\n");
		return;
	}
	printf("data[%d]=%d\n",index,sl->data[index]);
}
void FindSqeListNums(SL* sl) //按值查找
{
	int nums = 0;
	printf("请输入要查找元素的值\n");
	scanf_s("%d", &nums);
	for (int i = 0; i < sl->len; i++) 
	{
		if (sl->data[i] == nums) 
		{
			printf("data[%d]=%d\n", i, sl->data[i]);
		}
	}

}
int InsertSeqList(SL*sl){//插入表

	int n = 0;
	int x = 0;
	printf("请输入需要插入的位置:");
	scanf_s("%d", &n);
	printf("请输入插入值:");
	scanf_s("%d", &x);
	if (n < 0 || n >sl->len) 
	{
		printf("插入位置错误\n");
		return 0;
	}
	if (sl->len== ININUM) 
	{
			printf("存储已满\n");
			return 0;
	}
		for (int i = ININUM-1; i > n; i--)
		{
			sl->data[i] = sl->data[i - 1];
		}
		sl->data[n] = x;
		printf("插入成功\n");
		sl->len++;
		My_Print(sl);
		return 1;
	
}

int DeleteSeList(SL* sl) //删除表
{
	int n = 0;
	printf("请输入需要删除的位置:");
	scanf_s("%d", &n);
	if (n < 0 || n > sl->len) 
	{
		return 0;
		printf("输入错误\n");
	}
		
	for (int i = n; i < sl->len-1; i++) 
	{
		sl->data[i] = sl->data[i + 1];

	}
	printf("删除成功\n");
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
		printf("------0.exit  1.insert   2.delete  3.find\n请选择：");
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
			printf("输入错误");
			break;
		}
		
		
	} while (input);
	
	
	return 0;

}