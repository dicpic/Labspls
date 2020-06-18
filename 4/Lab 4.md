


МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования<br>
<br/><br/>

### Отчёт по лабораторной работе №4<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(2)
Решетника Даниила Сергеевича
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
## Лабораторная работа №4
**Цель:**

1. Закрепить навыки работы с перечислениями;<br>
2. Закрепить навыки работы с структурами;<br>
3. Освоить методы составления многофайловых программ.

**Ход работы:**

1. Файл, реализующий саму игру "Иксики-нолики" с функциями из вспомогательного файла:
```cpp
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
```
2. Вспомогательный файл:
```cpp
#include "pch.h"
#include<iostream>
#include"xxx.h"
#include<ctime>

Game initGame(char userChar) 
{
	Game f;
	for (int i = 0; i < size; i++) 
	{ 
		for (int j = 0; j < size; j++) 
		{
			f.board[i][j] = ' ';
		}
	}

	if (userChar == 'o')
	{
		f.botChar = 'x'; 
		f.isUserTurn = true;
	}
	else
	{
		f.botChar = 'o';
		f.isUserTurn = false;
	}

	f.status = PLAY;
	f.userChar = userChar;

	return f;
}

void updateDisplay(const Game game)
{
	system("cls"); 
	std::cout << "\n          ";
	for (int j = 0; j < size; j++) 
	{
		std::cout << "-+--";
	}
	std::cout << "-+-\n          ";
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			std::cout <<" | " << game.board[i][j];
		}
		std::cout << " | \n          ";
		for (int j = 0; j < size; j++) 
		{
			std::cout << "-+--";
		}
		std::cout << "-+-\n          ";
	}

}

void botTurn(Game* game) 
{
	bool empty = true;
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			if (game->board[i][j] != ' ') empty = false;
		}
	}
	if (empty) 
	{
		game->board[int(size/2)][int(size / 2)] = game->botChar;
		return;
	}

	for (int i = 0; i < size; i++) {
		int kol = 0;
		for (int j = 0; j < size; j++) {
			if (game->board[i][j] == game->userChar) 
			{
				kol++;
				if (kol == size - 1) {
					for (int k = 0; k < size; k++)
					{
						if (game->board[i][k] == ' ') 
						{
							game->board[i][k] = game->botChar;
							return;
						}
					}
				}
			}
		}
	}

	for (int j = 0; j < size; j++)
	{
		int kol = 0;
		for (int i = 0; i < size; i++) 
		{
			if (game->board[i][j] == game->userChar) 
			{
				kol++;
				if (kol == size - 1) 
				{
					for (int k = 0; k < size; k++) 
					{
						if (game->board[k][j] == ' ') 
						{
							game->board[k][j] = game->botChar;
							return;
						}
					}
				}
			}
		}
	}

	int diag = 0;
	for (int i = 0; i < size; i++)
	{
		if (game->board[i][i] == game->userChar) diag++;
		if (diag == size - 1) {
			for (int k = 0; k < size; k++)
			{
				if (game->board[k][k] == ' ') 
				{
					game->board[k][k] = game->botChar;
					return;
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (game->board[i][size - 1 - i] == game->userChar) diag++;
		if (diag == size - 1) 
		{
			for (int k = 0; k < size; k++)
			{
				if (game->board[k][size - 1 - k] == ' ') 
				{
					game->board[k][size - 1 - k] = game->botChar;
					return;
				}
			}
		}
	}

	int randX;
	int randY;
	do {
		randX = rand() % size;
		randY = rand() % size;
	} while (game->board[randX][randY] != ' ');

	game->board[randX][randY] = game->botChar;
}


void userTurn(Game* game) {
	while (true) {
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		std::cout << "\n Введите координаты (x, y): ";
		int x; int y;
		std::cin >> x >> y;
		if ((x < 1 || x > size) || (y < 1 || y > size) || (game->board[y - 1][x - 1] != ' ')) 
		{
			std::cout << "\n Here we go again";
			continue;
		}
		game->board[y - 1][x - 1] = game->userChar;
		break;

	}
}

bool updateGame(Game* game) {

	game->isUserTurn = !game->isUserTurn;

	for (int i = 0; i < size; i++)
	{
		int j[4] = {0};
		if (game->board[i][i] != ' ')
		{
			while (game->board[j[0]][i] == game->board[i][i])
				j[0] += 1;
			while (game->board[i][j[1]] == game->board[i][i])
				j[1] += 1;
			while (game->board[j[2]][j[2]] == game->board[i][i])
				j[2] += 1;
			while (game->board[size - 1 - j[3]][j[3]] == game->board[i][i])
				j[3] += 1;
			if ((j[0] - 1 == size)|| (j[1] - 1 == size) || (j[2] == size) || (j[3] == size))
			{
				if (game->board[i][i] == game->userChar) game->status = UWIN;
				else game->status = BWIN;
				return true;
			}
		}
		for (int j = 0; j < size; j++)
		{
			if (game->board[i][j] == ' ') return false;
		}
	}
	return true;
}
```

3. Заголовочный файл, который необходим для связи главного и вспомогательного файла:

```cpp
#pragma once
int const size = 3; //можно менять размер поля

enum Status {
	PLAY,            
	UWIN,        
	BWIN,         
};

struct Game {
	char board[size][size];  
	bool isUserTurn;  
	char userChar;    
	char botChar;     
	Status status;
};

Game initGame(char userChar);

void updateDisplay(const Game game);

void botTurn(Game* game);

void userTurn(Game* game);

bool updateGame(Game* game);
```
**Вывод:** На данной лабораторной работе, я закрепил навыки работы с перечислениями и структурами и освоил методы составления многофайловых систем.
