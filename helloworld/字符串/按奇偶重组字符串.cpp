#include <iostream>
#include<cstring>
using namespace std;
char* chongzu(char* odd, char* even)
{
	int i, j, len1, len2;
	char* str = new char[20];
	len1 = strlen(odd);
	len2 = strlen(even);
	for (i = 0, j = 0;i < len1;i += 2, j++)
		str[j] = odd[i];
	for (i = 1;i < len2;i += 2, j++)
		str[j] = even[i];
	str[j] = '\0';
	return str;
}
int main()
{
	char* str1 = new char[20];
	char* str2 = new char[20];
	cin >> str1;
	cin >> str2;
	cout << chongzu(str1, str2);
	return 0;
}