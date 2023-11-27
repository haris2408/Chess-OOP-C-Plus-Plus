#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include<time.h>
#include "position.h"
#pragma once
class board;
enum Color { bwhite = 15, bblack = 0, white = 4, black = 6, cyan = 3, green = 2,red=12 };
using namespace std;


class Piece
{
protected:
	position P;
	Color clrr;
	board* bord;
	bool IsVerticalMove(position end);
	bool IsHorizontalMove(position end);
	bool IsDiagonalMove(position end);
	bool IsVerticalPathClear(position end);
	bool IsHorizontalPathClear(position end);
	bool IsDiagonalPathClear(position end);

public:
	Piece();
	Piece(position h_position, Color h_co,board* h_board);
	void move(position End);
	virtual bool islegal(position End) = 0;
	virtual void draw() = 0;
	virtual char GetSym() = 0;
	void erase();
	Color getcolor();
	static void gotoRowCol(int rpos, int cpos);
	static void changeColor(Color clrr);
	~Piece() {}
};

