#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	int N, num;//�˿�����+�˿����
	Queue<int> A, B;//A��B���ڶ���
	cout << "������˿��������˿���ţ��ո������:" << endl;
	cin >> N;
	cout << "ҵ�����˳��:" << endl;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (num % 2) {  // ���������ż����A���棩��B��ż������
			A.push(num);
		}
		else {
			B.push(num);
		}
	}

	while (!A.empty() || !B.empty()) {
		for (int i = 0; i < 2; i++) {//A�������
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
		if (!B.empty()) {//B���һ��
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