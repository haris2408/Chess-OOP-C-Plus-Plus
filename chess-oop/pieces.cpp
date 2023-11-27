#include "pieces.h"
#include"board.h"


//PAWN
bool pawn::Isfrwrdmove(position End)
{
	if (this->bord->getTurn() == black)
	{
		return (End.getr() - this->P.getr() > 0 && End.getr() - this->P.getr() == 1);
	}
	else if (this->bord->getTurn() == white)
	{
		return (End.getr() - this->P.getr() < 0 && End.getr() - this->P.getr() == -1);
	}
	else
		return false;
}
pawn::pawn()
	:Piece()
{

}
pawn::pawn(position h_position, Color h_co, board* h_board)
	:Piece(h_position,h_co,h_board)
{
	isfirst = true;
}
bool pawn::islegal(position End)
{
	if (this->bord->getTurn() == white && (End.getr() > this->P.getr()))
		return false;
	else if (this->bord->getTurn() == black && (End.getr() < this->P.getr()))
		return false;
	int deltaR = abs(End.getr() - this->P.getr());
	int deltaC = abs(End.getc() - this->P.getc());
	if ((this->P.getr() == 1 || this->P.getr() == 6)&&(this->P.getc()==End.getc()) && (deltaR == 1 || deltaR == 2) && (this->bord->iskillhapen(End) == false))
	{
		if ((this->bord->getTurn() == black && (this->P.getr() < End.getr()) && (End.getr() - 1 == this->P.getr() || End.getr() - 2 == this->P.getr()))
			|| (this->bord->getTurn() == white && (this->P.getr() > End.getr()) && (End.getr() == this->P.getr() - 1 || End.getr() == this->P.getr() - 2)))
		{
			if (this->P.getr() == 1)
			{
				if (deltaR == 2)
				{
					return (this->bord->GetPiece(this->P.getr() + 1, this->P.getc()) == nullptr);
				}
				else
					return true;
			}
			if (this->P.getr() == 6)
			{
				if (deltaR == 2)
				{
					return (this->bord->GetPiece(this->P.getr() - 1, this->P.getc()) == nullptr);
				}
				else
					return true;
			}
		}
	}
	else if ((deltaR == 1) && (deltaC == 0) && (this->bord->iskillhapen(End) == false))
	{
		if (((this->bord->getTurn() == black && (this->P.getr() < End.getr()) && (End.getr() - 1 == this->P.getr()) && (this->P.getr() != 1)) || (this->bord->getTurn() == white && (this->P.getr() > End.getr()) && (End.getr() == this->P.getr() - 1)) && (this->P.getr() != 6)) && (this->Isfrwrdmove(End)))
		{
			return true;
		}
	}
	else if ((deltaR == 1) && (deltaC == 1) && (this->bord->iskillhapen(End) == true))
	{
		if ((this->bord->getTurn() == black && (this->P.getr() < End.getr())) || (this->bord->getTurn() == white && (this->P.getr() > End.getr())))
			return true;
	}
	else
		return false;
}
void pawn::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 3;
	sc = this->P.getc() * 10 + 2;
	gotoRowCol(sr, sc + 2);
	cout << s << s << s;
	gotoRowCol(sr + 1, sc + 2);
	cout << s << s << s;
	gotoRowCol(sr + 2, sc + 3);
	cout << s;
	gotoRowCol(sr + 3, sc + 3);
	cout << s;
	gotoRowCol(sr + 4, sc + 2);
	cout << s << s << s;
}
char pawn::GetSym()
{
	if (this->clrr == black)
		return 'P';
	else
		return 'p';
}

//CASTLE
castle::castle()
	:Piece()
{

}
castle::castle(position h_position, Color h_co, board* h_board)
	:Piece(h_position, h_co, h_board)
{
	isfirst = true;
}
bool castle::islegal(position End)
{
	return ((this->IsHorizontalMove(End) && this->IsHorizontalPathClear(End))||(this->IsVerticalMove(End) && this->IsVerticalPathClear(End)));
}
void castle::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 2;
	sc = this->P.getc() * 10 + 1;
	gotoRowCol(sr, sc + 2);
	cout << s << s << s << s << s;
	gotoRowCol(sr + 1, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 2, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 3, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 4, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 5, sc + 2);
	cout << s << s << s << s << s;
}
char castle::GetSym()
{
	if (this->clrr == black)
		return 'C';
	else
		return 'c';
}

