#include <iostream>
using namespace std;
struct Fraction
{
	int z;
	int m;
}s[2];
void add(Fraction a, Fraction b)
{
	int  i, z, m, gcd = 1;
	z = a.z * b.m + b.z * a.m;
	m = a.m * b.m;
	if (z % m == 0)
		cout << z / m;
	else
	{
		for (i = 2;i <= z && i <= m;i++)
			if (z % i == 0 && m % i == 0)
				gcd = i;
		cout << z / gcd << '/' << m / gcd;
	}
	return;
}
int main()
{
	cin >> s[0].z >> s[0].m;
	cin >> s[1].z >> s[1].m;
	add(s[0], s[1]);
	return 0;
}