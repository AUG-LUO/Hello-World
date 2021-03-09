#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include"head.h"
using namespace std;

//菜单函数
void menu()
{
	cout << "请选择所需操作：" << '\n'
		<< "1.取负运算" << '\n'
		<< "2.求倒数" << '\n'
		<< "3.约分" << '\n'
		<< "4.小数转分数" << '\n'
		<< "5.字符串型分数转整数型分数" << '\n'
		<< "6.通分(请用&间隔两个分数)" << '\n'
		<< "7.运算符计算(请用//作为除法区别于分数线)" << '\n'
		<< "8.运算符判断" << endl;
	return  ;

}



//构造函数
fraction::fraction(char* f) : numerator(0), denominator(1)
{
	frac = new char[25];
	ans = new char[25];
	strcpy(frac, f);
}


//取负运算
void fraction::inverse()
{
	if (frac[0] == '+')
	{
		ans[0] = '-';
		int i = 1;
		for (;frac[i];i++)
			ans[i] = frac[i];
		ans[i] = '\0';
	}
	else if(frac[0]=='-')
	{
		ans[0] = '+';
		int i = 1;
		for (;frac[i];i++)
			ans[i] = frac[i];
		ans[i] = '\0';
	}
	else
	{
		ans[0] = '-';
		int i = 0;
		for (;frac[i];i++)
			ans[i+1] = frac[i];
		ans[i + 1] = '\0';
	}
	return ;
}

//转数值型分数
void fraction::string_int()
{
	char* numer = new char[20];
	char* denom = new char[20];
	int i = 0;
	for (;frac[i] != '/';i++)
		numer[i] = frac[i];
	numer[i] = '\0';
	i++;
	int j = 0;
	for (;frac[i];j++, i++)
		denom[j] = frac[i];
	denom[j] = '\0';
	numerator = atoi(numer);
	denominator = atoi(denom);
	delete[]numer;
	delete[]denom;
}

//取倒数函数
void fraction::reciprocal()
{
	int temp;
	temp = abs(numerator);
	if (numerator < 0)
		denominator = -denominator;
	numerator = denominator;
	denominator = temp;
}

//约分函数
void fraction::reduction()
{
		int a = numerator, b = denominator;
		int gcd = a;
		while (b % a != 0)
		{
			gcd = b % a;
			b = a;
			a = gcd;
		}
		numerator /= gcd;
		denominator /=gcd;
		return;
}

//小数转分数函数
void fraction::double_string()
{
	char* int_part = new char[20];
	char* dec_part = new char[20];
	int i,d;
	int n = 0;
	for (;frac[n] != '.';n++)
		int_part[n] = frac[n];
	int_part[n] = '\0';
	n++;
	int len = 0;//小数位数
	for (;frac[n]!='\0';len++, n++)
		dec_part[len] = frac[n];
	dec_part[len] = '\0';
	i = atoi(int_part);
	d= atoi(dec_part);//转成整数部分与小数部分
	
	denominator = (int)pow(10, len);
	numerator = i * denominator + d;
	reduction();
	delete[]int_part;
	delete[]dec_part;
}

//计算

//通分函数
void fraction::same_deno(fraction &c)
{
	int a = c.denominator, b = denominator;
	int gcd = a;
	while (b % a != 0)
	{
		gcd = b % a;
		b = a;
		a = gcd;
	}
	int lcm = c.denominator * denominator / gcd;
	numerator = numerator *(lcm / denominator);
	c.numerator = c.numerator * (lcm / c.denominator);;
	denominator = lcm;
	c.denominator = lcm;
	return;
}

//“*/+-”重载函数
void fraction::operator *(fraction &c)
{
	numerator*=c.numerator;
	denominator *= c.denominator;
	return ;
}
void fraction::operator /(fraction &c)
{
	numerator *= c.denominator;
	denominator  *= c.numerator;
	return;
}
void fraction::operator +(fraction &c)
{
	same_deno(c);
	numerator +=c.numerator;
	return ;
}
void fraction::operator -(fraction &c)
{
	same_deno(c);
	numerator -= c.numerator;
	return;
}

//逻辑运算符重载
bool operator==(fraction& c,fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator == c1.numerator)
		return true;
	else
		return false;
}
bool operator!=(fraction& c, fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator!= c1.numerator)
		return true;
	else
		return false;
}
bool operator<(fraction& c, fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator < c1.numerator)
		return true;
	else
		return false;
}
bool operator>(fraction& c, fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator >c1.numerator)
		return true;
	else
		return false;
}
bool operator<=(fraction& c, fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator <= c1.numerator)
		return true;
	else
		return false;
}
bool operator>=(fraction& c, fraction& c1)
{
	c.same_deno(c1);
	if (c.numerator >= c1.numerator)
		return true;
	else
		return false;
}

void fraction::show(int num)
{
	ofstream fout("cout.txt", ios::app);
	if (!fout.fail())
	{
		fout << "运算结果为：";
		if (num == 1)
			fout << ans << endl;
		else
		{
			if (denominator < 0)
			{
				denominator = -denominator;
				numerator = -numerator;
			}
			if (denominator == 1)
				fout << numerator<<endl;
			else
				fout << numerator << '/' << denominator << endl;
		}
	}
	fout.close();
}

//析构函数
fraction::~fraction()
{
	delete [] frac;
	delete [] ans;
}

