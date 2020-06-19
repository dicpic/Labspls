#include "pch.h"
#include <iostream>
#include"plswork.h"
#include<cstdlib>
#include<conio.h>

int main()
{
	BmpImg img;
	std::vector<int> binaryvector(0);

	img.read("pic10.bmp");

	int  height = img.get_height() - 1, width = img.get_width() - 1;

	for (int h = 0, w; h <= height; h++)
	{
		for (w = 0; w <= width; w++)
		{
			if (img.blue_at(h, w) % 2 != 0)
				binaryvector.push_back(1);
			else 
				binaryvector.push_back(0);
			
			if (img.green_at(h, w) % 2 != 0)
				binaryvector.push_back(1);
			else
				binaryvector.push_back(0);

			if (img.red_at(h, w) % 2 != 0)
				binaryvector.push_back(1);
			else
				binaryvector.push_back(0);
		}

	}

	char out = 0;

	//for (int i = 0; i < binaryvector.size() - 1; i++)
	//{
	//	if (i % 8 == 0)
	//		std::cout << " ";
	//	std::cout << binaryvector[i];
	//}

	for (int k = 1, d = 0; d != 8; k++)
	{
		if (binaryvector[k-1] == 0) 
		{
			out = out << 1;
			d++;
		}
		else 
		{
			out = out << 1;
			out++;
			d = 0;
		}
		if (k % 8 == 0) 
		{
			std::cout << out;
			out = 0;
		}
	}
	_getch();
}