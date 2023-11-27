#include"board.h"
#pragma once
class Chess
{
protected:
	position S, E;
	board game;
	char savedG[50][8][8];
	int SGI;
	void Replay();
	void saveTurnfile(char arr[8][8]);
	void InitFile();
	void PawnPromotion(char arr[8][8]);
	bool startScreen();
public:
	Chess();
	void play();
	void displaymsg();
};

