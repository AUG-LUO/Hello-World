#include <iostream>
#include<string>
using namespace std;
int find(char* str1, char* str2)
{
	int i, j, t;
	for (i = 0;str1[i] != '\0';i++)
		if (str1[i] == str2[0])
		{
			for (j = 0, t = i;str2[j] != '\0';j++, t++)
				if (str2[j] != str1[t])
					break;
			if (str2[j] == '\0')
				return i;
		}
	return -1;
}
int main()
{
	char* str1 = new char[20];
	char* str2 = new char[20];
	cin >> str1;
	cin >> str2;
	cout << find(str1, str2);
	return 0;
}

//���װ棺��������г��ִ�������һ�γ�������ĸλ�ã��Ҳ��ִ�Сд
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int i, j, t;
	int n = 0, l_c, l_str, where[3000];//����Ҫ�����㹻����ò�ҪԽ��
	char* str = new char[11];
	char* c = new char[1000001];
	gets_s(str, 11);//������gets_s
	gets_s(c, 1000001);
	l_str = strlen(str);//�ó����жϸ�����
	l_c = strlen(c);
	for (i = 0;str[i] != '\0';i++)
		str[i] = tolower(str[i]);
	for (i = 0;i < l_c;i++)
		c[i] = tolower(c[i]);
	for (i = -1;i < l_c;i++)
		if ((c[i] == ' ' || i == -1) && c[i + 1] == str[0])
		{
			for (j = 0, t = i + 1;j < l_str;j++, t++)
				if (str[j] != c[t])
					break;
			if (j == l_str && (c[t] == ' ' || c[t] == '\0'))//�ո�ascll��32��α�㲻ͬ
			{
				where[n] = i + 1;
				n++;
			}
		}
	if (n)
		cout << n << ' ' << where[0];
	else
		cout << -1;
	delete[]str;
	delete[]c;
	return 0;
}