#include<iostream>
#include"head.h"
using namespace std;

int main()
{
	Game A;
	A.start();
	A.draw();
	while (A.jugde_end()!=0)
	{
		int old_row, old_col;
		int new_row, new_col;
		cout << "������Ҫ�ƶ����������꣺" << endl;
		cin >> old_row >> old_col;
		cout << "����������ӵ�Ŀ�����꣺" << endl;
		cin >> new_row >> new_col;
		if (A.move(old_row, old_col, new_row, new_col)&&!A.jugde_kill_point())//�ƶ������÷־���������
			A.add();
	}
	A.print();
	return 0;
}