#include <iostream>
#include<string.h>
using namespace std;
int main()
{
	char* str1 = new char[20];
	char* str2 = new char[20];
	char* str = new char[40];
	cin >> str1;
	cin >> str2;
	int n1, n2, i, j;
	n1 = strlen(str1);
	n2 = strlen(str2);
	for (i = 0;i < n1 / 2;i++)
		str[i] = str1[i];
	for (;i < n2 + n1 / 2;i++)
		str[i] = str2[i - n1 / 2];
	if (n1 % 2 == 0)
		for (j = n1 / 2;j < n1 + 1;j++, i++)
			str[i] = str1[j];
	else
		for (j = n1 / 2 + 1;j < n1 + 1;j++, i++)
			str[i] = str1[j];
	cout << str;
	return 0;
}