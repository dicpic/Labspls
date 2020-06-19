#include"pch.h"
#include<iostream>
#include<cmath>
#include<conio.h>

int main() 
{

	double a, b, X0, Xn, dx, max, min;
	int i = 0;
	double mas[228];

	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	std::cout << "X0 = ";
	std::cin >> X0;
	std::cout << "dX = ";
	std::cin >> dx;
	std::cout << "Xn = ";
	std::cin >> Xn;

	for (double x = X0; x <= Xn + dx; x += dx, i++) 
	{
		if (x <= a) 
			mas[i] = log(x) + abs(x);
		else if (x < b) 
			mas[i] = pow(x,3.3)*cos(x);
			else 
			mas[i] = pow(x,4);

		if (i == 0) 
		{
			max = mas[0];
			min = mas[0];
		}
		if (mas[i] > max)
			max = mas[i];
		if (mas[i] < min)
			min = mas[i];

		std::cout << "\nmas[" << i << "] = " << mas[i];
	}

	std::cout << "\nZmax = " << max;
	std::cout << "\nZmin = " << min;

	_getch();
}