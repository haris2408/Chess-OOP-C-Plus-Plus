#include"Piece.h"
#include"pieces.h"
#pragma once

class board
{
protected:
	Piece* B[8][8];
	Color turn;
	friend Piece;
	char HIGH[8][8];
	void printGrid();
public:
	board();
	void init();
	void displayBoard();
	void move(position start, position end);
	void selectPiece(position& obj);
	void selectDestination(position& obj);
	void PrintHollowBox(int sr, int sc, Color cc);
	void Highlight(position obj);
	void PrintHighlight();
	bool PieceSelectedIsValid(position obj);
	bool DestinationSelectedIsValid(position objS, position objE);
	bool iskillhapen(position End);
	Piece* GetPiece(int ri, int ci);
	Color getTurn();
	void setTurn(Color obj);
	void PrintfilBox(int sr, int sc, int size, Color cc);
	void AlterTurn();
	void SaveBoard(char arr[8][8]);
	void LoadBoard(char arr[8][8]);
	void PrintMsg(int r, int c, const char ms[], int co);
	void DisplayButtons();
	~board() {  }
};

