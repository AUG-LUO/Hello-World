#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	int N, num;//顾客总数+顾客序号
	Queue<int> A, B;//A、B窗口队列
	cout << "请输入顾客总数、顾客序号（空格隔开）:" << endl;
	cin >> N;
	cout << "业务完成顺序:" << endl;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (num % 2) {  // 根据序号奇偶加入A（奇）或B（偶）序列
			A.push(num);
		}
		else {
			B.push(num);
		}
	}

	while (!A.empty() || !B.empty()) {
		for (int i = 0; i < 2; i++) {//A输出两次
			if (!A.empty()) {
				if (B.empty() && A.size() == 1) {
					cout << A.front();
				}
				else {
					cout << A.front() << ' ';
				}
				A.pop();
			}
		}
		if (!B.empty()) {//B输出一次
			if (A.empty() && B.size() == 1) {
				cout << B.front();
			}
			else {
				cout << B.front() << ' ';
			}
			B.pop();
		}
	}
	cout << endl;
	system("pause");
	return 0;
}