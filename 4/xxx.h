#pragma once

int const size = 3;

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