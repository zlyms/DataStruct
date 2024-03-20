#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996) // ���� Visual Studio �еľ�����Ϣ

// ����ڵ��д洢����������
typedef struct ElemType
{
	int value; // �ڵ�ֵ
} ElemType;

// ����������ڵ�ṹ��
typedef struct TreeNode
{
	ElemType data; // �ڵ�����
	struct TreeNode* LChild; // ���ӽڵ�ָ��
	struct TreeNode* RChild; // ���ӽڵ�ָ��
} TreeNode, * TreeRoot;

// ��ʼ��������
void IniTree(TreeRoot* T)
{
	*T = NULL;
}

// ���������Ƿ�Ϊ��
int empityTree(TreeRoot T)
{
	if (T == NULL)
	{
		return 0; // ����
	}
	return 1; // �ǿ���
}

// �������Ϊsz���������������Ȳ����½ڵ�
void creatBinTree(TreeRoot* T, int sz)
{
	if (*T != NULL || sz <= 0)
	{
		return; // ���������Ѵ��ڻ��ߴ���Ľڵ������Ϸ�����ֱ�ӷ���
	}
	int e;
	int temp = sz;
	scanf_s("%d", &e); // �ӱ�׼�����ȡ�ڵ�ֵ
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode)); // �����ڴ�ռ�
	if (p == NULL)
	{
		perror("creatBinTree:"); // �ڴ����ʧ��ʱ���������Ϣ
		return;
	}
	p->data.value = e; // ���ڵ�ֵ�����½ڵ��������
	p->LChild = p->RChild = NULL; // �������ӽڵ�ָ����Ϊ��
	*T = p; // ����ǰ�ڵ�ָ�븳�����ڵ�ָ��
	creatBinTree(&((*T)->LChild), --sz); // �ݹ鴴��������
	sz = temp;//����sz
	creatBinTree(&((*T)->RChild), --sz); // �ݹ鴴��������
}

// �ڶ������ж�λָ���ڵ�
void locate(TreeRoot T, int e, TreeNode** x)
{
	if (T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	if (T->data.value == e)
	{
		*x = T; // ���ҵ���Ŀ��ֵ��ȵĽڵ㣬�򽫽ڵ��ַ����ָ��ָ��
	}
	locate(T->LChild, e, x); // ���������м�������
	locate(T->RChild, e, x); // ���������м�������
}

// ����ӽڵ�
int addchild(TreeRoot T, TreeNode* x, TreeRoot T1, int b)
{
	if (b == 0)
	{
		x->LChild = T1; // ������ӽڵ�
	}
	else if (b == 1)
	{
		x->RChild = T1; // ������ӽڵ�
	}
	return 1;
}

// �������ɾ���ڵ㼰���ӽڵ�
void postorderdelete(TreeRoot* T)
{
	if (*T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	postorderdelete(&((*T)->LChild)); // �ݹ�ɾ��������
	postorderdelete(&((*T)->RChild)); // �ݹ�ɾ��������
	free((*T)); // �ͷŵ�ǰ�ڵ���ڴ�ռ�
	*T = NULL; // ����ǰ�ڵ�ָ����Ϊ��
}

// ɾ���ӽڵ�
void deleteChild(TreeRoot T, TreeNode* x, int b)
{
	if (T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	TreeNode* p = NULL;
	if (b == 0)
	{
		p = x->LChild; // ��ȡ���ӽڵ�ָ��
	}
	else if (b == 1)
	{
		p = x->RChild; // ��ȡ���ӽڵ�ָ��
	}
	postorderdelete(&p); // �������ɾ���ӽڵ㼰���ӽڵ�
}

// �������
void preorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	printf("%d  ", T->data.value); // �����ǰ�ڵ��ֵ
	preorder(T->LChild); // �ݹ����������
	preorder(T->RChild); // �ݹ����������
}

// �������
void inorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	inorder(T->LChild); // �ݹ����������
	printf("%d  ", T->data.value); // �����ǰ�ڵ��ֵ
	inorder(T->RChild); // �ݹ����������
}

// �������
void postorder(TreeRoot T)
{
	if (T == NULL)
	{
		return; // ����Ϊ�գ���ֱ�ӷ���
	}
	postorder(T->LChild); // �ݹ����������
	postorder(T->RChild); // �ݹ����������
	printf("%d  ", T->data.value); // �����ǰ�ڵ��ֵ
}

// ������
int main()
{
	TreeRoot T;
	IniTree(&T); // ��ʼ��������
	creatBinTree(&T, 3); // ����������
	TreeNode* x;
	locate(T, 1, &x); // �ڶ������ж�λָ���ڵ�
	//preorder(T); // �������
	//printf("\n");
	//inorder(T); // �������
	//printf("\n");
	//postorder(T); // �������
	//printf("\n");
	deleteChild(T, x, 0); // ɾ��ָ���ڵ�����ӽڵ�
	return 0;
}
