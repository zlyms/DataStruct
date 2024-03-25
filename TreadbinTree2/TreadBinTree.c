#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

typedef struct ElemType
{
    int value;
} ElemType;

typedef struct TreeNode
{
    ElemType data;
    struct TreeNode* LChild;
    struct TreeNode* RChild;
    struct TreeNode* parent;
    int ltag, rtag;
} TreeNode, * TreeRoot;

void IniTree(TreeRoot* T)
{
    *T = NULL;
}

int empityTree(TreeRoot T)
{
    if (T == NULL)
    {
        return 0;
    }
    return 1;
}

TreeNode* pre=NULL;//��¼���ڵ�
void creatBinTree(TreeRoot* T, int sz)
{
    if (*T != NULL || sz <= 0)
    {
        return;
    }
    int e = 0;
    int temp = sz;
    scanf_s("%d", &e);
    TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
    if (p == NULL)
    {
        perror("creatBinTree:");
        return;
    }
    p->data.value = e;
    p->LChild = p->RChild = NULL;
    p->rtag = p->ltag = 0;
    p->parent = pre;
    *T = p; 
    pre = p;
    creatBinTree(&((*T)->LChild), --sz);
    pre = *T;
    sz = temp;
    creatBinTree(&((*T)->RChild), --sz);
}
//�ҵ�ֵΪe�Ľڵ�
void locate(TreeRoot T, int e, TreeNode** x)
{
    if (T == NULL)
    {
        return;
    }
    if (T->data.value == e)
    {
        *x = T;
    }
    locate(T->LChild, e, x);
    locate(T->RChild, e, x);
}
//�����bΪ0�����������1���������
int addchild(TreeRoot T, TreeNode* x, TreeRoot T1, int b)
{
    if (b == 0)
    {
        x->LChild = T1;
    }
    else if (b == 1)
    {
        x->RChild = T1;
    }
    return 1;
}
//ͨ���������ɾ��
void postorderdelete(TreeRoot* T)
{
    if (*T == NULL)
    {
        return;
    }
    postorderdelete(&((*T)->LChild));
    postorderdelete(&((*T)->RChild));
    free((*T));
    *T = NULL;
}
//bΪ0ɾ����������1ɾ��������
void deleteChild(TreeRoot T, TreeNode* x, int b)
{
    if (T == NULL)
    {
        return;
    }
    TreeNode* p = NULL;
    if (b == 0)
    {
        p = x->LChild;
        postorderdelete(&p);
        x->LChild = NULL;
    }
    else if (b == 1)
    {
        p = x->RChild;
        postorderdelete(&p);
        x->RChild = NULL;
    }
   
}
// ���ʽڵ㲢������
void visit(TreeNode* p, TreeNode** pre)
{
    if (p->LChild == NULL)//pֻ��ǰ����pΪ��ǰ����λ�ã�
    {
        p->ltag = 1;
        p->LChild = *pre;

    }
    if (*pre != NULL && (*pre)->RChild == NULL)//preֻ�ܺ��
    {
        (*pre)->rtag = 1;
        (*pre)->RChild = p;
    }
    *pre = p;
}
//ǰ�����
void preorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
  
    visit(T, pre);
    if (T->ltag == 0)//ǰ�������������޸ĵ�ǰ�ڵ���ָ��ָ��ǰ���ڷ��ʣ��������ѭ�� ��������Ҫ�жϵ�ǰ��ָ����ָ���ӣ���������
    {                //���䣺���򣬺�����Ϊʲô�������⴦��������ʽڵ���ͨ��ջ��������ָ�룬��������޸�ָ���ٷ��ʵ����               
                     //��ǰ�����޸ĵ�ǰ�ڵ����ָ��֮�󣬷���������
        preorder(T->LChild, pre);
    }
    preorder(T->RChild, pre);
}
//����ǰ������������
void createPreTread(TreeRoot T)
{
    TreeNode* pre = NULL;
    if (T != NULL)
    {
        preorder(T, &pre);
        pre->rtag = 1;
        pre->RChild = NULL;
    }
}
//�������
void inorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
    inorder(T->LChild, pre);
    /*if (T->LChild == NULL)
    {
        T->ltag = 1;
        T->LChild = *pre;

    }
    if (*pre != NULL && T->RChild == NULL)
    {
        T->rtag = 1;
        (*pre)->RChild = T;
    }
   * pre = T;*/
    visit(T, pre);
    inorder(T->RChild, pre);
}
//������������������
void createinTread(TreeRoot T)
{
    TreeNode* pre = NULL;
    if (T != NULL)
    {
        inorder(T, &pre);
        pre->rtag = 1;
        pre->RChild = NULL;
    }
}
//����
void postorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
    postorder(T->LChild, pre);
    postorder(T->RChild, pre);
   // printf("%d  ", T->data.value);
    visit(T, pre);
}
//������������������
void createPostTread(TreeRoot T)
{
    TreeNode* pre = NULL;
    if (T != NULL)
    {
        postorder(T, &pre);
        if (pre->RChild == NULL) //����������һ���ڵ��Ϊ���ڵ㣬��ָ��ָ������������Ҳ����ֻ�����������������⴦��
                                 //ǰ��������������һ���ڵ��Ϊ���ұߵ�Ҷ�ӽڵ㣬��ָ���ΪNULL
        {
            pre->rtag = 1;
        }
    }
}
TreeNode* GetLeft(TreeRoot T)//������Ҷ�ڵ�
{  
        while (T->ltag==0)
            T = T->LChild;
        return T;
}

