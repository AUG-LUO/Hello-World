#include <iostream>
using namespace std;
bool isprime(int m)
{
	int i;
	for (i = 2;i < m;i++)
		if (m % i == 0)
			return 0;
	return 1;
}
int main()
{
	int i,j,n;
	for(i=3,j=5,n=0;n<10;i++,j++)
		if ((isprime(i)) && (isprime(j)))
		{
			cout <<'<'<<i<<','<<j<<'>'<<endl;
			n++;
		}
	return 0;
}