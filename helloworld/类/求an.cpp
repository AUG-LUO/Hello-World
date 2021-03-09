#include <iostream>
using namespace std;
class vector
{
private:
	int n;
	int* array;
public:
	vector(int n1)
	{
		n = n1;
		array = new int[n];//注意要放在构造函数里初始化
	}
	~vector()
	{
		delete array;//所有new申请的空间都要delete释放防止内存溢出
	}
	int an()
	{
		array[0] = 1;
		array[1] = 1;
		int i;
		for (i = 2;i < n;i++)
			array[i] = array[i - 1] + 2 * array[i - 2];
		return array[n - 1];
	}
};
int main()
{
	int n;
	cin >> n;
	vector v(n);
	cout << v.an();
	return 0;
}
