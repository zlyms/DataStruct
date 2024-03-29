#include<stdio.h>
#define MAXSIZE 15
#pragma warning(disable:4996) // ����4996���棬�þ���ͨ���ǹ���ʹ���˱���Ϊ����ȫ�ĺ������ߺ����ĵ��ò����ϱ�׼�淶

typedef char Elemtype; // �������ڵ������ݵ�����

typedef struct
{
	Elemtype data; // �ڵ��д洢������
	int parent;    // ���ڵ���±꣬-1��ʾ�ýڵ�Ϊ���ڵ�
} TreeNode; // ���ڵ�Ľṹ�嶨��

typedef struct 
{
	TreeNode nodes[MAXSIZE]; // �洢�ڵ������
	int n;                   // ��ǰ���нڵ������
} PTree; // ���鼯�Ľṹ�嶨��

// ��ʼ�����鼯�����ڵ�������Ϊ0�����и��ڵ��±���Ϊ-1����ʾ���ڵ㣩
void IniPTree(PTree* PT)
{
	if (PT == NULL) // ����������Ϊ��ָ�룬ֱ�ӷ���
	{
		return;
	}
	PT->n = 0; // ���ڵ�������ʼ��Ϊ0
	for (int i = 0; i < MAXSIZE; i++) // �������нڵ����飬�����ڵ��±��ʼ��Ϊ-1
	{
		PT->nodes[i].parent = -1;
	}
}

Elemtype e = 'A'; // ����һ��ȫ�ֱ��� e ���ڳ�ʼ���ڵ�����

// �������鼯
void CreatePTree(PTree* PT)
{
	if (PT == NULL) // ����������Ϊ��ָ�룬ֱ�ӷ���
	{
		return;
	}	
	int switchoff = 1; // �����Ƿ������ӽڵ�Ŀ���
	int temp = PT->n; // ��ʱ���������ڱ��浱ǰ�ڵ���±�
	int size = 0; // ��¼��ǰ���Ͻڵ����
    int root = PT->n; // ��¼���ڵ���±�
	while (switchoff != 1 && PT->n < MAXSIZE) // ѭ����ȡ�û����룬ֱ������Ϊ1���߽ڵ������ﵽ����
	{
		scanf("%d",&switchoff); // ����һ�����������ڿ����Ƿ������ӽڵ�0������ӣ�1�˳�
		PT->nodes[PT->n].parent = temp; // ���õ�ǰ�ڵ�ĸ��ڵ��±�Ϊtemp
		PT->nodes[PT->n++].data = e; // ���õ�ǰ�ڵ������Ϊe�������ڵ�������1
		size--; // �ڵ��С��1
		if (switchoff == 0) // �������Ϊ0����temp����Ϊ��ǰ�ڵ���±�
		{
			temp = PT->n - 1;
		}
		e++; // e����1��������һ���ڵ�����ݳ�ʼ��
	}
	if (root < PT->n) // ������ڸ��ڵ�
		PT->nodes[root].parent = size; // ���ø��ڵ�ĸ��ڵ��±�Ϊsize
}

// ���ҽڵ����ڼ��ϵĸ��ڵ�
int find(PTree* PT, int x)
{
	while (PT->nodes[x].parent >= 0) // ����ڵ�x�ĸ��ڵ��±���ڵ���0����˵��x���Ǹ��ڵ�
		x = PT->nodes[x].parent; // ��x����Ϊ�丸�ڵ��±꣬��������
	return x; // ����x����Ϊ���ڵ���±�
}

// �Ľ��Ĳ��Һ�����ͬʱʵ����·��ѹ��
int findImporve(PTree* PT, int x)
{
	int root = x; // ��ʼ�����ڵ�Ϊx
	if (PT == NULL) // �����Ϊ�գ�ֱ�ӷ���
	{
		return;
    }
	while (PT->nodes[root].parent >= 0) // ѭ��ֱ���ҵ����ڵ�
	{
		root = PT->nodes[root].parent; // ���¸��ڵ�Ϊ�丸�ڵ�
	}
	while (x != root) // ѭ��ֱ���ڵ�x�ĸ��ڵ�Ϊ���ڵ�
	{
		int t = PT->nodes[x].parent; // ����ڵ�x�ĸ��ڵ�
		PT->nodes[x].parent = root; // ���ڵ�x�ĸ��ڵ����Ϊ���ڵ�
		x = t; // ����xΪ�丸�ڵ㣬����ѹ��·��
	}
	return root; // ���ظ��ڵ���±�
}

// �ϲ���������
void uniontree(PTree* PT, int root1, int root2)
{
	if (root1 == root2) // ����������ڵ���ͬ������Ҫ�ϲ���ֱ�ӷ���
	{
		return;
	}
	if (PT->nodes[root1].parent < PT->nodes[root2].parent) // С��������ϲ�
	{
		PT->nodes[root2].parent = root1; // �����ڵ�2�ĸ��ڵ��±����Ϊ���ڵ�1���±�
	}
	else // ����
	{
		PT->nodes[root1].parent = root2; // �����ڵ�1�ĸ��ڵ��±����Ϊ���ڵ�2���±�
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