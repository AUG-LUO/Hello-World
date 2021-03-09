//描述
//N个人围成一圈，从1至N顺序排号。从第一个人开始报数（1至3报数），凡报到3的人失去机会，最后坐在第几位的人能够获得该物资？
//输入
//一行，总人数N。保证 N > 1。
//输出
//一行，获得物资的人的初始排号。
#include <iostream>
using namespace std;
void REMAIN(int* r, int N, int t)
{
	int i, n;
	do {
		n = 0;
		for (i = 0;i < N;i++)
		{
			if (r[i] == 3)//是3的时候跳过操作，并用n记录3的个数
			{
				n++;
				continue;
			}
			r[i] = t;//给不是3的数继续重复赋值123（这里从上一次赋值剩下的最后一个数t开始进行
			t++;
			if (t == 4)
				t = 1;
		}
	} while (N - n != 1);//不断重复记录3的个数，直到只剩下一个数不是3
	for (i = 0;i < N;i++)
		if (r[i] != 3)//输出这个不是3的数的下标
			cout << i + 1;
	return;
}
int main()
{
	int i, t, N;
	cin >> N;
	int* r = new int[N];
	for (i = 0;i < N;i += 3)//给数组循环赋值123，用t记录最后一个值
	{
		*(r + i) = 1;
		t = 1;
		if (i + 1 == N)
		{
			t = 2;
			break;
		}
		if (i + 2 == N)
		{
			t = 3;
			break;
		}
		*(r + i + 1) = 2;
		*(r + i + 2) = 3;
	}
	REMAIN(r, N, t);
	return 0;
}