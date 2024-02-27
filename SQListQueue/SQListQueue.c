#include <stdio.h>

#define CAPACITY 10 // �����������Ϊ10
typedef int Elemtype; // ����Ԫ������Ϊ����
typedef struct
{
    Elemtype data[CAPACITY]; // ������������
    int rear, front; // ����β����ͷ��ָ��
} SQqueue; // ����˳����нṹ��

void IniSQquee(SQqueue* sq)
{
    sq->front = 0; // ��ʼ������ͷָ��
    sq->rear = 0; // ��ʼ������βָ��
}

int EnQueue(SQqueue* sq, Elemtype e)
{
    if ((sq->rear + 1) % CAPACITY == sq->front) // �����������
    {
        printf("��������\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    sq->data[sq->rear] = e; // ��Ԫ�ز����β
    sq->rear = (sq->rear + 1) % CAPACITY; // ���¶�βָ��
    return 1; // ���سɹ�
}

int isempty(SQqueue* sq)
{
    if (sq->front == sq->rear) // �������ͷβָ�����
    {
        return 1; // ����Ϊ��
    }
    else
    {
        return 0; // ���зǿ�
    }
}

int deQueue(SQqueue* sq, int* x)
{
    if (isempty(sq)) // �������Ϊ��
    {
        printf("�ӿ�\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    *x = sq->data[sq->front]; // ��ȡ��ͷԪ��
    sq->front = (sq->front + 1) % CAPACITY; // ���¶�ͷָ��
    return 1; // ���سɹ�
}

int Gethead(SQqueue* sq, int* x)
{
    if (isempty(sq)) // �������Ϊ��
    {
        printf("�ӿ�\n"); // �����ʾ��Ϣ
        return 0; // ����ʧ��
    }
    *x = sq->data[sq->front]; // ��ȡ��ͷԪ��
    return 1; // ���سɹ�
}

int main()
{
    SQqueue sq; // ����˳����б���
    int x; // �������ͱ���x
    IniSQquee(&sq); // ��ʼ������
    EnQueue(&sq, 5); // ���Ԫ��5
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    EnQueue(&sq, 3); // ���Ԫ��3
    //deQueue(&sq, &x); // ���ӣ���������Ԫ�ش洢��x��
    Gethead(&sq, &x); // ��ȡ��ͷԪ�أ�������洢��x��
    printf("%d\n", x); // �����ͷԪ��
    return 0; // ���سɹ�
}
