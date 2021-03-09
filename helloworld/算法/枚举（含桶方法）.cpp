#include <iostream>
#include<cstdio>
using namespace std;
int main()
{
	int i, book[10], num[10], sum;
	for (num[1] = 1; num[1] < 10; num[1]++)
		for (num[2] = 1; num[2] < 10; num[2]++)
			for (num[3] = 1; num[3] < 10; num[3]++)
				for (num[4] = 1; num[4] < 10; num[4]++)
					for (num[5] = 1; num[5] < 10; num[5]++)
						for (num[6] = 1; num[6] < 10; num[6]++)
							for (num[7] = 1; num[7] < 10; num[7]++)
								for (num[8] = 1; num[8] < 10; num[8]++)
									for (num[9] = 1; num[9] < 10; num[9]++)//分别是九个位数，让他们从1到9循环
									{
										for (i = 1;i < 10;i++)
											book[i] = 0;
										for (i = 1;i < 10;i++)
											book[num[i]] = 1;//将用到的数字置1
										sum = 0;//记得每次置零（有些操作是需要每次循环做的）
										for (i = 1;i < 10;i++)
											sum += book[i];//算一下每出一组数是否9个数都用到了
										if (sum == 9 && 2 * (num[1] * 100 + num[2] * 10 + num[3]) == (num[4] * 100 + num[5] * 10 + num[6]) && 3 * (num[1] * 100 + num[2] * 10 + num[3]) == (num[7] * 100 + num[8] * 10 + num[9]))
											printf("%d%d%d %d%d%d %d%d%d\n", num[1], num[2], num[3], num[4], num[5], num[6], num[7], num[8], num[9]);
									}

	return 0;
}