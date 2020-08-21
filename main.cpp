#include <iostream>

/*
Note:


Even though the program itself is not too complex, one might be confused. In
that case, please just ask me to explain. I don't like writing comments that no
one will read.

*******************************************


The basic idea is that we can "zoom" in to the numberline until we find a number
that satisfies "a^n = r" or a number really close to it.

In order to "zoom" in, we need the limits. In other words, we need to define 3
numbers. u (upper limit) which is a number always larger than the number we're
looking for, l (lower limit) which is a number always smaller than the number
we're looking for and m (middle) a number in the middle of these limits.

To "zoom in" we just have to find where n is with respect to m. If n is bigger
than m m becomes the lower bound otherwise it becomes the upper bound. That
continues until either of the limits or m, become close enough or equal with n.

The complex struct was made to support 2nth root of a negative number and imaginary functions in general.
*/

#define PI 3.1415926535

struct complex
{
	double r;
	double i;
	complex() : r(0), i(0) {}
	complex(double r) : r(r), i(0) {}
	complex(double r, double i) : r(r), i(i) {}
	friend std::ostream &operator<<(std::ostream &os, const complex &n)
	{
		if (n.i != 0 && n.r == 0)
		{
			os << n.i << "i";
		}
		else if (n.i == 0 && n.r != 0)
		{
			os << n.r;
		}
		else if (n.i > 0 && n.r != 0)
		{
			os << n.r << " + " << n.i << "i";
		}
		else
		{
			os << n.r << " - " << n.i * (-1) << "i";
		}
		return os;
	}
	friend std::istream &operator>>(std::istream &in, complex &num)
	{
		std::string c;
		getline(in, c);
		std::string real = "0";
		std::string imag = "0";
		bool roi = 0;
		int isign = 1;
		for (int i = 0; i < c.length(); i++)
		{
			if (c[i] == '+')
			{
				roi = 1;
				c[i] = ' ';
			}
			else if (c[i] == '-' && i > 0)
			{
				isign = -1;
				roi = 1;
				c[i] = ' ';
			}
			else if (c[i] == 'i')
			{
				c[i] = ' ';
			}
			real[i] = (!roi) ? c[i] : ' ';
			imag[i] = (roi) ? c[i] : ' ';
		}
		num.r = std::stod(real);
		num.i = std::stod(imag) * isign;
		return in;
	}
};

const complex prec(complex);

double pow(double, int);
const double nthrootni(double, unsigned int);
int factorial(int);
double cos(double);
double sin(double);
double tan(double);
double arctan(double);
double arg(complex &);
const complex nthroot(complex &, unsigned int);

int main()
{
	complex c;
	unsigned int n;
	std::cout << "Enter the radical:\n";
	std::cin  >> c;
	std::cout << "\nEnter the degree of the root:\n";
	std::cin  >> n;
	std::cout << "\n\nThe root of degree"
           << n << " of " 
				     << c << " is:\n"
			 	     << prec(nthroot(c, n));
}

const complex prec(complex num)
{
	int c0 = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
	int ic0 = 0, ic1 = 0, ic2 = 0, ic3 = 0, ic4 = 0, ic5 = 0;
	int sign;
	if (num.r > 0)
	{
		sign = (num.r < 0) ? -1 : 1;
		num.r *= sign;
		for (;num.r > 1;  num.r -= 1)
		{
			++c0;
		}
		for (;num.r > 0.1;  num.r -= 0.1)
		{
			++c1;
		}
		for (;num.r > 0.01;  num.r -= 0.01)
		{
			++c2;
		}
		for (;num.r > 0.001;  num.r -= 0.001)
		{
			++c3;
		}
		for (;num.r > 0.0001;  num.r -= 0.0001)
		{
			++c4;
		}
		for (;num.r > 0.00001;  num.r -= 0.00001)
		{
			++c5;
		}
	}
	if (num.i > 0)
	{
		sign = (num.i < 0) ? -1 : 1;
		num.i *= sign;
		for (;num.i > 1;  num.i -= 1)
		{
			++ic0;
		}
		for (;num.i > 0.1;  num.i-= 0.1)
		{
			++ic1;
		}
		for (;num.i > 0.01;  num.i -= 0.01)
		{
			++ic2;
		}
		for (;num.i > 0.001;  num.i -= 0.001)
		{
			++ic3;
		}
		for (;num.i > 0.0001;  num.i -= 0.0001)
		{
			++ic4;
		}
		for (;num.i > 0.00001;  num.i -= 0.00001)
		{
			++ic5;
		}
	}
	if (c5 >= 5)
		++c4;
	if (ic5 >= 5)
		++ic4;
		
	if (num.i > 0)
	{
		num.i = (ic0 + ic1 * 0.1 + ic2 * 0.01 + ic3 * 0.001 + ic4 * 0.0001) * sign;
	}
	if (num.r > 0)
	{
		num.r = (c0 + c1 * 0.1 + c2 * 0.01 + c3 * 0.001 + c4 * 0.0001) * sign;
	}
	return num;
}

