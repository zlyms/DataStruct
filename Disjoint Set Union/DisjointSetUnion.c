#include<stdio.h>
#define MAXSIZE 15
#pragma warning(disable:4996) // 禁用4996警告，该警告通常是关于使用了被认为不安全的函数或者函数的调用不符合标准规范

typedef char Elemtype; // 定义树节点中数据的类型

typedef struct
{
	Elemtype data; // 节点中存储的数据
	int parent;    // 父节点的下标，-1表示该节点为根节点
} TreeNode; // 树节点的结构体定义

typedef struct 
{
	TreeNode nodes[MAXSIZE]; // 存储节点的数组
	int n;                   // 当前树中节点的数量
} PTree; // 并查集的结构体定义

// 初始化并查集，将节点数量置为0，所有父节点下标置为-1（表示根节点）
void IniPTree(PTree* PT)
{
	if (PT == NULL) // 如果传入的树为空指针，直接返回
	{
		return;
	}
	PT->n = 0; // 将节点数量初始化为0
	for (int i = 0; i < MAXSIZE; i++) // 遍历所有节点数组，将父节点下标初始化为-1
	{
		PT->nodes[i].parent = -1;
	}
}

Elemtype e = 'A'; // 定义一个全局变量 e 用于初始化节点数据

// 创建并查集
void CreatePTree(PTree* PT)
{
	if (PT == NULL) // 如果传入的树为空指针，直接返回
	{
		return;
	}	
	int switchoff = 1; // 控制是否继续添加节点的开关
	int temp = PT->n; // 临时变量，用于保存当前节点的下标
	int size = 0; // 记录当前集合节点个数
    int root = PT->n; // 记录根节点的下标
	while (switchoff != 1 && PT->n < MAXSIZE) // 循环读取用户输入，直到开关为1或者节点数量达到上限
	{
		scanf("%d",&switchoff); // 输入一个整数，用于控制是否继续添加节点0换层添加，1退出
		PT->nodes[PT->n].parent = temp; // 设置当前节点的父节点下标为temp
		PT->nodes[PT->n++].data = e; // 设置当前节点的数据为e，并将节点数量加1
		size--; // 节点大小减1
		if (switchoff == 0) // 如果输入为0，则将temp设置为当前节点的下标
		{
			temp = PT->n - 1;
		}
		e++; // e自增1，用于下一个节点的数据初始化
	}
	if (root < PT->n) // 如果存在根节点
		PT->nodes[root].parent = size; // 设置根节点的父节点下标为size
}

// 查找节点所在集合的根节点
int find(PTree* PT, int x)
{
	while (PT->nodes[x].parent >= 0) // 如果节点x的父节点下标大于等于0，则说明x不是根节点
		x = PT->nodes[x].parent; // 将x更新为其父节点下标，继续查找
	return x; // 返回x，即为根节点的下标
}

// 改进的查找函数，同时实现了路径压缩
int findImporve(PTree* PT, int x)
{
	int root = x; // 初始化根节点为x
	if (PT == NULL) // 如果树为空，直接返回
	{
		return;
    }
	while (PT->nodes[root].parent >= 0) // 循环直到找到根节点
	{
		root = PT->nodes[root].parent; // 更新根节点为其父节点
	}
	while (x != root) // 循环直到节点x的父节点为根节点
	{
		int t = PT->nodes[x].parent; // 保存节点x的父节点
		PT->nodes[x].parent = root; // 将节点x的父节点更新为根节点
		x = t; // 更新x为其父节点，继续压缩路径
	}
	return root; // 返回根节点的下标
}

// 合并两个集合
void uniontree(PTree* PT, int root1, int root2)
{
	if (root1 == root2) // 如果两个根节点相同，不需要合并，直接返回
	{
		return;
	}
	if (PT->nodes[root1].parent < PT->nodes[root2].parent) // 小树向大树合并
	{
		PT->nodes[root2].parent = root1; // 将根节点2的父节点下标更新为根节点1的下标
	}
	else // 否则
	{
		PT->nodes[root1].parent = root2; // 将根节点1的父节点下标更新为根节点2的下标
	}
}

int main() 
{
	PTree PT;
	IniPTree(&PT);
	/*CreatePTree(&PT);
	CreatePTree(&PT);
	CreatePTree(&PT);*/
	PT.nodes[PT.n++] = (TreeNode){ 'A',-6 };
	PT.nodes[PT.n++] = (TreeNode){ 'B', 0 };
	PT.nodes[PT.n++] = (TreeNode){ 'C',-2 };
	PT.nodes[PT.n++] = (TreeNode){ 'D',-5 };
	PT.nodes[PT.n++] = (TreeNode){ 'E', 1 };
	PT.nodes[PT.n++] = (TreeNode){ 'F', 1 };
	PT.nodes[PT.n++] = (TreeNode){ 'G', 2 };
	PT.nodes[PT.n++] = (TreeNode){ 'H', 3 };
	PT.nodes[PT.n++] = (TreeNode){ 'I', 3 };
	PT.nodes[PT.n++] = (TreeNode){ 'J', 3 };
	PT.nodes[PT.n++] = (TreeNode){ 'K', 4 };
	PT.nodes[PT.n++] = (TreeNode){ 'L', 4 };
	PT.nodes[PT.n++] = (TreeNode){ 'M', 7 };
	find(&PT, 9);
	return 0;
}