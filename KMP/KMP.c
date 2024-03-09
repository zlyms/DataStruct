//#include<stdio.h>
//#define M 10
//void IniNext(char* next)
//{
//	next[0] = -1;
//	next[1] = 0;
//	next[2] = 1;
//}
//void Next(char *arr, char* next)
//{
//	if (arr == NULL) 
//	{
//		printf("�մ�\n");
//		return;
//	}
//	int i;
//	int front = 0;
//	int rear = front+1;	
//	for (i = 1; i < M; i++) 
//	{
//		while (rear!=i) 
//		{
//		
//		}
//	}
//}
//int main() 
//{
//	char arr[M] = " abababab";
//	char next[M];
//	IniNext(next);
//	return 0;
//
//}
#include <stdio.h>   
#define M 10
void getNext(char* S, int len, int* next)
{
    next[1] = 0;
    int i = 1;
    int j = 0;
    while (i < len)
    {
        if (j == 0 || S[i] == S[j])//i����next�±��ģʽ���±꣬j�洢�ϴ�ƥ��ɹ�����һλ�ã������ǰλ�������ƥ��λ�õ���һλ�������ζ����һλ���غϵģ�����ǰ��׺+1
        {
            i++;
            j++;
            next[i] = j;
        }
        else//��������������ƺ��ҹ�ȥ��Ҳ����ģʽ�����Ӵ��Ĺ���ǰ��׺��һλ��Ҳ�����غϲ��ֺ�һλ��ѭ�������ҵ���ǰλ���ܹ�ƥ���λ��
        {
            j = next[j];
        }
    }
}
void NextVal(char*modle,int*nextVal,int *next,int LM) 
{
    nextVal[1] = 0;
    for (int j = 2; j <= LM; j++) 
    {
        if (modle[j] == modle[next[j]]) //���ģʽ����ǰλ�÷�����ƥ�䣬��ζ�������غϲ��ֵĺ�һλҲһ�����ǵ�ǰ�ַ���
                                        //����һ�����ֵ�ǰλ������ζ�������غϲ��ֵĺ�һλ���,���ص���һ�غ�λ�ú�һλ
                                        //����Ϊ���ڵ�ǰλ��֮ǰ���Ѿ����к��ˣ����Կ���ֱ��������ͬ���ŵ�λ��
        {
            nextVal[j] = nextVal[next[j]];
        }
        else 
        {
            nextVal[j] = next[j];
        }
    }
}
int KMP(char* S, char* model, int* next, int LA, int LM)
{
    int i = 1;
    int j = 1;
    while (i <= LA && j <= LM)//���j�ߵ�ģʽ��β����ζ��ƥ��ɹ������i�ߵ�β��jû���ߵ�β����ζ��ƥ��ʧ��
    {
        if (j == 0 || S[i] == model[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > LM) 
    {
        return i - j;//����ƥ��λ���±�
    }
    else 
    {
        return 0;
    }

}
int main()
{
    char arr[] = " bababab";
    char modle[] = " aaaab";
    int next[M] = { 0 };
    int nextVal[M] = { 0 };
    int sizeS = sizeof(arr) / sizeof(arr[0]) - 2;
    int sizeM = sizeof(modle) / sizeof(modle[0]) - 2;
    getNext(modle, sizeM, next);
    NextVal(modle,nextVal,next,sizeM);
    int i=KMP(arr,modle,next,sizeS,sizeM);
    return 0;
}
