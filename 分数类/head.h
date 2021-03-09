#ifndef HEAD_H
#define HEAD_H
using namespace std;
void menu();//打印菜单函数
class fraction
{
private:
	char* frac, *ans;//输入、输出字符串
	int numerator, denominator;//分子，分母
public:
	fraction(char* f);
	//输入字符串的构造函数
	void inverse();//取负运算函数
	void string_int() ;//转数值型分数运算函数
	void reciprocal() ;//倒数运算函数
	void reduction() ;//约分运算函数
	void double_string() ;//小数转分数运算函数
	void same_deno(fraction &c);//通分函数

	void operator *(fraction& c);
	void operator /(fraction& c);
	void operator +(fraction& c);
	void operator -(fraction& c);

	friend bool operator ==(fraction& c,fraction& c1);
	friend bool operator !=(fraction& c, fraction& c1);
	friend bool operator <(fraction& c,fraction& c1);
	friend bool operator >(fraction& c,fraction& c1);
	friend bool operator <=(fraction& c,fraction& c1);
	friend bool operator >=(fraction& c,fraction& c1);


	void show(int num) ;
	~fraction();
	
};

#endif