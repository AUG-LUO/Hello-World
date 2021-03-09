#include <iostream>
using namespace std;
int main()
{
	int i;
	char* str1 = new char[100];
	char* str2 = new char[100];
	cin >> str1;
	for (i = 0;str1[i] != '\0';i++)
		str2[i] = str1[i];
	str2[i] = '\0';
	cout << str2;
	return 0;
}