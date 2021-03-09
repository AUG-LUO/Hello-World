#include <iostream>
#include<cstring>
using namespace std;
class Array
{
private:
	int n;
	int* array;
public:
	Array(int n1, int* a1)
	{
		n = n1;
		array = a1;
	}
	void operator^(Array& b)
	{
		int i, j, temp;
		for (i = 0;i < n;i++)
			if (array[i] != ' ')
				if (b.array[i] == 0)
					array[i] = 1;
				else
					for (j = 1, temp = array[i];j < b.array[i];j++)
						array[i] *= temp;
		return;
	}
	void visit(int* a)
	{
		int i;
		for (i = 0;i < n; i++)
			a[i] = array[i];
	}
	void pritf()
	{
		int i;
		for (i = 0;i < n;i++)
			cout << array[i] << ' ';
	}
};
void change(char* a1, int* a)
{
	int i, j;
	int len = strlen(a1);
	for (i = 0, j = 0;i < len;i++)
		if (a1[i] != ' ')
		{
			a[j] = a1[i] - '0';
			j++;
		}
	return;
}


int main()
{
	char* a1 = new char[50];
	char* b1 = new char[50];
	char* c1 = new char[50];
	int* a = new int[10];
	int* b = new int[10];
	int* c = new int[10];
	gets_s(a1, 50);
	gets_s(b1, 50);
	int n = (strlen(a1) + 1) / 2;
	change(a1, a);
	change(b1, b);
	Array t1(n, a), t2(n, b);
	t1^ t2;
	t1.visit(c);
	Array t3(n, c);
	t3.pritf();
	delete[]a1;
	delete[]b1;
	delete[]c1;
	return 0;
}