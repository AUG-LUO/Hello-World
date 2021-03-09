#include <iostream>
#include<iomanip>
using namespace std;
class container
{
public:
	const double pi;
	double radius;
	container(double a) :pi(3.1416)
	{
		radius = a;
	}
	virtual double surface_area() = 0;
	virtual double volume() = 0;
};
class cube :public container
{
public:
	cube(double r) :container(r)
	{}
	double surface_area()
	{
		return 4 * pi * radius * radius;
	}
	double volume()
	{
		return 4 * pi * radius * radius * radius / 3;
	}
};
class sphere :public container
{
public:
	sphere(double a) :container(a)
	{}
	double surface_area()
	{
		return 6 * radius * radius;
	}
	double volume()
	{
		return  radius * radius * radius;
	}
};
class cylinder :public container
{
private:
	double h;
public:
	cylinder(double r, double h1) :container(r)
	{
		h = h1;
	}
	double surface_area()
	{
		return 2 * pi * radius * h + 2 * pi * radius * radius;
	}
	double volume()
	{
		return h * pi * radius * radius;
	}
};

int main()
{
	double r1, a, r2, h;
	cin >> a;
	cin >> r1;
	cin >> r2 >> h;
	sphere a1(a);
	cube a2(r1);
	cylinder a3(r2, h);
	cout << setiosflags(ios::fixed) << setprecision(1) << a1.surface_area() << " " << a1.volume() << endl;
	cout << setiosflags(ios::fixed) << setprecision(1) << a2.surface_area() << " " << a2.volume() << endl;
	cout << setiosflags(ios::fixed) << setprecision(1) << a3.surface_area() << " " << a3.volume() << endl;
	return 0;
}