TreeNode* GetRight(TreeRoot T)//������Ҷ�ڵ�
{
    while (T->rtag == 0)
        T = T->RChild;
    return T;
}
//-------------------------------------����-------------------------------------------
//����������
TreeNode* inNextNode(TreeRoot T)
{
    if (T->rtag == 1)
    {
        return T->RChild;
    }
    else if (T->rtag == 0)//�����    �ң�
                          //�����������ң���
    {
        return GetLeft(T->RChild);
    }

}
//��������������
void Inorder2(TreeRoot T)
{
    TreeNode* p = T;
    for (p = GetLeft(p); p != NULL; p = inNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}

//�������ǰ��
TreeNode* inPreNode(TreeRoot T)
{
    if (T->ltag == 1)
    {
        return T->LChild;
    }
    else if (T->ltag == 0)
    {
        return GetRight(T->LChild);//��    ��    ���ң�
    }                             // ��������ң����ң�
}
//�����������������
void reverseInorder2(TreeRoot T)
{
    TreeNode* p = T;
    for (p = GetRight(p); p != NULL; p = inPreNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//--------------------------------------ǰ��-------------------------------------------
//ǰ��������
TreeNode* preNextNode(TreeRoot T)
{
    if (T->rtag == 1|| T->LChild == NULL)//�������ң�
                                         //�����������ң��ң�
    {
        return T->RChild;
    }
    else if (T->rtag == 0&& T->LChild!=NULL)
    {
        return T->LChild;
    }
}
//ǰ������������
void preorder2(TreeRoot T)
{ 
    for (TreeNode* p = T; p != NULL; p = preNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//ǰ�����ǰ��
TreeNode* prepreNode(TreeRoot T)
{
    TreeNode* p = T->parent;
    if (T->ltag == 1) 
    {
        return T->LChild;
    }
    else if (T->ltag == 0 && p->LChild != NULL&&T==p->RChild)
    {
        return GetRight(p->LChild);
    }
    else 
    {
        return T->parent;
    }
}
//ǰ���������������
void  reversepreorder2(TreeRoot T)
{
    TreeNode* p;
    for (p = GetRight(T); p != NULL; p = prepreNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//---------------------------------����-------------------------------
//����������
TreeNode* postNextNode(TreeRoot T)
{
    TreeNode* p = T->parent;
    if (p == NULL)
        return p;
    if (T->rtag == 1)
    {
        return T->RChild;
    }
    else if (T->rtag == 0 && T==p->LChild&&p->RChild!=NULL&&p->ltag==0)
    {
        return GetLeft(p->RChild);
    }
    else 
    {
        return p;
    }
}
//����������������
void postorder2(TreeRoot T)
{
    TreeNode* p =T;
    for (p->ltag == 1 ? (p = GetLeft(p->RChild)) : (p = GetLeft(p->LChild)); p != NULL; p = postNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//�������ǰ��
TreeNode* postpreNode(TreeRoot T) 
{
    if (T->ltag == 1) 
    {
        return T->LChild;
    }
    else if(T->ltag==0&&T->RChild!=NULL)
    {
        return T->RChild;
    }
    else 
    {
        return T->LChild;
    }
}
//�����������������
void reversePostorder2(TreeRoot T)
{
    for (TreeNode* p = T; p != NULL; p = postpreNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
int main()
{
    TreeRoot T;
    IniTree(&T);
    creatBinTree(&T, 3);
    TreeNode* x;
   locate(T, 1, &x);
   deleteChild(T, x, 0);
   /*createinTread(T);
    Inorder2(T);
    printf("\n");
    reverseInorder2(T);*/
  //  createPreTread(T);
   // preorder2(T);
   // reversepreorder2(T);
   createPostTread(T);
   postorder2(T);
  // reversePostorder2(T);
    return 0;
}
