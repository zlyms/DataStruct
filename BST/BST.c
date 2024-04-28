#include<stdio.h>
#include<stdlib.h>

typedef struct BSTNode
{
	int key;
	struct BSTNode* Lchild, * Rchild;
}BSTNode, * BSTree;

// ��ʼ������������
void iniBSTree(BSTree* bst)
{
	if (*bst == NULL)
	{
		return;
	}
	*bst = NULL;
}

// ���������������ڵ�
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

// �ڶ����������������ڵ�
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

// ȫ�ֱ������ڼ�¼ɾ�������е�ǰ���ڵ�
BSTNode* pre = NULL;

// ɾ�������������еĽڵ�
int DeleteBSTNode(BSTree* bst, int x)
{
	if ((*bst) == NULL)
	{
		return -1; // δ�ҵ�Ҫɾ���Ľڵ�
	}
	else if ((*bst)->key == x && (*bst)->Lchild != NULL && (*bst)->Rchild != NULL)
	{
		// ɾ���������ӽڵ��������ҵ��������е����ֵ�滻��ǰ�ڵ㣬Ȼ��ɾ���������е����ֵ�ڵ�
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
		// ɾ��ֻ�������������
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = (*bst)->Lchild;
		}
		else
		{
			pre->Rchild = (*bst)->Rchild;
		}
		free((*bst));
		return 1; // ɾ���ɹ�
	}
	else if ((*bst)->key == x && (*bst)->Lchild == NULL && (*bst)->Rchild != NULL)
	{
		// ɾ��ֻ�������������
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = (*bst)->Lchild;
		}
		else
		{
			pre->Rchild = (*bst)->Rchild;
		}
		free((*bst));
		return 1; // ɾ���ɹ�
	}
	else if ((*bst)->key == x && (*bst)->Lchild == NULL && (*bst)->Rchild == NULL)
	{
		// ɾ��Ҷ�ӽڵ�����
		if (pre->Lchild == (*bst))
		{
			pre->Lchild = NULL;
		}
		else
		{
			pre->Rchild = NULL;
		}
		free((*bst));
		return 1; // ɾ���ɹ�
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
	DeleteBSTNode(&bst, 43); // ɾ����ֵΪ43�Ľڵ�
	return 0;
}
