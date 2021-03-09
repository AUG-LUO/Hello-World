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
	}//Ĭ�Ϲ��캯��
	Node(string n,string na,string s,string a,string so) : next(NULL),numble(n),name(na),sex(s),age(a),sort(so) {
	}//���캯��

};
class Linkedlist {
private:
	Node* head;//����ͷָ��
public:
	Linkedlist() { head = new Node(); }//���캯��
	void create(int num);//��������
	void print();//��ӡ����
	int search(string n);//�����Ų���λ�ò���
	Node* locate(int n);//��λ����

	bool insert(); //�������
	bool find();//���Ҳ���
	bool clear();//ɾ������
	bool set();//�޸Ĳ���
	
};
void Linkedlist::create(int num)//��������
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
int Linkedlist::search(string n)//�����Ų���λ�ò���
{
	Node* current = head->next;
	int i = 1;
	for (;current != NULL;current = current->next, i++) {
		if (current->numble == n)break;
	}//���ҵ��ÿ���ʱֹͣѭ�������ص�ǰָ��λ��i
	if (current == NULL)//����ѭ��������βNULL������-1��ʾδ�ҵ�
		return -1;
	return i;//��������λ�Ľ��λ��
}
Node* Linkedlist::locate(int n)//��λ����
{
	if (n < 0)return NULL;//n������
	Node* current = head;
	for (int i = 0;current != NULL;current = current->next, i++)//���ҵ���λ��ʱֹͣѭ�������ص�ǰָ��
		if (i == n)break;
	return current;//��������λ�Ľ���ַ����ΪNULL,��nֵ����
}


bool Linkedlist::insert() //�������
{
	int site;
	string n, na, s, a, so;
	cout << "��������Ҫ����Ŀ���λ�ã�";
	cin >> site;
	Node* current = locate(site - 1);
	if (current == NULL) { cout << "�������λ�ò��Ϸ�," ;return false; }//���붨λ���ɹ�
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����䣬�������";
	cin >> n >> na >> s >> a >> so;
	Node* newnode = new Node(n, na, s, a, so);
	if (newnode == NULL) { cerr << "�洢�������" << endl;exit(1); }//�������ɹ�
	newnode->next = current->next;
	current->next = newnode;
	print();
	return true;
}
bool Linkedlist::find()//���Ҳ���
{
	string n;
	cout << "��������Ҫ���ҵĿ������ţ�";
	cin >> n;
	int site = search(n);
	Node* current = locate(site);
	if (current == NULL) { cout << "��Ҫ���ҵĿ���������," ;return false; }//���Ҷ�λ���ɹ�
	cout << "����ҵĿ�����Ϣ�ǣ�" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	return true;
}
bool Linkedlist::clear()//ɾ������
{
	string n;
	cout << "��������Ҫɾ���Ŀ������ţ�";
	cin >> n;
	int site = search(n);
	Node* current = locate(site - 1);
	if (current == NULL||current->next==NULL ) { cout << "��Ҫɾ���Ŀ���������," ;return false; }//ɾ����λ���ɹ�
	Node* del = current->next;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << del->numble << "    " << del->name << "    " << del->sex << "    " << del->age << "    " << del->sort << endl;
	current->next = del->next;
	delete del;
	return true;
}
bool Linkedlist::set()//�޸Ĳ���
{
	string n;
	int change;
	cout << "��������Ҫ�޸ĵĿ������ţ�";
	cin >> n;
	int site = search(n);
	Node* current = locate(site);
	if (current == NULL) { cout << "��Ҫ�޸ĵĿ���������," ;return false; }//�޸Ķ�λ���ɹ�
	cout << "��Ҫ�޸ĵĿ�����Ϣ�ǣ�" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	cout << "��������Ҫ�޸ĵ�������ţ�1Ϊ���ţ�2Ϊ������3Ϊ�Ա�4Ϊ���䣬5Ϊ������𣩣�";
	cin >> change;
	cout << "��������Ҫ�޸ĵ����ݣ�";
	switch (change) {
	case 1:cin >> current->numble;break;
	case 2:cin >> current->name;break;
	case 3:cin >> current->sex;break;
	case 4:cin >> current->age;break;
	case 5:cin >> current->sort;break;
	}
	cout << "�޸ĺ�Ŀ�����Ϣ�ǣ�" << current->numble << "    " << current->name << "    " << current->sex << "    " << current->age << "    " << current->sort << endl;
	return true;
}

void Linkedlist::print()//��ӡ����
{
	cout << setiosflags(ios::left) << setw(8) << "����" << setiosflags(ios::left) << setw(8) << "����" << setiosflags(ios::left) << setw(8) << "�Ա�" << setiosflags(ios::left) << setw(8) << "����" << setiosflags(ios::left) << setw(8) << "�������" << endl;
	for (Node* current = head->next;current != NULL;current = current->next)
		cout << setiosflags(ios::left) << setw(8) << current->numble << setiosflags(ios::left) << setw(8) << current->name << setiosflags(ios::left) << setw(8) << current->sex << setiosflags(ios::left) << setw(8) << current->age << setiosflags(ios::left) << setw(8) << current->sort << endl;
}