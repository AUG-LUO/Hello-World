#include"Nine.h"
using namespace std;

int main() {
	schedule T;
	T.putIn();
	T.arrangeTerm();
	T.arrangeWeek();
	T.print();
	cout << "已创建课表！" << endl;
	system("pause");
	return 0;
}

