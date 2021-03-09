#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
class tri
{
private:
	double a, b, c;
public:
	tri(double a1, double b1, double c1)
	{
		a = a1;b = b1;c = c1;
	}
	virtual double area()
	{
		double p;
		p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	double peri()
	{
		return a + b + c;
	}
};
class col :public tri
{
private:
	double h;
public:
	col(double a1, double b1, double c1, double h1) :tri(a1, b1, c1)
	{
		h = h1;
	}
	double area()
	{
		return 2 * tri::area() + tri::peri() * h;
	}
	double volume()
	{
		return h * tri::area();
	}
};
int main()
{
	double a, b, c, h;
	cin >> a >> b >> c;
	cin >> h;
	col co(a, b, c, h);
	tri* tr = &co;
	cout << setiosflags(ios::fixed) << setprecision(2) << co.volume() << " " << tr->area();
	return 0;
}