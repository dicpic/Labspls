#include "pch.h"
#include <iostream>
#include"plswork.h"
#include<cstdlib>
#include<conio.h>

int main()
{
	BmpImg img;
	setlocale(LC_ALL, "Russian");
	std::vector<int> arr(0);
	int i = 0, count = 0, count_main = 0;
	char output;
	img.read("pic10.bmp");
	const int width = img.get_width() - 1;
	const int height = img.get_height() - 1;

	for (int y = 0, x; y <= height; y++)
	{
		for (x = 0; x <= width; x++)
		{
			if (img.blue_at(x, y) % 2 != 0) 
				arr.push_back(1);
			else 
				arr.push_back(0);
			
			if (img.green_at(x, y) % 2 != 0)
				arr.push_back(1);
			else
				arr.push_back(0);
			if (img.red_at(x, y) % 2 != 0)
				arr.push_back(1);
			else
				arr.push_back(0);
		}

	}
	output = 0;
	for (int k = 0; i != 8; k++) {
		if (arr[k] == 0) {
			output = output << 1;
			i++;
		}
		else {
			output = output << 1;
			output++;
			i = 0;
		}
		if ((k + 1) % 8 == 0) {

			std::cout << output;
			output = 0;
		}
	}
	_getch();
}