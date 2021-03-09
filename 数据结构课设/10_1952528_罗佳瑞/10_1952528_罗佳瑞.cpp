#include <iostream>
#include"Ten.h"
#include<windows.h>
using namespace std;

int main()
{
	menu();
	int type=0;
	long long startTime, endTime;
	int amount;
	while (1) {
		cin >> amount;
		if (cin.good())break;
		else cout << "输入有误！请重新输入:";
		cin.ignore(INT32_MAX, '\n');
	}
	Sort T(amount);
	while (type != 9){
		cout << "\n请选择排序算法:";
		cin >> type;
		if (0 < type && type < 9)
		{
			T.create();
			startTime = GetTickCount64();
		}
		switch (type)
		{
		case 1:T.bubbleSort();break;
		case 2:T.selectionSort();break;
		case 3:T.straightInsertion(0, amount);break;
		case 4:T.shellSort(0, amount);break;
		case 5:T.quickSort(0, amount);break;
		case 6:T.heapSort(0, amount);break;
		case 7:T.mergeSort();break;
		case 8:T.radixSort(0, amount);break;
		case 9:cout << "正在退出……" << endl;break;
		default:cout << "操作输入错误！请重新输入！" << endl;
		}
		if (0 < type && type < 9)
			{
				endTime = GetTickCount64();
				cout << "该排序算法所用时间：" << endTime - startTime << "ms" << endl;
				T.print();
				T.clear();
			}
	}
	system("pause");
		return 0;
}