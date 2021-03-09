//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include <iostream>
using namespace std;
struct Student
{
	int num;
	string name;
	int Chinese;
	int math;
	int English;
	int sum;
}s[50];
void low(Student* s, int N)
{
	int  i, j, n, temp, low[10] = { 0 };
	for (i = 1, j = 0;i < N;i++)
		if (s[low[j]].sum > s[i].sum)
		{
			if (j > 0)
			{
				j = 0;
			}
			low[j] = i;
		}
		else if (s[low[j]].sum == s[i].sum)
		{
			j += 1;
			low[j] = i;
		}
		else
			continue;
	n = j + 1;
	for (i = 0; i < n;i++)
		for (j = i + 1; j < n;j++)
			if (s[low[j]].num < s[low[i]].num)
			{
				temp = low[i];
				low[i] = low[j];
				low[j] = temp;
			}
	for (j = 0;j < n;j++)
	{
		cout << s[low[j]].num << " " << s[low[j]].name << " " << s[low[j]].sum;
		if (n != 1)
			cout << endl;
	}
	return;
}
int main()
{
	int i, N;
	cin >> N;
	for (i = 0;i < N;i++)
	{
		cin >> s[i].num >> s[i].name >> s[i].Chinese >> s[i].math >> s[i].English;
		s[i].sum = s[i].Chinese + s[i].math + s[i].English;
	}
	low(s, N);
	return 0;
}