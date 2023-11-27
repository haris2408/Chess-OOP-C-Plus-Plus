#include "board.h"
#include"pieces.h"
board::board()
{
	
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void board::setTurn(Color obj)
{
	this->turn = obj;
}
void board::init()
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (ri == 1)
			{
				this->B[ri][ci] = new pawn(position(ci, ri), black, this);
			}
			else if (ri == 6)
			{
				this->B[ri][ci] = new pawn(position(ci, ri), white, this);
			}
			else
			{
				this->B[ri][ci] = nullptr;
			}
		}
	}
	B[0][0] = new castle(position(0, 0), black, this);
	B[0][7] = new castle(position(7, 0), black, this);
	B[0][1] = new knight(position(1, 0), black, this);
	B[0][6] = new knight(position(6, 0), black, this);
	B[0][2] = new bishop(position(2, 0), black, this);
	B[0][5] = new bishop(position(5, 0), black, this);
	B[0][3] = new queen(position(3, 0), black, this);
	B[0][4] = new king(position(4, 0), black, this);

	B[7][0] = new castle(position(0, 7), white, this);
	B[7][7] = new castle(position(7, 7), white, this);
	B[7][1] = new knight(position(1, 7), white, this);
	B[7][6] = new knight(position(6, 7), white, this);
	B[7][2] = new bishop(position(2, 7), white, this);
	B[7][5] = new bishop(position(5, 7), white, this);
	B[7][3] = new queen(position(3, 7), white, this);
	B[7][4] = new king(position(4, 7), white, this);
}
void board::PrintfilBox(int sr, int sc, int size,Color cc)
{
	char s = -37;
	Piece::changeColor(cc);
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			Piece::gotoRowCol(sr + r, sc + c);
			cout << s;
		}
	}
}
void board::printGrid()
{
	int size = 10;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			int sr = r * size, sc = c * size;
			if (r == 0 || r % 2 == 0)
			{
				if (c == 0 || c % 2 == 0)
					PrintfilBox(sr, sc, size, bwhite);
				else
					PrintfilBox(sr, sc, size, bblack);
			}
			else
			{
				if (c == 0 || c % 2 == 0)
					PrintfilBox(sr, sc, size, bblack);
				else
					PrintfilBox(sr, sc, size, bwhite);
			}
		}
	}
}
void board::displayBoard()
{
	printGrid();
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (this->B[ri][ci] == nullptr)
				continue;
			else
				this->B[ri][ci]->draw();
		}
		cout << endl;
	}
	cout << endl;
}
void board::move(position start, position end)
{
	this->B[end.getr()][end.getc()] = this->B[start.getr()][start.getc()];
	this->B[end.getr()][end.getc()]->draw();
	this->B[start.getr()][start.getc()] = nullptr;
}

void board::AlterTurn()
{
	if (turn == white)
		this->turn = black;
	else
		this->turn = white;
}
void board::selectPiece(position& obj)
{
	int sri, sci;
	Piece::changeColor(bwhite);
	bool ch = false;
	
		Piece::gotoRowCol(84, 0);
		cout << "\nSelect Piece\n";
		getRowColbyLeftClick(sri, sci);
		/*if ((sri >= 50 && sri <= 55) && (sci >= 85 && sci <= 100))
			return;*/
		sri = sri / 10;
		sci = sci / 10;
	obj.setr(sri);
	obj.setc(sci);
}
void board::selectDestination(position& obj)
{
	int dri, dci;
	Piece::changeColor(bwhite);
	bool ch = false;
	do
	{
		Piece::gotoRowCol(84, 0);
		cout << "Select Destination                     ";
		getRowColbyLeftClick(dri, dci);
		
		for (int ri = 0; ri < 80; ri += 10)
		{
			for (int ci = 0; ci < 80; ci += 10)
			{
				if ((dri >= ri && dri <= ri + 10) && (dci >= ci && dci <= ci + 10))
				{
					ch = true;
					dri = ri / 10;
					dci = ci / 10;
				}
			}
		}
		if (!ch)
		{
			Piece::gotoRowCol(84, 0);
			cout << "Invalid Coordinate Select Agian!!!";

		}
	} while (ch == false);
	obj.setr(dri);
	obj.setc(dci);
}
bool board::PieceSelectedIsValid(position obj)
{
	if ((obj.getr() >= 5 && obj.getr() <= 6) && ((obj.getc() >= 9 && obj.getc() <= 10) || (obj.getc() >= 11 && obj.getc() <= 12)|| (obj.getc() >= 13 && obj.getc() <= 14)))
		return true;
	return(this->B[obj.getr()][obj.getc()] != nullptr && this->B[obj.getr()][obj.getc()]->getcolor() == this->turn);
}

