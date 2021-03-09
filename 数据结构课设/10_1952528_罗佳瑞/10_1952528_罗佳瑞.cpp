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
		else cout << "������������������:";
		cin.ignore(INT32_MAX, '\n');
	}
	Sort T(amount);
	while (type != 9){
		cout << "\n��ѡ�������㷨:";
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
		case 9:cout << "�����˳�����" << endl;break;
		default:cout << "��������������������룡" << endl;
		}
		if (0 < type && type < 9)
			{
				endTime = GetTickCount64();
				cout << "�������㷨����ʱ�䣺" << endTime - startTime << "ms" << endl;
				T.print();
				T.clear();
			}
	}
	system("pause");
		return 0;
}