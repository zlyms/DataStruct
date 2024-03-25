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

TreeNode* pre=NULL;//记录父节点
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
//找到值为e的节点
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
//添加树b为0添加右子树，1添加左子树
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
//通过后序遍历删除
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
//b为0删除右子树，1删除左子树
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
// 访问节点并线索化
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
//前序遍历
void preorder(TreeRoot T, TreeNode** pre)
{
    if (T == NULL)
    {
        return;
    }
  
    visit(T, pre);
    if (T->ltag == 0)//前序线索树会先修改当前节点左指针指向前驱在访问，会产生死循环 ，所以需要判断当前左指针是指向孩子，还是线索
    {                //补充：后序，和中序为什么不用特殊处理，后序访问节点是通过栈，而不是指针，不会存在修改指针再访问的情况               
                     //而前序，是修改当前节点的左指针之后，访问右子树
        preorder(T->LChild, pre);
    }
    preorder(T->RChild, pre);
}
//创建前序线索二叉树
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
//中序遍历
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
//创建中序线索二叉树
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
//后序
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
//创建后续线索二叉树
void createPostTread(TreeRoot T)
{
    TreeNode* pre = NULL;
    if (T != NULL)
    {
        postorder(T, &pre);
        if (pre->RChild == NULL) //后序遍历最后一个节点必为根节点，右指针指向右子树，但也可能只有左子树，所以特殊处理
                                 //前序，中序遍历的最后一个节点必为最右边的叶子节点，右指针必为NULL
        {
            pre->rtag = 1;
        }
    }
}
TreeNode* GetLeft(TreeRoot T)//找最左叶节点
{  
        while (T->ltag==0)
            T = T->LChild;
        return T;
}

TreeNode* GetRight(TreeRoot T)//找最右叶节点
{
    while (T->rtag == 0)
        T = T->RChild;
    return T;
}
//-------------------------------------中序-------------------------------------------
//中序遍历后继
TreeNode* inNextNode(TreeRoot T)
{
    if (T->rtag == 1)
    {
        return T->RChild;
    }
    else if (T->rtag == 0)//（左根    右）
                          //（左根（左根右））
    {
        return GetLeft(T->RChild);
    }

}
//中序线索树遍历
void Inorder2(TreeRoot T)
{
    TreeNode* p = T;
    for (p = GetLeft(p); p != NULL; p = inNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}

//中序遍历前驱
TreeNode* inPreNode(TreeRoot T)
{
    if (T->ltag == 1)
    {
        return T->LChild;
    }
    else if (T->ltag == 0)
    {
        return GetRight(T->LChild);//（    左    根右）
    }                             // （（左根右）根右）
}
//中序线索树逆向遍历
void reverseInorder2(TreeRoot T)
{
    TreeNode* p = T;
    for (p = GetRight(p); p != NULL; p = inPreNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//--------------------------------------前序-------------------------------------------
//前序遍历后继
TreeNode* preNextNode(TreeRoot T)
{
    if (T->rtag == 1|| T->LChild == NULL)//（根左右）
                                         //（根（根左右）右）
    {
        return T->RChild;
    }
    else if (T->rtag == 0&& T->LChild!=NULL)
    {
        return T->LChild;
    }
}
//前序线索树遍历
void preorder2(TreeRoot T)
{ 
    for (TreeNode* p = T; p != NULL; p = preNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//前序遍历前驱
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
//前序线索树逆向遍历
void  reversepreorder2(TreeRoot T)
{
    TreeNode* p;
    for (p = GetRight(T); p != NULL; p = prepreNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//---------------------------------后序-------------------------------
//后序遍历后继
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
//后序序线索树遍历
void postorder2(TreeRoot T)
{
    TreeNode* p =T;
    for (p->ltag == 1 ? (p = GetLeft(p->RChild)) : (p = GetLeft(p->LChild)); p != NULL; p = postNextNode(p))
    {
        printf("%d  ", p->data.value);
    }
}
//后序遍历前序
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
//后序线索树逆向遍历
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
