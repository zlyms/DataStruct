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
//		printf("空串\n");
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
        if (j == 0 || S[i] == S[j])//i对于next下标和模式串下标，j存储上次匹配成功的下一位置，如果当前位置与最近匹配位置的下一位置相等意味着又一位是重合的，公共前后缀+1
        {
            i++;
            j++;
            next[i] = j;
        }
        else//如果不是沿着门牌号找过去，也就是模式串的子串的公共前后缀后一位，也就是重合部分后一位，循环往复找到当前位置能够匹配的位置
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
        if (modle[j] == modle[next[j]]) //如果模式串当前位置发生不匹配，意味着与其重合部分的后一位也一定不是当前字符，
                                        //所以一旦发现当前位置与意味着与其重合部分的后一位相等,返回到下一重合位置后一位
                                        //又因为，在当前位置之前的已经排列好了，所以可以直接跳过相同符号的位置
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
    while (i <= LA && j <= LM)//如果j走到模式串尾部意味着匹配成功，如果i走到尾部j没有走到尾部意味着匹配失败
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
        return i - j;//返回匹配位置下标
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
