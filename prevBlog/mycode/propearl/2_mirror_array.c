/****************************************************************************
  > File Name : 2_mirror_array.c
  > Author  : Arming 
  > Email   : cloudniw1@gmail.com
  > Created : Thu 02 May 2013 09:28:43 PM CST
****************************************************************************/

#include <stdio.h>
int reverse(char *str, int begin, int end);
int main()
{

	//char a[]="abcdefghij";
	char a[]="abc";
	reverse(a, 0, 2);
	printf("%s\n",a);
	return 0;
}

int reverse(char *str, int begin, int end)
{
	if(begin < 0 || end < 0 || begin > end )
		return -1;
	if(begin == end)
		return 0;
	int i = begin, j = end;
	char temp;
	for(i = begin, j = end;i<=j;i++,j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return 0;
}
