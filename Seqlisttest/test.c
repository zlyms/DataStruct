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
		sl->data[i] = -1;
	}
	sl->len = 0;
}
void creatList(SL* sl) //初始化顺序表
{
	for (int i = 0; i < ININUM; i++)
	{
		sl->data[i] = i;
	}
	sl->len = ININUM;
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
	printf("data[%d]=%d\n", index, sl->data[index]);
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
int InsertSeqList(SL* sl) {//插入表

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
	if (sl->len == ININUM)
	{
		printf("存储已满\n");
		return 0;
	}
	for (int i = ININUM - 1; i > n; i--)
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

	for (int i = n; i < sl->len - 1; i++)
	{
		sl->data[i] = sl->data[i + 1];

	}
	printf("删除成功\n");
	sl->len--;
	My_Print(sl);
	return 1;
}
// 反转顺序表
void reverseSQL(SL* sl)
{
	int i = 0; // 定义起始索引
	int j = ININUM - 1; // 定义末尾索引
	int temp; // 临时变量，用于交换元素值
	while (i < j)  // 循环直到 i 大于等于 j
	{
		temp = sl->data[i]; // 交换元素值
		sl->data[i] = sl->data[j];
		sl->data[j] = temp;
		i++; // 向后移动起始索引
		j--; // 向前移动末尾索引
	}
}

// 将顺序表中的奇数放在一个顺序表中，偶数放在另一个顺序表中
int devide(SL* sl1, SL* sl2, SL* sl3)
{
	if (sl1->len == 0)  // 判断顺序表 sl1 是否为空
	{
		return 0; // 如果为空，则直接返回
	}
	int i, j, k; // 循环变量
	for (i = 0, j = 0, k = 0; i < sl1->len; i++) // 遍历顺序表 sl1
	{
		sl1->data[i] % 2 == 1 ? (sl2->data[j] = sl1->data[i], j++, sl2->len++) : (sl3->data[k] = sl1->data[i], k++, sl3->len++); // 根据奇偶性将元素放入不同的顺序表中
	}
	return 1; // 操作成功返回 1
}

// 将两个有序顺序表合并成一个有序顺序表
int unionlist(SL* sl1, SL* sl2, SL* sl3)
{
	int i, j, k; // 循环变量
	for (i = 0, j = 0, k = 0; i < sl1->len || j < sl2->len; )
	{
		if (sl1->data[i] > sl2->data[j] && sl1->data[i] != -1) // 如果 sl1 中的元素大于 sl2 中的元素且不为 -1
		{
			sl3->data[k] = sl1->data[i]; // 将 sl1 中的元素放入 sl3
			i++; // 移动 sl1 的索引
			k++; // 移动 sl3 的索引
			sl3->len++; // 更新 sl3 的长度
		}
		else if (sl1->data[i] < sl2->data[j] && sl2->data[j] != -1) // 如果 sl1 中的元素小于 sl2 中的元素且不为 -1
		{
			sl3->data[k] = sl2->data[j]; // 将 sl2 中的元素放入 sl3
			j++; // 移动 sl2 的索引
			k++; // 移动 sl3 的索引
			sl3->len++; // 更新 sl3 的长度
		}
	}
	return 1; // 操作成功返回 1
}

// 将顺序表中的奇数放在前面，偶数放在后面
void LeftoddRighteven(SL* sl)
{
	int i = 0; // 定义起始索引
	int j = sl->len - 1; // 定义末尾索引
	int temp; // 临时变量，用于交换元素值
	while (i < j)  // 循环直到 i 大于等于 j
	{
		if (sl->data[i] % 2 == 1 && sl->data[j] % 2 == 0) // 如果起始索引对应元素为奇数，末尾索引对应元素为偶数
		{
			i++; // 向后移动起始索引
			j--; // 向前移动末尾索引
		}
		else if (sl->data[i] % 2 == 0 && sl->data[j] % 2 == 1) // 如果起始索引对应元素为偶数，末尾索引对应元素为奇数
		{
			temp = sl->data[i]; // 交换元素值
			sl->data[i] = sl->data[j];
			sl->data[j] = temp;
			i++; // 向后移动起始索引
			j--; // 向前移动末尾索引
		}
		else if (sl->data[i] % 2 == 0 && sl->data[j] % 2 == 0) // 如果起始索引对应元素为偶数，末尾索引对应元素也为偶数
		{
			j--; // 向前移动末尾索引
		}
		else // 其余情况
		{
			i++; // 向后移动起始索引
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