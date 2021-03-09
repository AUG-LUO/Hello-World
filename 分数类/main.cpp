#include<iostream>
#include<fstream>
#include"head.h"
using namespace std;

int main()
{
	menu();
	int num;
	char* f = new char[25];
	cout << "请选择所需操作：" << endl;
	cin >> num;
	cout << "请输入分数/运算：" << endl;
	cin >> f;
	if (num == 1)//1、取负运算
	{
		fraction t(f);
		t.inverse();
		t.show(num);//输出函数
	}
	else if (num == 6 || num == 7 || num == 8)
	{
		char* t1 = new char[20];
		char* t2 = new char[20];
		char op;
		int i = 0;
		for (;f[i] != '+' && f[i] != '-' && f[i] != '*' && f[i] != '!' && f[i] != '=' && f[i] != '<' && f[i] != '>' && (!(f[i] == '/' && f[i + 1] == '/')) && f[i] != '&';i++)
			t1[i] = f[i];
		t1[i] = '\0';//取出第一个分数字符串
		op = f[i];//取出运算符
		i++;
		char _op = 0;
		if (f[i] == '=' || f[i] == '/')
		{
			_op = f[i];
			i++;
		}
		int j = 0;
		for (;f[i];j++, i++)
			t2[j] = f[i];
		t2[j] = '\0';//取出第二个分数字符串
		fraction tf1(t1), tf2(t2);
		//进行运算
		tf1.string_int();
		tf2.string_int();
		if (num == 6)//6、通分运算
		{
			tf1.same_deno(tf2);
			tf1.show(num);
			tf2.show(num);
		}
		else if (num == 7)//7、运算符计算
		{
			switch (op)
			{
			case '+':tf1 + tf2;break;
			case '-':tf1 - tf2;break;
			case '*':tf1* tf2;break;
			case '/':tf1 / tf2;break;
			}
			tf1.reduction();
			tf1.show(num);
		}
		else if (num == 8)//8、运算符判断
		{
			ofstream fout("cout.txt", ios::app);
			if (!fout.fail())
			{
				bool op_ans=true;
				if (_op == '=')
				{
					switch (op)
					{
					case '=':op_ans = (tf1 == tf2);break;
					case '!':op_ans = (tf1 != tf2);break;
					case '<':op_ans = (tf1 <= tf2);break;
					case '>':op_ans = (tf1 >= tf2);break;
					}
					
				}
				else
				{
					switch (op)
					{
					case '<':op_ans = (tf1 < tf2);break;
					case '>':op_ans = (tf1 > tf2);break;
					}
				
				}
				if (op_ans)
					fout << "正确" << endl;
				else
					fout << "错误" << endl;
			}
			fout.close();
		}
		delete[]t1;
		delete[]t2;
	}
	else
	{
		fraction t(f);
		if (num == 4)
			t.double_string();//4、小数转分数
		else
		{
			t.string_int();//5.转整数型分数
			if (num == 2)//2、取倒数
				t.reciprocal();
			else if (num == 3)//3、约分
				t.reduction();
		}
		t.show(num);//输出函数
	}
	delete[]f;
	return 0;
}