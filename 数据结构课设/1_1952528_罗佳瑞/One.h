#pragma once
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

class Node {
public:
	Node* next;
	string numble, name, sex, age, sort;
	Node() : next(NULL){
		string numble, name, sex, sort;
	}//默认构造函数
	Node(string n,string na,string s,string a,string so) : next(NULL),numble(n),name(na),sex(s),age(a),sort(so) {
	}//构造函数

};
class Linkedlist {
private:
	Node* head;//链表头指针
public:
	Linkedlist() { head = new Node(); }//构造函数
	void create(int num);//创建链表
	void print();//打印链表
	int search(string n);//按考号查找位置操作
	Node* locate(int n);//定位函数

	bool insert(); //插入操作
	bool find();//查找操作
	bool clear();//删除操作
	bool set();//修改操作
	
};
void Linkedlist::create(int num)//创建链表
{
	string n, na, s, a, so;
	Node* tail = head;
	for (int i = 0;i < num;i++)
	{
		cin >> n >> na >> s >> a >> so;
		Node* newnode = new Node(n, na, s, a, so);
		tail->next = newnode;
		tail = newnode;
	}
}
int Linkedlist::search(string n)//按考号查找位置操作
{
	Node* current = head->next;
	int i = 1;
	for (;current != NULL;current = current->next, i++) {
		if (current->numble == n)break;
	}//当找到该考号时停止循环，返回当前指针位置i
	if (current == NULL)//否则，循环到链表尾NULL，返回-1表示未找到
		return -1;
	return i;//返回所定位的结点位置
}
Node* Linkedlist::locate(int n)//定位函数
{
	if (n < 0)return NULL;//n不合理
	Node* current = head;
	for (int i = 0;current != NULL;current = current->next, i++)//当找到该位置时停止循环，返回当前指针
		if (i == n)break;
	return current;//返回所定位的结点地址，若为NULL,则n值过大
}


bool Linkedlist::insert() //插入操作
{
	int site;
	string n, na, s, a, so;
	cout << "请输入你要插入的考生位置：";
	cin >> site;
	Node* current = locate(site - 1);
	if (current == NULL) { cout << "您输入的位置不合法," ;return false; }//插入定位不成功
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄，报考类别：";
	cin >> n >> na >> s >> a >> so;
	Node* newnode = new Node(n, na, s, a, so);
	if (newnode == NULL) { cerr << "存储分配错误！" << endl;exit(1); }//创建不成功
	newnode->next = current->next;
	current->next = newnode;
	print();
	return true;
}
bool Linkedlist::find()//查找操作
{
	string n;
	cout << "请输入你要查找的考生考号：";
	cin >> n;
	int site = search(n);
	Node* current = locate(site);
	if (current == NULL) { cout << "您要查找的考生不存在," ;return false; }//查找定位不成功
	cout << "你查找的考生信息是：" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	return true;
}
bool Linkedlist::clear()//删除操作
{
	string n;
	cout << "请输入你要删除的考生考号：";
	cin >> n;
	int site = search(n);
	Node* current = locate(site - 1);
	if (current == NULL||current->next==NULL ) { cout << "您要删除的考生不存在," ;return false; }//删除定位不成功
	Node* del = current->next;
	cout << "你删除的考生信息是：" << del->numble << "    " << del->name << "    " << del->sex << "    " << del->age << "    " << del->sort << endl;
	current->next = del->next;
	delete del;
	return true;
}
bool Linkedlist::set()//修改操作
{
	string n;
	int change;
	cout << "请输入你要修改的考生考号：";
	cin >> n;
	int site = search(n);
	Node* current = locate(site);
	if (current == NULL) { cout << "您要修改的考生不存在," ;return false; }//修改定位不成功
	cout << "你要修改的考生信息是：" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	cout << "请输入你要修改的内容序号（1为考号，2为姓名，3为性别，4为年龄，5为报考类别）：";
	cin >> change;
	cout << "请输入你要修改的内容：";
	switch (change) {
	case 1:cin >> current->numble;break;
	case 2:cin >> current->name;break;
	case 3:cin >> current->sex;break;
	case 4:cin >> current->age;break;
	case 5:cin >> current->sort;break;
	}
	cout << "修改后的考生信息是：" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	return true;
}

void Linkedlist::print()//打印链表
{
	cout << setiosflags(ios::left) << setw(8) << "考号" << setiosflags(ios::left) << setw(8) << "姓名" << setiosflags(ios::left) << setw(8) << "性别" << setiosflags(ios::left) << setw(8) << "年龄" << setiosflags(ios::left) << setw(8) << "报考类别" << endl;
	for (Node* current = head->next;current != NULL;current = current->next)
		cout << setiosflags(ios::left) << setw(8) << current->numble << setiosflags(ios::left) << setw(8) << current->name << setiosflags(ios::left) << setw(8) << current->sex << setiosflags(ios::left) << setw(8) << current->age << setiosflags(ios::left) << setw(8) << current->sort << endl;
}