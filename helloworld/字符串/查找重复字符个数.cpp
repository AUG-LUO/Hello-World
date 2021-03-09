#include <iostream>
#include<string.h>
using namespace std;
int main()
{
	char* str = new char[50];
	char* substr = new char[50];
	int i, j, n = 0, substr_len;
	cin >> str;
	cin >> substr;
	substr_len = strlen(substr);
	for (i = 0;str[i] != '\0';i++)
		if (str[i] == substr[0])
		{
			for (j = 0;substr[j] != '\0';j++)
				if (substr[j] != str[i + j])
					break;
			if (j == substr_len)
				n++;
		}
	cout << n;
	return 0;
}