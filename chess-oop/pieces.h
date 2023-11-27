#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include<time.h>
#include"Piece.h"
#pragma once
class pawn :
	public Piece
{
private:
	bool Isfrwrdmove(position End);
protected:
	bool isfirst;
public:
	pawn();
	pawn(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~pawn() {  }
};


class castle :
	 public Piece
{
protected:
	bool isfirst;
public:
	castle();
	castle(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~castle() {  }
};


class knight :
	public Piece
{
public:
	knight();
	knight(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~knight() {  }
};


class bishop :
	 public Piece
{

public:
	bishop();
	bishop(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~bishop() {  }
};


class queen :
	public Piece
{
public:
	queen();
	queen(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~queen() {  }
};


class king:
	public Piece
{
public:
	king();
	king(position h_position, Color h_co, board* h_board);
	virtual bool islegal(position End)override;
	virtual void draw();
	virtual char GetSym()override;
	~king() {  }
};