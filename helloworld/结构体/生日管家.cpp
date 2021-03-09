//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include <iostream>
using namespace std;
struct Birth
{
	string name;
	int old;
	string birthday;
}all[10];
void find(Birth* all, int N, string name)
{
	int  i;
	for (i = 0;i < N;i++)
		if (name == all[i].name)
		{
			cout << all[i].old << " " << all[i].birthday;
			break;
		}
	if (i == N)
		cout << "Not Found";
	return;
}
int main()
{
	int i;
	int N;
	string name;
	cin >> N;
	for (i = 0;i < N;i++)
		cin >> all[i].name >> all[i].old >> all[i].birthday;
	cin >> name;
	find(all, N, name);
	return 0;
}