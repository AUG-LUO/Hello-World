#include<iostream>
#include"Two.h"
using namespace std;

int main(){
	Linkedlist s1,s2;
	cout << "请输入序列1（以-1表示序列结尾）：" << endl;
	s1.create();
	cout << "请输入序列2（以-1表示序列结尾）：" << endl;
	s2.create();
	cout << "两个输入序列的交集序列为：" << endl;
	print(compare(s1, s2));
	cout << endl;
	system("pause");
	return 0;
}