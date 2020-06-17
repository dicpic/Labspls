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
		std::cout << "\n ¬ведите координаты (x, y): ";
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