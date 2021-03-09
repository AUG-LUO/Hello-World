//求解？？？+？？？=？？？成立，填入1~9
#include <iostream>
#include<cstring>
using namespace std;
int a[10], book[10], total = 0;
void dfs(int step) {//第step个盒子的尝试
	int i;
	if (step == 10) {//边界判断
		if (a[1] * 100 + a[2] * 10 + a[3] + a[4] * 100 + a[5] * 10 + a[6] == a[7] * 100 + a[8] * 10 + a[9])
		{
			total++;
			printf("%d%d%d+%d%d%d=%d%d%d\n", a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
			return;
		}
	}
	for (i = 1;i <= 9;i++)//尝试第i张卡
	{
		if (book[i] == 0)
		{
			a[step] = i;
			book[i] = 1;

			dfs(step + 1);//走到下一个盒子
			book[i] = 0;//退回的时候要取回卡片
		}
	}
	return;
}
int main() {
	dfs(1);
	printf("total=%d", total / 2);
	return 0;
}