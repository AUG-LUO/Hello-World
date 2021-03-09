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
		void printChild(Person* member);//打印第一代子女
		void construct();//建立家谱

		Person* find(Person* current, string n);//查找家庭成员
		void constructFamily();//建立家庭
		void addChild();//添加家庭成员

		void deleteMember(Person* member);//删除操作
		void deleteFamily();//解散局部家庭

		void changeName();//改变家庭成员姓名
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
		cout << "**              家谱管理系统              **" << endl
			<< "============================================" << endl
			<< "**          请选择要执行的操作:           **" << endl
			<< "**          A --- 完善家庭                **" << endl
			<< "**          B --- 添加家庭成员            **" << endl
			<< "**          C --- 解散局部成员            **" << endl
			<< "**          D --- 更改家庭成员姓名        **" << endl
			<< "**          E --- 退出系统                **" << endl
			<< "============================================" << endl;

		construct();
		while (1) {
			char op;
			cout << "请选择要执行的操作: ";
			cin >> op;
			if (!cin.good()) {
				cin.clear();
				op = -1;  // 输入有误
			}
			cin.ignore(INT32_MAX, '\n');
			switch (op) {
			case 'A':case'a':constructFamily();break;
			case 'B':case'b':addChild();break;
			case 'C':case'c':deleteFamily();break;
			case 'D':case'd':changeName();break;
			case 'E':case'e':cout << "正在退出..." << endl;return;
			default:cout << "操作输入有误，请重新输入！" << endl << endl;continue;
			}
			cout << endl;
		}
	}
	void genealogy::printChild(Person* member) {//打印第一代子女
		Person* temp = member->firstChild;
		if (temp == NULL)
		{
			cerr << "该家庭成员没有子女！" << endl;
			return;
		}
		cout << member->name << "的第一代子女是：";
		while (temp != NULL)
		{
			cout << temp->name << ' ';
			temp = temp->nextSibling;
		}
		cout << endl;
	}

	void genealogy::construct()//建立家谱
	{
		ancestor = new Person;//为祖先结点申请地址
		cout << "请输入祖先的姓名：";
		cin >> ancestor->name;
		cout << "此家谱的祖先是：" << ancestor->name << endl << endl;
	}
	Person* genealogy::find(Person* current, string n)//查找家庭成员
	{
		if (current == NULL)return NULL;//递归到底未找到
		if (current->name == n)return current;//找到返回当前指针
		Person* temp;
		if ((temp = find(current->firstChild, n)) != NULL)return temp;//递归寻找左子树（子女）
		else return find(current->nextSibling, n);//递归寻找右子树（兄弟）
	
	}

	void genealogy::constructFamily()//建立家庭
	{
		string s;
		cout << "请输入要建立家庭人的姓名：";
		cin >> s;
		Person* member =find(ancestor, s);
		if (member == NULL)
		{
			cout << "查无此人！请重新操作" << endl;
			return;
		}
		if (member->firstChild != NULL)
		{
			cout << "已建立家庭！" << endl;
			return;
		}
		int n;
		cout << "请输入" << member->name << "的儿女人数：";
		cin >> n;
		string* child = new string[n];
		cout << "请依次输入" << member->name << "的儿女的姓名：";
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
	void genealogy::addChild()//添加家庭成员
	{
		string p, c;
		cout << "请输入要添加儿女的人的姓名：";
		cin >> p;
		Person* member =find(ancestor, p);
		if (member == NULL)
		{
			cout << "查无此人！请重新操作" << endl;
			return;
		}
		cout << "请输入" << p << "新添加的儿女的姓名：";
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
	void genealogy::deleteMember(Person* member)//删除操作
	{
		Person* temp = member;
		while (temp->nextSibling != NULL)//先循兄弟链到底
			temp = temp->nextSibling;
		if (temp->lastSibling != NULL) {//向回把后一个兄弟截下来,都为没有兄弟节点的树
			temp = temp->lastSibling;
			(temp->nextSibling)->lastSibling = NULL;
			deleteMember(temp->nextSibling);
		}
		if (temp->firstChild != NULL)//处理截下来的兄弟子链
			deleteMember(temp->firstChild);
		delete member;
		member = NULL;//都处理完释放该结点
		return;
	}
	void genealogy::deleteFamily()//解散局部家庭
	{
		string s;
		cout << "请输入要解散家庭的人的姓名：";
		cin >> s;
		Person* member =find(ancestor, s);
		if (member == NULL)
		{
			cout << "查无此人！请重新操作" << endl;
			return;
		}
		if (member == ancestor)
		{
			cout << "根节点不允许被删除！请重新操作" << endl;
			return;
		}
		printChild(member);
		if (member->firstChild != NULL)//删掉该结点的子孙
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
		member = NULL;//删掉该结点
		return;
	}
	void genealogy::changeName()//改变家庭成员姓名
	{
		string s1, s2;
		cout << "请输入要更改姓名的人目前姓名：";
		cin >> s1;
		Person* member =find(ancestor, s1);
		if (member == NULL)
		{
			cout << "查无此人！请重新操作" << endl;
			return;
		}
		cout << "请输入更改后的姓名：";
		cin >> s2;
		member->name = s2;
		cout << s1 << "已更名为" << s2 << endl;
	}