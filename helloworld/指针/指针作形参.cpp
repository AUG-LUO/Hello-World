#include <iostream>
using namespace std;
int findmax(int p[][3], int m, int n, int* pRow, int* pCol)//用指针作形参，地址作实参，可改变其所指向地址下内容
{
	int i, j;
	for (i = 0;i < m;i++)
		for (j = 0;j < n;j++)
			if (p[i][j] > p[*pRow][*pCol])
			{
				*pRow = i;
				*pCol = j;
			}
	return p[*pRow][*pCol];
}
int main()
{
	int i, j, a[2][3];
	for (i = 0;i < 2;i++)
		for (j = 0;j < 3;j++)
			cin >> a[i][j];
	int* pRow = new int;//初始化的时候给个空间就好
	int* pCol = new int;
	*pRow = 0;//赋内容的值
	*pCol = 0;
	cout << findmax(a, 2, 3, pRow, pCol);
	cout << " " << *pRow << " " << *pCol;//不能放到一行输出，因为先执行输出语句，后执行函数！！
	return 0;
}