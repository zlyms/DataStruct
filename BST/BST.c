#include<stdio.h>
#include<stdlib.h>

typedef struct BSTNode
{
	int key;
	struct BSTNode* Lchild, * Rchild;
}BSTNode, * BSTree;

// 初始化二叉搜索树
void iniBSTree(BSTree* bst)
{
	if (*bst == NULL)
	{
		return;
	}
	*bst = NULL;
}

// 向二叉搜索树插入节点
void InsertBSTNode(BSTree* bst, int x)
{
	if ((*bst) == NULL)
	{
		BSTNode* ptr = (BSTNode*)malloc(sizeof(BSTNode));
		if (ptr == NULL)
		{
			perror("InsertBSTNode");
			return;
		}
		(*bst) = ptr;
		(*bst)->key = x;
		(*bst)->Rchild = (*bst)->Lchild = NULL;
	}
	else if ((*bst)->key == x)
	{
		return;
	}
	else if ((*bst)->key > x)
	{
		InsertBSTNode(&((*bst)->Lchild), x);
	}
	else
	{
		InsertBSTNode(&((*bst)->Rchild), x);
	}
}

// 在二叉搜索树中搜索节点
BSTNode* BSTsearch(BSTree* bst, int x)
{
	BSTNode* T = *bst;
	if (T == NULL)
	{
		return NULL;
	}
	if (T->key == x)
	{
		return T;
	}
	else if (T->key > x)
	{
		BSTsearch(&(T->Lchild), x);
	}
	else
	{
		BSTsearch(&(T->Rchild), x);
	}
}

// 全局变量用于记录删除操作中的前驱节点
BSTNode* pre = NULL;

// 删除二叉搜索树中的节点
int DeleteBSTNode(BSTree* bst, int x)
{
	if ((*bst) == NULL)
	{
		return -1; // 未找到要删除的节点
	}
	else if ((*bst)->key == x && (*bst)->Lchild != NULL && (*bst)->Rchild != NULL)
	{
		// 删除有两个子节点的情况，找到左子树中的最大值替换当前节点，然后删除左子树中的最大值节点
		BSTNode* p = (*bst)->Lchild;
		while (p->Rchild)
		{
			p = p->Rchild;
		}
		int t = p->key;
		DeleteBSTNode(bst, p->key);
		(*bst)->key = t;
	}
	else if ((*bst)->key == x && (*bst)->Lchild != NULL && (*bst)->Rchild == NULL)
	{
		// 删除只有左子树的情况
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = (*bst)->Lchild;
		}
		else
		{
			pre->Rchild = (*bst)->Rchild;
		}
		free((*bst));
		return 1; // 删除成功
	}
	else if ((*bst)->key == x && (*bst)->Lchild == NULL && (*bst)->Rchild != NULL)
	{
		// 删除只有右子树的情况
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = (*bst)->Lchild;
		}
		else
		{
			pre->Rchild = (*bst)->Rchild;
		}
		free((*bst));
		return 1; // 删除成功
	}
	else if ((*bst)->key == x && (*bst)->Lchild == NULL && (*bst)->Rchild == NULL)
	{
		// 删除叶子节点的情况
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = NULL;
		}
		else
		{
			pre->Rchild = NULL;
		}
		free((*bst));
		return 1; // 删除成功
	}
	else if ((*bst)->key > x)
	{
		pre = (*bst);
		DeleteBSTNode(&((*bst)->Lchild), x);
	}
	else
	{
		pre = (*bst);
		DeleteBSTNode(&((*bst)->Rchild), x);
	}
}

int main()
{
	BSTree bst;
	iniBSTree(&bst);
	int arr[10] = { 2,3,1,31,43,41,44,1,4,41 };
	for (int i = 0; i < 10; i++)
	{
		InsertBSTNode(&bst, arr[i]);
	}
	DeleteBSTNode(&bst, 43); // 删除键值为43的节点
	return 0;
}
