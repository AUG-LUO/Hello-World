#include <iostream>
using namespace std;
struct Student
{
	string name;
	int key;
	int grade;
}s[16] = {
{ "Alan",123456,90},
{"Barry",223456,95},
{ "Carl",323456,91},
{"Daniel",423456,96},
{"Eve",523456,85},
{"Frank",623456,86},
{"Grace",723456,80},
{"Helen",823456,85},
{"Iris",134568,91},
{"Jane",234568,92},
{"Lee",334568,95},
{"Martin",434568,96},
{"Nina",534568,85},
{"Owen",634568,80},
{"Paul",734568,86},
{"Tony",834568,85}
};
int main()
{
	string name;
	int key, i;
	cin >> name;
	cin >> key;
	for (i = 0;i < 16;i++)
		if (name == s[i].name && key == s[i].key)
		{
			cout << s[i].grade;
			break;
		}
	if (i == 16)
		cout << -1;
	return 0;
}