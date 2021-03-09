#include <iostream>
using namespace std;
int main()
{
	int k, i = 0;
	double s = 0.0;//注意精度
	cin >> k;
	do {
		i++;
		s += (double)1 / i;//注意这里类型转换或者直接写1.0
	} while (s <= k);
	cout << i;
	return 0;
}