#include <iostream>
using namespace std;
int find_same(char* str1, char* str2)
{
	int i;
	for (i = 0;str1[i] != '\0' && str2[i] != '\0';i++)
		if (str1[i] != str2[i])
			break;
	if (i == 0)
		return 0;
	else
		return i;
}
int main()
{
	int i, n1, n2, n3;
	char* str1 = new char[50];
	char* str2 = new char[50];
	char* str3 = new char[50];
	cin >> str1 >> str2 >> str3;
	n1 = find_same(str1, str2);
	n2 = find_same(str2, str3);
	n3 = find_same(str1, str3);
	if (!n1 || !n2 || !n3)
		cout << "NONEXISTENT";
	else
	{
		if (n1 > n2)
			n1 = n2;
		if (n1 > n3)
			n1 = n3;
	}
	for (i = 0;i < n1;i++)
		cout << str1[i];
	return 0;
}