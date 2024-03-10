#include<stdio.h>

int main() 
{
	char arr[] = "IOIOIOIOIIIOOOOO";
	int i = 0;
	int tap=0;
	while (arr[i]) 
	{
		if (arr[i] == 'I') 
		{
			tap++;
		}
		else 
		{
			tap--;
		}
		if (tap < 0) 
		{
			printf("s");
			break;
		}
	}
	return 0;
}