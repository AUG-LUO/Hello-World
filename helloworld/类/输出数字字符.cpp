//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include <iostream>
#include<string.h>
using namespace std;
class string_Integer
{
private:
	char* str;
public:
	string_Integer(char* str1)
	{
		str = str1;
	}
	void transfer()
	{
		int i, j;
		char* temp = new char[50];
		for (i = 0, j = 0;str[i];i++)
			if (isdigit(str[i]))
			{
				temp[j] = str[i];
				j++;
			}
		temp[j] = 0;
		if (temp[0] == '0' && strlen(temp) > 1)
			for (i = 0;temp[i];i++)
				temp[i] = temp[i + 1];
		strcpy(str, temp);
	}
	char* show()
	{
		return str;
	}
};
int main()
{
	char* str1 = new char[50];
	cin >> str1;
	string_Integer s(str1);
	s.transfer();
	cout << s.show();
	return 0;
}