bool board::DestinationSelectedIsValid(position objS, position objE)
{
	if (objE.getr() == objS.getr() && objE.getc() == objS.getc())
		return false;
	return(this->B[objE.getr()][objE.getc()] == nullptr || this->B[objE.getr()][objE.getc()]->getcolor() != this->turn);
}
Piece* board::GetPiece(int ri, int ci)
{
	return this->B[ri][ci];
}
Color board::getTurn()
{
	return this->turn;
}
bool board::iskillhapen(position End)
{
	if (this->B[End.getr()][End.getc()] != nullptr)
		return true;
	return false;
}
void board::Highlight(position obj)
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			this->HIGH[r][c] = ' ';
		}
	}
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			position E(c,r);
			if (this->DestinationSelectedIsValid(obj, E) && this->B[obj.getr()][obj.getc()]->islegal(E))
				this->HIGH[r][c] = '*';
			else
				this->HIGH[r][c] = ' ';

		}
	}
}
void board::PrintHighlight()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (this->HIGH[r][c] == '*')
			{
				this->PrintHollowBox(r * 10, c * 10, green);
			}
		}
	}
}
void board::PrintHollowBox(int sr, int sc, Color cc)
{
	char s = -37;
	Piece::changeColor(cc);
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if (r == 0 || r == 10 - 1)
			{
				Piece::gotoRowCol(sr + r, sc + c);
				cout << s;
			}
			else if (c == 0 || c == 10 - 1)
			{
				Piece::gotoRowCol(sr + r, sc + c);
				cout << s;
			}
		}
	}
}
void board::SaveBoard(char arr[8][8])
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (this->B[ri][ci] != nullptr)
				arr[ri][ci] = this->B[ri][ci]->GetSym();
			else
				arr[ri][ci] = '-';
		}
	}
}
void board::LoadBoard(char arr[8][8])
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (arr[ri][ci])
			{
			case 'P':
				this->B[ri][ci] = new pawn(position(ci, ri), black, this);
				break;
			case 'p':
				this->B[ri][ci] = new pawn(position(ci, ri), white, this);
				break;
			case 'C':
				this->B[ri][ci] = new castle(position(ci, ri), black, this);
				break;
			case 'c':
				this->B[ri][ci] = new castle(position(ci, ri), white, this);
				break;
			case 'H':
				this->B[ri][ci] = new knight(position(ci, ri), black, this);
				break;
			case 'h':
				this->B[ri][ci] = new knight(position(ci, ri), white, this);
				break;
			case 'B':
				this->B[ri][ci] = new bishop(position(ci, ri), black, this);
				break;
			case 'b':
				this->B[ri][ci] = new bishop(position(ci, ri), white, this);
				break;
			case 'Q':
				this->B[ri][ci] = new queen(position(ci, ri), black, this);
				break;
			case 'q':
				this->B[ri][ci] = new queen(position(ci, ri), white, this);
				break;
			case 'K':
				this->B[ri][ci] = new king(position(ci, ri), black, this);
				break;
			case 'k':
				this->B[ri][ci] = new king(position(ci, ri), white, this);
				break;
			case '-':
				this->B[ri][ci] = nullptr;
				break;
			}
		}
	}
}
void board::PrintMsg(int r, int c, const char ms[], int co)
{
	Piece::gotoRowCol(r, c);
	cout << ms;
}
void board::DisplayButtons()
{
	PrintMsg(40, 85, "THIS GAME IS ON AUTO SAVE!", 6);

	PrintfilBox(50, 90,10, cyan);
	PrintMsg(50, 90, "UNDO ", 8);

	PrintfilBox(50, 110,10, green);
	PrintMsg(50, 110, "REDO", 9);

	PrintfilBox(50, 130, 10, red);
	PrintMsg(50, 130, "REPLAY", 9);
}