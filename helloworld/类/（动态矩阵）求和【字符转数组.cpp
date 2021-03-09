#include <iostream>
#include<cstring>
using namespace std;
class matrix
{
private:
	int row, col;
	int** array;
public:
	matrix(int** a1, int r1, int c1)
	{
		array = a1;
		row = r1;
		col = c1;
	}
	void same(matrix b)
	{
		if (b.row == row && b.col == col)
			add(b);
		else
			cout << -1;
		return;
	}
	void add(matrix b)
	{
		int i, j;
		int** c = new int* [10];
		for (i = 0;i < 10;i++)
			c[i] = new int[50];
		for (i = 0;i < row;i++)
			for (j = 0;j < col;j++)
				c[i][j] = array[i][j] + b.array[i][j];
		for (i = 0;i < row;i++)
		{
			for (j = 0;j < col;j++)
				cout << c[i][j] << " ";
			cout << endl;
		}
		return;
	}
};
int col(char a[][50])
{
	int i, c = 1;
	for (i = 0;a[0][i] != '\n';i++)
		if (a[0][i] == ' ')
			c++;
	return c;
}
void addn(char a[][50], int r, int n[10])
{
	int i;
	for (i = 0;i < r;i++)
		a[i][n[i]] = '\n';
}
int** change(char a[][50], int r, int c)
{
	int i, j, t = 0, n, temp;
	int** num = new int* [10];
	for (i = 0;i < 10;i++)
		num[i] = new int[20];
	int** array = new int* [10];
	for (i = 0;i < 10;i++)
		array[i] = new int[20];
	for (i = 0;i < r;i++)
		for (j = 0, t = 0;t < c;j++)
		{
			for (n = 0;a[i][j] != ' ' && a[i][j] != '\n'; j++)
				n++;
			num[i][t] = n;
			t++;
		}

	for (i = 0;i < r;i++)
		for (j = 0;a[i][j] != '\n';j++)
			if (a[i][j] != ' ')
				a[i][j] -= '0';
	for (i = 0;i < r;i++)
		for (j = 0, t = 0;t < c;j++, t++)
			if (num[i][t] == 2)
			{
				array[i][t] = a[i][j] * 10 + a[i][j + 1];
				j += 2;
			}
			else
			{
				array[i][t] = a[i][j];
				j++;
			}
	return array;
}

int main()
{
	int i, r1, c1, r2, c2;
	int* last1 = new int[10];
	int* last2 = new int[10];//用于每行加\n
	char t1[10][50], t2[10][50];//用于输入
	t1[0][0] = 0;t2[0][0] = 0;

	for (i = 0;(t1[i][0] = cin.get()) != '\n';i++)
	{
		cin.getline(t1[i] + 1, 20, '\n');
		last1[i] = strlen(t1[i]);
	}
	r1 = i;

	for (i = 0;(t2[i][0] = cin.get()) != EOF;i++)
	{
		cin.getline(t2[i] + 1, 20, '\n');
		last2[i] = strlen(t2[i]);
	}
	r2 = i;

	addn(t1, r1, last1);
	addn(t2, r2, last2);

	c1 = col(t1);
	c2 = col(t2);

	int** a1 = new int* [10];
	for (i = 0;i < 10;i++)
		a1[i] = new int[20];

	int** b1 = new int* [10];
	for (i = 0;i < 10;i++)
		b1[i] = new int[20];

	a1 = change(t1, r1, c1);
	b1 = change(t2, r2, c2);

	matrix a(a1, r1, c1), b(b1, r2, c2);
	a.same(b);
	return 0;
}