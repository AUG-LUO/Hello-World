#include<iostream>
#include<cstring>
using namespace std;

class Person {
public:
	string name;
	Person* parent;
	Person* firstChild;
	Person* nextSibling;
	Person* lastSibling;
	Person() :parent(NULL), firstChild(NULL), lastSibling(NULL), nextSibling(NULL) {}
	Person(string n, Person * P = NULL, Person * F = NULL, Person * N = NULL, Person * L = NULL)
			:name(n), parent(P), firstChild(F), lastSibling(L), nextSibling(N) {}
	};

	class genealogy {
	private:
		Person* ancestor;
		void printChild(Person* member);//��ӡ��һ����Ů
		void construct();//��������

		Person* find(Person* current, string n);//���Ҽ�ͥ��Ա
		void constructFamily();//������ͥ
		void addChild();//��Ӽ�ͥ��Ա

		void deleteMember(Person* member);//ɾ������
		void deleteFamily();//��ɢ�ֲ���ͥ

		void changeName();//�ı��ͥ��Ա����
	public:
		void run();
	};

	int main() {
		genealogy T;
		T.run();
		system("pause");
		return 0;
	}

	void genealogy::run() {
		cout << "**              ���׹���ϵͳ              **" << endl
			<< "============================================" << endl
			<< "**          ��ѡ��Ҫִ�еĲ���:           **" << endl
			<< "**          A --- ���Ƽ�ͥ                **" << endl
			<< "**          B --- ��Ӽ�ͥ��Ա            **" << endl
			<< "**          C --- ��ɢ�ֲ���Ա            **" << endl
			<< "**          D --- ���ļ�ͥ��Ա����        **" << endl
			<< "**          E --- �˳�ϵͳ                **" << endl
			<< "============================================" << endl;

		construct();
		while (1) {
			char op;
			cout << "��ѡ��Ҫִ�еĲ���: ";
			cin >> op;
			if (!cin.good()) {
				cin.clear();
				op = -1;  // ��������
			}
			cin.ignore(INT32_MAX, '\n');
			switch (op) {
			case 'A':case'a':constructFamily();break;
			case 'B':case'b':addChild();break;
			case 'C':case'c':deleteFamily();break;
			case 'D':case'd':changeName();break;
			case 'E':case'e':cout << "�����˳�..." << endl;return;
			default:cout << "���������������������룡" << endl << endl;continue;
			}
			cout << endl;
		}
	}
	void genealogy::printChild(Person* member) {//��ӡ��һ����Ů
		Person* temp = member->firstChild;
		if (temp == NULL)
		{
			cerr << "�ü�ͥ��Աû����Ů��" << endl;
			return;
		}
		cout << member->name << "�ĵ�һ����Ů�ǣ�";
		while (temp != NULL)
		{
			cout << temp->name << ' ';
			temp = temp->nextSibling;
		}
		cout << endl;
	}

	void genealogy::construct()//��������
	{
		ancestor = new Person;//Ϊ���Ƚ�������ַ
		cout << "���������ȵ�������";
		cin >> ancestor->name;
		cout << "�˼��׵������ǣ�" << ancestor->name << endl << endl;
	}
	Person* genealogy::find(Person* current, string n)//���Ҽ�ͥ��Ա
	{
		if (current == NULL)return NULL;//�ݹ鵽��δ�ҵ�
		if (current->name == n)return current;//�ҵ����ص�ǰָ��
		Person* temp;
		if ((temp = find(current->firstChild, n)) != NULL)return temp;//�ݹ�Ѱ������������Ů��
		else return find(current->nextSibling, n);//�ݹ�Ѱ�����������ֵܣ�
	
	}

	void genealogy::constructFamily()//������ͥ
	{
		string s;
		cout << "������Ҫ������ͥ�˵�������";
		cin >> s;
		Person* member =find(ancestor, s);
		if (member == NULL)
		{
			cout << "���޴��ˣ������²���" << endl;
			return;
		}
		if (member->firstChild != NULL)
		{
			cout << "�ѽ�����ͥ��" << endl;
			return;
		}
		int n;
		cout << "������" << member->name << "�Ķ�Ů������";
		cin >> n;
		string* child = new string[n];
		cout << "����������" << member->name << "�Ķ�Ů��������";
		Person* temp = member->firstChild;
		for (int i = 0; i < n; i++)
		{
			cin >> child[i];
			Person* newChild = new Person(child[i], member);
			if (i == 0)
			{
				member->firstChild = newChild;
				temp = member->firstChild;
			}
			else
			{
				newChild->lastSibling = temp;
				temp->nextSibling = newChild;
				temp = temp->nextSibling;
			}
		}
		printChild(member);
	}
	void genealogy::addChild()//��Ӽ�ͥ��Ա
	{
		string p, c;
		cout << "������Ҫ��Ӷ�Ů���˵�������";
		cin >> p;
		Person* member =find(ancestor, p);
		if (member == NULL)
		{
			cout << "���޴��ˣ������²���" << endl;
			return;
		}
		cout << "������" << p << "����ӵĶ�Ů��������";
		cin >> c;
		Person* newChild = new Person(c, member);
		Person* temp = member->firstChild;
		if (member->firstChild == NULL)
			member->firstChild = newChild;
		else
		{
			while (temp->nextSibling != NULL)
				temp = temp->nextSibling;
			newChild->lastSibling = temp;
			temp->nextSibling = newChild;
		}
		printChild(member);
	}
	void genealogy::deleteMember(Person* member)//ɾ������
	{
		Person* temp = member;
		while (temp->nextSibling != NULL)//��ѭ�ֵ�������
			temp = temp->nextSibling;
		if (temp->lastSibling != NULL) {//��ذѺ�һ���ֵܽ�����,��Ϊû���ֵܽڵ����
			temp = temp->lastSibling;
			(temp->nextSibling)->lastSibling = NULL;
			deleteMember(temp->nextSibling);
		}
		if (temp->firstChild != NULL)//������������ֵ�����
			deleteMember(temp->firstChild);
		delete member;
		member = NULL;//���������ͷŸý��
		return;
	}
	void genealogy::deleteFamily()//��ɢ�ֲ���ͥ
	{
		string s;
		cout << "������Ҫ��ɢ��ͥ���˵�������";
		cin >> s;
		Person* member =find(ancestor, s);
		if (member == NULL)
		{
			cout << "���޴��ˣ������²���" << endl;
			return;
		}
		if (member == ancestor)
		{
			cout << "���ڵ㲻����ɾ���������²���" << endl;
			return;
		}
		printChild(member);
		if (member->firstChild != NULL)//ɾ���ý�������
			deleteMember(member->firstChild);
		if (member->lastSibling != NULL && member->nextSibling != NULL) {
			(member->lastSibling)->nextSibling = member->nextSibling;
			(member->nextSibling)->lastSibling = member->lastSibling;
		}
		else if (member->lastSibling != NULL && member->nextSibling == NULL) {
			(member->lastSibling)->nextSibling = NULL;
		}
		else if (member->lastSibling == NULL && member->nextSibling != NULL) {
			(member->nextSibling)->lastSibling = NULL;
			(member->parent)->firstChild = member->nextSibling;
		}
		else if (member->lastSibling == NULL && member->nextSibling == NULL) {
			(member->parent)->firstChild = NULL;
		}
		delete member;
		member = NULL;//ɾ���ý��
		return;
	}
	void genealogy::changeName()//�ı��ͥ��Ա����
	{
		string s1, s2;
		cout << "������Ҫ������������Ŀǰ������";
		cin >> s1;
		Person* member =find(ancestor, s1);
		if (member == NULL)
		{
			cout << "���޴��ˣ������²���" << endl;
			return;
		}
		cout << "��������ĺ��������";
		cin >> s2;
		member->name = s2;
		cout << s1 << "�Ѹ���Ϊ" << s2 << endl;
	}