#include <iostream>
#define n 50
using namespace std;
int main()
{
	int i, j, l, r, a, N, s[n][n];//由于是数组，r等关于下标的计算均有-1的运算存在【勿忘】
	cin >> N;
	for (r = 0, a = 1;r < N - 1;r++)//r为由外而内的圈数，循环进行到最里圈时停止
									//a为第r圈起始数
	{
		l = N - 2 * (r + 1);//l为第r圈的边长（即减去两端的长度）
		for (i = r;i >= r && i < N - r;i++)//该循环通过一圈一圈不断进行给第r圈赋值直到赋值到最里圈
			for (j = r;j >= r && j < N - r;j++)
				if (i == N - 1 - r)//第r圈的下边
					s[i][j] = a + l + 1 - (j - r);
				else if (j == 0 + r)//第r圈的左边
					s[i][j] = a + 2 * (l + 1) - (i - r);
				else if (i == 0 + r)//第r圈的上边
					s[i][j] = a + 2 * (l + 1) + (j - r);
				else if (j == N - 1 - r)//第r圈的右边
					s[i][j] = a + 3 * (l + 1) + (i - r);
		a = a + (4 * l + 4);//下一圈的起始值：增加一圈下来赋的值
	}
	if (N % 2 != 0)//奇数的螺旋最里是一个数
		s[N / 2][N / 2] = N * N;
	for (i = 0;i < N;i++)//赋值完毕输出即可
	{
		for (j = 0;j < N;j++)
			cout << s[i][j] << " ";
		cout << endl;
	}
	return 0;
}