//KNIGHT
knight::knight()
	:Piece()
{

}
knight::knight(position h_position, Color h_co, board* h_board)
	:Piece(h_position, h_co, h_board)
{
}
bool knight::islegal(position End)
{
	int deltaR = abs(End.getr() - this->P.getr());
	int deltaC = abs(End.getc() - this->P.getc());
	return ((deltaR == 2 && deltaC == 1) || (deltaR == 1 && deltaC == 2));
}
void knight::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 2;
	sc = this->P.getc() * 10 + 2;
	gotoRowCol(sr, sc + 2);
	cout << s << s << s << s;
	gotoRowCol(sr + 1, sc + 1);
	cout << s << s << s << s;
	gotoRowCol(sr + 2, sc);
	cout << s << s << s << s << s;
	gotoRowCol(sr + 3, sc + 1);
	cout << s << s << s << s;
	gotoRowCol(sr + 4, sc + 3);
	cout << s << s;
	gotoRowCol(sr + 5, sc + 3);
	cout << s << s;
	gotoRowCol(sr + 6, sc + 1);
	cout << s << s << s << s << s;
}
char knight::GetSym()
{
	if (this->clrr == black)
		return 'H';
	else
		return 'h';
}

//BISHOP
bishop::bishop()
	:Piece()
{

}
bishop::bishop(position h_position, Color h_co, board* h_board)
	:Piece(h_position, h_co, h_board)
{
}
bool bishop::islegal(position End)
{
	return (this->IsDiagonalMove(End)&&this->IsDiagonalPathClear(End));
}
void bishop::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 1;
	sc = this->P.getc() * 10 + 1;
	gotoRowCol(sr, sc + 4);
	cout << s;
	gotoRowCol(sr + 1, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 2, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 3, sc + 4);
	cout << s;
	gotoRowCol(sr + 4, sc + 4);
	cout << s;
	gotoRowCol(sr + 5, sc + 4);
	cout << s;
	gotoRowCol(sr + 6, sc + 3);
	cout << s << s << s;
}
char bishop::GetSym()
{
	if (this->clrr == black)
		return 'B';
	else
		return 'b';
}

//QUEEN
queen::queen()
	:Piece()
{

}
queen::queen(position h_position, Color h_co, board* h_board)
	:Piece(h_position, h_co, h_board)
{
}
bool queen::islegal(position End)
{
	if(IsVerticalMove(End) && IsVerticalPathClear(End))
	{
		return true;
	}
	else if (IsHorizontalMove(End) && IsHorizontalPathClear(End))
	{
		return true;
	}
	else if (IsDiagonalMove(End) && IsDiagonalPathClear(End))
	{
		return true;
	}
	return false;
}
void queen::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 2;
	sc = this->P.getc() * 10 + 1;
	gotoRowCol(sr, sc + 2); cout << s;
	gotoRowCol(sr, sc + 4); cout << s;
	gotoRowCol(sr, sc + 6); cout << s;
	gotoRowCol(sr + 1, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 2, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 3, sc + 4);
	cout << s;
	gotoRowCol(sr + 4, sc + 4);
	cout << s;
	gotoRowCol(sr + 5, sc + 4);
	cout << s;
	gotoRowCol(sr + 6, sc + 3);
	cout << s << s << s;
}
char queen::GetSym()
{
	if (this->clrr == black)
		return 'Q';
	else
		return 'q';
}

//KING
king::king()
	:Piece()
{

}
king::king(position h_position, Color h_co, board* h_board)
	:Piece(h_position, h_co, h_board)
{
}
bool king::islegal(position End)
{
	int deltaR = abs(End.getr() - this->P.getr());
	int deltaC = abs(End.getc() - this->P.getc());
	if ((deltaR>=0&& deltaR<=1)&&(deltaC >= 0 && deltaC <= 1))
		return true;
	return false;
}
void king::draw()
{
	char s = -37;
	changeColor(this->clrr);
	int sr, sc;
	sr = this->P.getr() * 10 + 1;
	sc = this->P.getc() * 10 + 1;
	gotoRowCol(sr, sc + 4);
	cout << s;
	gotoRowCol(sr + 1, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 2, sc + 4);
	cout << s;
	gotoRowCol(sr + 3, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 4, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 5, sc + 3);
	cout << s << s << s;
	gotoRowCol(sr + 6, sc + 4);
	cout << s;
	gotoRowCol(sr + 7, sc + 3);
	cout << s << s << s;
}
char king::GetSym()
{
	if (this->clrr == black)
		return 'K';
	else
		return 'k';
}