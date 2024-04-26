#include<stdio.h>
#include<stdlib.h>
#include <math.h>

typedef int Elemtype;
typedef struct
{
	Elemtype maxValue; // 当前索引块中的最大值
	int high, low;     // 当前索引块的上下限
}index;

typedef struct
{
	index* i;   // 索引数组指针，用于存储分块的索引信息
	int num;    // 分块的数量
}bolckTable;

void iniblockTable(bolckTable* bl)
{
	if (bl == NULL)
	{
	}
	bl->num = 0; // 初始化分块表的数量为0
}

void DivideListBlock(bolckTable* bl, Elemtype List[], int size)
{
	if (bl == NULL)
	{
		return;
	}

	int n = ceil(sqrt(size)); // 计算分块的数量，向上取整
	int l = floor(sqrt(size)); // 每块的大小，向下取整
	index* ptr = (index*)malloc(sizeof(index) * n); // 分配索引数组的内存空间
	if (ptr == NULL)
	{
		perror("DivideListBlock");
		return;
	}
	bl->i = ptr; // 将索引数组指针指向分配的内存空间
	bl->num = n; // 更新分块的数量

	int s = 0;
	for (int i = 0; i < bl->num; i++)
	{
		int max = -1111; // 初始化当前索引块的最大值为一个较小的数
		for (int j = 0; j < l && s < size; j++, s++)
		{
			if (List[s] > max)
			{
				max = List[s]; // 找出当前索引块中的最大值
			}
		}
		bl->i[i].maxValue = max; // 更新当前索引块的最大值
		bl->i[i].high = (i + 1) * l - 1; // 更新当前索引块的上限
		if (bl->i[i].high >= size)
		{
			bl->i[i].high = size - 1; // 若超出线性表长度，则将上限设为线性表最后一个元素的下标
		}
		bl->i[i].low = i * l; // 更新当前索引块的下限
	}
}


int SeqbBockSeach(bolckTable* bl, Elemtype x, Elemtype List[])
{
	if (bl == NULL)
	{
		return -1; // 若分块表为空，则返回-1表示未找到目标元素
	}
	for (int i = 0; i < bl->num; i++)
	{
		int j = bl->i[i].low; // 设置起始位置为当前索引块的下限
		while (bl->i[i].maxValue >= x && j <= bl->i[i].high)
		{
			if (List[j] == x) // 若当前元素等于目标元素，则返回当前元素的下标
			{
				return j;
			}
			j++;
		}
	}
	return -1; // 若在分块表中未找到目标元素，则返回-1表示未找到
}

int BinaryaBlockSearch(bolckTable* bl, Elemtype x, Elemtype List[])
{
	if (bl == NULL)
	{
		return -1; // 若分块表为空，则返回-1表示未找到目标元素
	}

	int h;
	int l;
	l = 0; h = bl->num - 1;
	int  mid = (h + l) / 2;

	// 当low > high ,low停在刚好最小大于x的位置上
	// 发生low > high的前一步是low==mid==high
	// 当x<mid low+1,low>high>x
	// 当x>mid high-1,low不动，low=mid>x
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

	// 二分查找结束后，根据找到的块进行顺序查找
	for (int i = bl->i[l].low; i <= bl->i[l].high; i++)
	{
		if (List[i] == x)
		{
			return i; // 若找到目标元素，则返回其下标
		}
	}
	return -1; // 若在分块表中未找到目标元素，则返回-1表示未找到
}

int main()
{
	bolckTable bl;
	Elemtype List[10] = { 1,2,31,32,41,56,78,81,79,99 };
	DivideListBlock(&bl, List, sizeof(List) / sizeof(List[0]));
	BinaryaBlockSearch(&bl, 23, List);
	return 0;
}
