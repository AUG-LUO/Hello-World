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
		cout << "请输入要移动的棋子坐标：" << endl;
		cin >> old_row >> old_col;
		cout << "请输入该棋子的目标坐标：" << endl;
		cin >> new_row >> new_col;
		if (A.move(old_row, old_col, new_row, new_col)&&!A.jugde_kill_point())//移动错误或得分均跳过生成
			A.add();
	}
	A.print();
	return 0;
}