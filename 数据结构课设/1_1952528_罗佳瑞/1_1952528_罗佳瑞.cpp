#include<iostream>
#include"One.h"

int main() {
	cout << "�������Ƚ���������Ϣϵͳ��" << endl;
	int n=0;
	while (n <= 0) {
		cout << "�����뿼��������";
		cin >> n;
		if (n > 0)
			break;
		cout << "������һ����������" << endl;
	}
	Linkedlist Studentlist;
	cout<< "���������뿼���Ŀ��š��������Ա����估�������" << endl;
	Studentlist.create(n);
	Studentlist.print();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������"<<endl;
	int op=1;
	while (op)
	{
		bool wrong = true;
		cout <<'\n'<< "��ѡ����Ҫ���еĲ�����";
		cin >> op;
		switch (op) {
		case 1:wrong=Studentlist.insert();break;
		case 2:wrong = Studentlist.clear();break;
		case 3:wrong = Studentlist.find();break;
		case 4:wrong = Studentlist.set();break;
	    case 5:Studentlist.print();break;
		case 0:cout << "�����˳�����" << endl;break;
		default:cout << "��Ǹ������Ҫ�Ĳ��������ڣ�������ѡ��" << endl;break;
		}
		if(wrong==false)
			cout<<"������ȷ�ϲ���!"<<endl;
	}
	return 0;
}