#include <iostream>
using namespace std;
void compute(int* a, int n,int* odd, int* even)
{
	int i;
	for (i = 0;i < n;i++)
		if (a[i] % 2 == 0)
			*even+=a[i];
		else
			*odd+=a[i];
}
int main()
{
	int i, n ;
	int* odd = new int;
	int* even = new int;
	int* a = new int[20];
	*odd = 0;
	*even = 0;
	cin >> n;
	for (i = 0;i < n;i++)
		cin >> a[i]; 
	compute(a, n, odd, even);
	cout << *odd << ' ' << *even;
	return 0;
}