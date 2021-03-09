#include<iostream>
#include"One.h"

int main() {
	cout << "首先请先建立考试信息系统！" << endl;
	int n=0;
	while (n <= 0) {
		cout << "请输入考生人数：";
		cin >> n;
		if (n > 0)
			break;
		cout << "请输入一个正整数。" << endl;
	}
	Linkedlist Studentlist;
	cout<< "请依次输入考生的考号、姓名、性别、年龄及报考类别：" << endl;
	Studentlist.create(n);
	Studentlist.print();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）"<<endl;
	int op=1;
	while (op)
	{
		bool wrong = true;
		cout <<'\n'<< "请选择您要进行的操作：";
		cin >> op;
		switch (op) {
		case 1:wrong=Studentlist.insert();break;
		case 2:wrong = Studentlist.clear();break;
		case 3:wrong = Studentlist.find();break;
		case 4:wrong = Studentlist.set();break;
	    case 5:Studentlist.print();break;
		case 0:cout << "正在退出……" << endl;break;
		default:cout << "抱歉，您想要的操作不存在，请重新选择！" << endl;break;
		}
		if(wrong==false)
			cout<<"请重新确认操作!"<<endl;
	}
	return 0;
}