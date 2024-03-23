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
    *T = p;
    creatBinTree(&((*T)->LChild), --sz);
    sz = temp;
    creatBinTree(&((*T)->RChild), --sz);
}

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
    }
    else if (b == 1)
    {
        p = x->RChild;
    }
    postorderdelete(&p);
}

void visit(TreeNode* p, TreeNode** pre)
{
    if (p->LChild == NULL)//p只管前驱（p为当前访问位置）
    {
        p->ltag = 1;
        p->LChild = *pre;

    }
    if (*pre != NULL && (*pre)->RChild == NULL)//pre只管后继
    {
        (*pre)->rtag = 1;
        (*pre)->RChild = p;
    }
    *pre = p;
}
void preorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
    printf("%d  ", T->data.value);
    visit(T, pre);
    if (T->ltag == 0)//前序线索树会先修改当前节点左指针指向前驱在访问，会产生死循环 ，所以需要判断当前左指针是指向孩子，还是线索
    {                //补充：后序，和中序为什么不用特殊处理，后序访问节点是通过栈，而不是指针，不会存在修改指针再访问的情况               
                     //而前序，是修改当前节点的左指针之后，访问右子树
        preorder(T->LChild, pre);
    }
    preorder(T->RChild, pre);
}
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
void postorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
    postorder(T->LChild, pre);
    postorder(T->RChild, pre);
    printf("%d  ", T->data.value);
    visit(T, pre);
}
void createPostTread(TreeRoot T)
{
    TreeNode* pre = NULL;
    if (T != NULL)
    {
        postorder(T, &pre);
        if (pre->RChild == NULL) //后序遍历最后一个节点必为根节点，右指针指向右子树，但也可能除非只有左子树所以特殊处理
                                 //前序，中序遍历的最后一个节点必为最右边的叶子节点，右指针必为NULL
        {
            pre->rtag = 1;
        }
    }
}

int main()
{
    TreeRoot T;
    IniTree(&T);
    creatBinTree(&T, 3);
    //TreeNode* x;
    //locate(T, 1, &x);
    //deleteChild(T, x, 0);
    createPostTread(T);
    return 0;
}
