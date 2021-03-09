#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int main()
{
	int i, j, n = 0, str_len;
	char* str = new char[50];
	char* str1 = new char[50];
	char* str2 = new char[50];
	gets_s(str, 50);
	str_len = strlen(str);
	for (i = 0;i < str_len;i++)
		if (isalpha(str[i]))
		{
			n++;
			str[i] = tolower(str[i]);
		}
	for (i = 0, j = 0;j < n / 2;i++)
		if (isalpha(str[i]))
		{
			str1[j] = str[i];
			j++;
		}
	str1[j] = '\0';
	for (i = str_len, j = 0;j < n / 2;i--)
		if (isalpha(str[i]))
		{
			str2[j] = str[i];
			j++;
		}
	str2[j] = '\0';
	for (i = 0;i < n / 2;i++)
		if (str1[i] != str2[i])
		{
			cout << 0;
			break;
		}
	if (i == n / 2)
		cout << 1;
	return 0;
}