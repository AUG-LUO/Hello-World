#include<iostream>
#include"Two.h"
using namespace std;

int main(){
	Linkedlist s1,s2;
	cout << "����������1����-1��ʾ���н�β����" << endl;
	s1.create();
	cout << "����������2����-1��ʾ���н�β����" << endl;
	s2.create();
	cout << "�����������еĽ�������Ϊ��" << endl;
	print(compare(s1, s2));
	cout << endl;
	system("pause");
	return 0;
}