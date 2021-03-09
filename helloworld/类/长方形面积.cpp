#include <iostream>
using namespace std;
class point
{
private:
	double x, y;
public:
	void point_x(double x1)
	{
		x = x1;
	}
	void point_y(double y1)
	{
		y = y1;
	}
	void read(double* x1, double* y1)
	{
		*x1 = x;*y1 = y;
	}
	void printf()
	{
		cout << x << ' ' << y << endl;
	}
};
class Rectangle
{
private:
	double S;
	point left_high, right_high, right_low, left_low;
public:
	void is_where(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		if (x1 == x2)
			if (x1 > x3)
			{
				left_high.point_x(x3);
				left_low.point_x(x3);
				right_high.point_x(x1);
				right_low.point_x(x1);
			}
			else
			{
				left_high.point_x(x1);
				left_low.point_x(x1);
				right_high.point_x(x3);
				right_low.point_x(x3);
			}
		else if (x1 > x2)
		{
			left_high.point_x(x2);
			left_low.point_x(x2);
			right_high.point_x(x1);
			right_low.point_x(x1);
		}
		else
		{
			left_high.point_x(x1);
			left_low.point_x(x1);
			right_high.point_x(x2);
			right_low.point_x(x2);
		}

		if (y1 == y2)
			if (y1 > y3)
			{
				left_high.point_y(y1);
				right_high.point_y(y1);
				left_low.point_y(y3);
				right_low.point_y(y3);
			}
			else
			{
				left_high.point_y(y3);
				right_high.point_y(y3);
				left_low.point_y(y1);
				right_low.point_y(y1);
			}
		else if (y1 > y2)
		{
			left_high.point_y(y1);
			right_high.point_y(y1);
			left_low.point_y(y2);
			right_low.point_y(y2);
		}
		else
		{
			left_high.point_y(y2);
			right_high.point_y(y2);
			left_low.point_y(y1);
			right_low.point_y(y1);
		}
	}
	void printf_point()
	{
		left_high.printf();
		right_high.printf();
		right_low.printf();
		left_low.printf();
	}
	void area()
	{
		double x1, y1, x2, y2, x3, y3;
		left_high.read(&x1, &y1);
		right_high.read(&x2, &y2);
		right_low.read(&x3, &y3);
		S = (x2 - x1) * (y2 - y3);
	}
	void printf()
	{
		cout << S << endl;
	}
};

int main()
{
	double x1, y1, x2, y2, x3, y3, x4, y4;
	Rectangle s;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	s.is_where(x1, y1, x2, y2, x3, y3);
	s.area();
	s.printf();
	s.printf_point();
	return 0;
}