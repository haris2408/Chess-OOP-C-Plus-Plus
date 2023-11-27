#include "Piece.h"
#include"board.h"

Piece::Piece()
{
	clrr = white;
}

Piece::Piece(position h_position, Color h_co,board* h_board)
{
	this->P = h_position;
	this->clrr = h_co;
	this->bord = h_board;
}
void Piece::move(position End)
{
	position temp = this->P;
	this->P = End;
	this->bord->move(temp, End);
}
void Piece::erase()
{
	gotoRowCol(this->P.getr(), this->P.getc());
	cout << "-";
}
Color Piece::getcolor()
{
	return this->clrr;
}
void Piece::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Piece::changeColor(Color clrr)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clrr);
}
bool Piece::IsVerticalMove(position end)
{
	return this->P.getc() == end.getc();
}
bool Piece::IsHorizontalMove(position end)
{
	return this->P.getr() == end.getr();
}
bool Piece::IsDiagonalMove(position end)
{
	int deltaR = end.getr() - this->P.getr();
	int deltaC = end.getc() - this->P.getc();
	return (abs(deltaR) == abs(deltaC));
}
bool Piece::IsVerticalPathClear(position end)
{
	if (this->P.getr() > end.getr())
	{
		for (int r = this->P.getr() - 1; r > end.getr(); r--)
		{
			if (this->bord->GetPiece(r, end.getc()) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		for (int r = this->P.getr() + 1; r < end.getr(); r++)
		{
			if (this->bord->GetPiece(r, end.getc()) != nullptr)
				return false;
		}
		return true;
	}
}
bool Piece::IsHorizontalPathClear(position end)
{
	if (this->P.getc() > end.getc())
	{
		for (int c = this->P.getc() - 1; c > end.getc(); c--)
		{
			if (this->bord->GetPiece(end.getr(), c) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		for (int c = this->P.getc() + 1; c < end.getc(); c++)
		{
			if (this->bord->GetPiece(end.getr(), c) != nullptr)
				return false;
		}
		return true;
	}
}
bool Piece::IsDiagonalPathClear(position end)
{
	int deltaR = end.getr() - this->P.getr();
	int deltaC = end.getc() - this->P.getc();
	if (deltaR > 0 && deltaC < 0)
	{
		for (int r = 1; r < deltaR; r++)
		{
			if ((this->bord->GetPiece(this->P.getr() + r,this->P.getr() - r) != nullptr) )
				return false;
		}
		return true;
	}
	else if (deltaC > 0 && deltaR < 0)
	{
		for (int r = 1; r < deltaC; r++)
		{
			if ((this->bord->GetPiece(this->P.getr() - r, this->P.getc() + r) != nullptr))
				return false;
		}
		return true;
	}
	else if (deltaC > 0 && deltaR > 0)
	{
		for (int r = 1; r < deltaR; r++)
		{
			if ((this->bord->GetPiece(this->P.getr() + r, this->P.getc() + r) != nullptr))
				return false;
		}
		return true;
	}
	else if (deltaC < 0 && deltaR < 0)
	{
		for (int r = 1; r < deltaR; r++)
		{
			if ((this->bord->GetPiece(this->P.getr() - r, this->P.getc() - r) != nullptr))
				return false;
		}
		return true;
	}
	return false;
}