double pow(double base, int exp)
{
	if (exp == 0)
		return 1;
	else if (exp == 1)
		return base;
	else if (exp > 1)
	{
		double tbase = base;
		for (int i = 1; i < exp; i++)
		{
			base *= tbase;
		}
	}
	return base;
}

const double nthrootni(double r, unsigned int n)
{
	int sign; //sign of r (+/-).
	bool zerodec;
	//if true r is a decimal with 0 in front of it.
	(r < 0) ? sign = -1 : sign = 1;
	r *= sign;
	(r > 0 && r < 1) ? zerodec = 1 : zerodec = 0;
	double u = (zerodec) ? 1 : r;
	double l = r / (n * n);

	if (pow(l, n) == r)
		return l * sign;
	l /= l + 1;
	//Always smaller than the cube root of r.
	double m;
	for (int j = 0; j < 50; j++)
	{
		if (pow(u, n) == r)
			return u * sign;
		else if (pow(l, n) == r)
			return l * sign;
		m = (u + l) / 2;
		if (pow(m, n) == r)
			return m * sign;
		else if (pow(m, n) < r)
			l = m;
		else
		{
			u = m;
		}
	}
	return m * sign;
}

int factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
	{
		return 1;
	}
}

double cos(double x)
{
	double result = 0;
	for (int n = 0; n < 17; n++)
	{
		result += (pow(-1, n) / factorial(2 * n)) * pow(x, 2 * n);
	}
	return result;
}

double sin(double x)
{
	return cos(PI / 2 - x);
}

double tan(double x)
{
	return sin(x) / cos(x);
}

double arctan(double x)
{
	// tan(arctan(x)) = x
	int sign = (x < 0) ? -1 : 1;
	double u = PI / 2;
	double l = 0;
	if (tan(l) == x)
		return l;
	double m;
	for (int i = 0; i < 50; i++)
	{
		if (tan(u) == x)
			return u * sign;
		else if (tan(l) == x)
			return l * sign;
		m = (u + l) / 2;
		if (tan(m) == x)
			return m * sign;
		else if (tan(m) < x)
			l = m;
		else
		{
			u = m;
		}
	}
	return m * sign;
}

double arg(complex &num)
{
	if (num.i != 0)
	{
		return 2 * arctan((nthrootni(num.r * num.r + num.i * num.i, 2) - num.r) / num.i);
	}
	else if (num.r < 0 && num.i == 0)
	{
		return PI;
	}
	else
	{
		return 0;
	}
}

const complex nthroot(complex &num, unsigned int n)
{
	if (num.i == 0)
	{
		bool i = ((n % 2 == 0) && (num.r < 0)) ? 1 : 0;

		int sign = (num.r < 0) ? -1 : 1;
		num.r *= sign;
		bool zerodec = 
			(num.r > 0 && num.r < 1) ? 1 : 0;
			

		double u = (zerodec) ? 1 : num.r;
		double l = num.r / (n * n);

		if (pow(l, n) == num.r)
			return (i) ? 
				complex(0, l) : 
				complex(l * sign);
				
		l /= l + 1;
		// Always smaller than the cube root of r.
		double m;
		for (int j = 0; j < 50; j++)
		{
			if (pow(u, n) == num.r)
				return (i) ? 
					complex(0, u) : 
					complex(u * sign);

			else if (pow(l, n) == num.r)
				return (i) ?
			    	 complex(0, m) : 
			    	 complex(l * sign);
			    	 
			m = (u + l) / 2;
			if (pow(m, n) == num.r)
				return (i) ? 
					complex(0, m) : 
					complex(m * sign);

			else if (pow(m, n) < num.r)
				l = m;
			else
			{
				u = m;
			}
		}
		return (i) ? 
			complex(0, m) :
		     complex(m * sign);
	}
	else
	{
		double phi = arg(num);
		double abs = nthrootni(num.r * num.r + num.i * num.i, 2);
		
		return complex(
			nthrootni(abs, n) * cos(phi / n), 
			nthrootni(abs, n) * sin(phi / n)
		);
	}
}
