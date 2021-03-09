#include <iostream>
using namespace std;
int main()
{
	int i, j, t = 0, m, n;
	cin >> m >> n;
	int** a = new int* [m];
	for (i = 0;i < m;i++)
		a[i] = new int[n];
	int* b = new int[m * n];
	int* c = new int[m * n];
	for (i = 0;i < m;i++)
		for (j = 0;j < n;j++)
		{
			cin >> a[i][j];
			if (a[i][j] == 0)
			{
				b[t] = i;
				c[t] = j;
				t++;
			}
		}
	for (t--;t >= 0;t--)
	{
		for (i = 0;i < n;i++)
			a[b[t]][i] = 0;
		for (j = 0;j < m;j++)
			a[j][c[t]] = 0;
	}
	for (i = 0;i < m;i++)
	{
		for (j = 0;j < n;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	delete[](a);
	delete[](b);
	delete[](c);
	return 0;
}