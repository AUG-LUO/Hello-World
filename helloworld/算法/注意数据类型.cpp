#include <iostream>
using namespace std;
int main()
{
	int k, i = 0;
	double s = 0.0;//ע�⾫��
	cin >> k;
	do {
		i++;
		s += (double)1 / i;//ע����������ת������ֱ��д1.0
	} while (s <= k);
	cout << i;
	return 0;
}