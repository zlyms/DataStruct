#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996) // 忽略 Visual Studio 中的警告信息

// 定义节点中存储的数据类型
typedef struct ElemType
{
	int value; // 节点值
} ElemType;

// 定义二叉树节点结构体
typedef struct TreeNode
{
	ElemType data; // 节点数据
	struct TreeNode* LChild; // 左子节点指针
	struct TreeNode* RChild; // 右子节点指针
} TreeNode, * TreeRoot;

// 初始化二叉树
void IniTree(TreeRoot* T)
{
	*T = NULL;
}

// 检查二叉树是否为空
int empityTree(TreeRoot T)
{
	if (T == NULL)
	{
		return 0; // 空树
	}
	return 1; // 非空树
}

// 创建深度为sz满二叉树，左优先插入新节点
void creatBinTree(TreeRoot* T, int sz)
{
	if (*T != NULL || sz <= 0)
	{
		return; // 若二叉树已存在或者传入的节点数不合法，则直接返回
	}
	int e;
	int temp = sz;
	scanf_s("%d", &e); // 从标准输入读取节点值
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode)); // 分配内存空间
	if (p == NULL)
	{
		perror("creatBinTree:"); // 内存分配失败时输出错误信息
		return;
	}
	p->data.value = e; // 将节点值赋给新节点的数据域
	p->LChild = p->RChild = NULL; // 将左右子节点指针置为空
	*T = p; // 将当前节点指针赋给根节点指针
	creatBinTree(&((*T)->LChild), --sz); // 递归创建左子树
	sz = temp;//重置sz
	creatBinTree(&((*T)->RChild), --sz); // 递归创建右子树
}

// 在二叉树中定位指定节点
void locate(TreeRoot T, int e, TreeNode** x)
{
	if (T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	if (T->data.value == e)
	{
		*x = T; // 若找到与目标值相等的节点，则将节点地址赋给指定指针
	}
	locate(T->LChild, e, x); // 在左子树中继续查找
	locate(T->RChild, e, x); // 在右子树中继续查找
}

// 添加子节点
int addchild(TreeRoot T, TreeNode* x, TreeRoot T1, int b)
{
	if (b == 0)
	{
		x->LChild = T1; // 添加左子节点
	}
	else if (b == 1)
	{
		x->RChild = T1; // 添加右子节点
	}
	return 1;
}

// 后序遍历删除节点及其子节点
void postorderdelete(TreeRoot* T)
{
	if (*T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	postorderdelete(&((*T)->LChild)); // 递归删除左子树
	postorderdelete(&((*T)->RChild)); // 递归删除右子树
	free((*T)); // 释放当前节点的内存空间
	*T = NULL; // 将当前节点指针置为空
}

// 删除子节点
void deleteChild(TreeRoot T, TreeNode* x, int b)
{
	if (T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	TreeNode* p = NULL;
	if (b == 0)
	{
		p = x->LChild; // 获取左子节点指针
	}
	else if (b == 1)
	{
		p = x->RChild; // 获取右子节点指针
	}
	postorderdelete(&p); // 后序遍历删除子节点及其子节点
}

// 先序遍历
void preorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	printf("%d  ", T->data.value); // 输出当前节点的值
	preorder(T->LChild); // 递归遍历左子树
	preorder(T->RChild); // 递归遍历右子树
}

// 中序遍历
void inorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	inorder(T->LChild); // 递归遍历左子树
	printf("%d  ", T->data.value); // 输出当前节点的值
	inorder(T->RChild); // 递归遍历右子树
}

// 后序遍历
void postorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // 若树为空，则直接返回
	}
	postorder(T->LChild); // 递归遍历左子树
	postorder(T->RChild); // 递归遍历右子树
	printf("%d  ", T->data.value); // 输出当前节点的值
}

// 主函数
int main()
{
	TreeRoot T;
	IniTree(&T); // 初始化二叉树
	creatBinTree(&T, 3); // 创建二叉树
	TreeNode* x;
	locate(T, 1, &x); // 在二叉树中定位指定节点
	//preorder(T); // 先序遍历
	//printf("\n");
	//inorder(T); // 中序遍历
	//printf("\n");
	//postorder(T); // 后序遍历
	//printf("\n");
	deleteChild(T, x, 0); // 删除指定节点的左子节点
	return 0;
}
