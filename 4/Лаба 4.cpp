
#include "pch.h"
#include <iostream>
#include"xxx.h"
#include <conio.h>

int main()
{
	bool again = 1;
	while(again)
	{
		setlocale(LC_ALL, "Russian");
		char sign;
		system("cls");
		std::cout << "\n  X или O?: ";
		std::cin >> sign;
		Game f = initGame(sign);

		while (true)
		{
			updateDisplay(f);
			if (f.isUserTurn) userTurn(&f);
			else botTurn(&f);
			if (updateGame(&f) == true)
			{
				updateDisplay(f);
				break;
			}
		}

		switch (f.status)
		{
		case UWIN:
			system("cls");
			std::cout << "\n YOU WIN";
			_getch();
			break;
		case BWIN:
			system("cls");
			std::cout << "\n YOU LOSE";
			_getch();
			break;
		default:
			system("cls");
			std::cout << "\n DRAW";
			_getch();
			break;
		}
		system("cls");
		std::cout << "\n  Wanna try again? (X или O): ";
		char ans;
		std::cin >> ans;
		switch (ans)
		{
		case 'x': 
			again = 1;
			break;
		case 'o': 
			again = 0;
			break;
		}
	}
}