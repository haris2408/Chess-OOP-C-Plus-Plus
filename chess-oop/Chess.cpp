#include "Chess.h"
#include <fstream>
Chess::Chess()
{
	this->SGI = 0;
}
void Chess::displaymsg()
{
	Piece::changeColor(bwhite);
	Piece::gotoRowCol(84, 90);
	if (game.getTurn() == black)
		cout << "Yellow's Turn\n";
	else
		cout << "Red's Turn\n";
}
void Chess::Replay()
{
	for (int i = 0; i <= this->SGI; i++)
	{
		this->game.LoadBoard(this->savedG[i]);
		this->game.displayBoard();
		Sleep(2000);
	}
}
void Chess::saveTurnfile(char arr[8][8])
{
	ofstream fout("saved_game.txt");
	if (this->game.getTurn() == black)
		fout << 1;
	else
		fout << 0;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			fout << arr[r][c];
		}
	}
}
bool Chess::startScreen()
{
	char x;
	Piece::changeColor(bwhite);
	do
	{
		Piece::gotoRowCol(15, 50);
		cout << "CHESS";
		Piece::gotoRowCol(18, 50);
		cout << "Saved Game(Y)or New Game(N): ";
		cin >> x;
		if (x == 'Y' || x == 'y')
		{
			Piece::changeColor(bblack);
			return true;
		}
		else if (x == 'N' || x == 'n')
		{
			Piece::changeColor(bblack);
			return false;
		}
	} while (true);
}
void Chess::InitFile()
{
	ifstream fin("saved_game.txt");
	char B[8][8];
	int t;
	fin >> t;
	if (t == 1)
		this->game.setTurn(black);
	else
		this->game.setTurn(white);
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			fin >> B[ri][ci];
		}
	}
	this->game.LoadBoard(B);
}
void Chess::PawnPromotion(char arr[8][8])
{
	char select;
	if ((arr[this->E.getr()][this->E.getc()] == 'p' && this->E.getr() == 0) || (arr[this->E.getr()][this->E.getc()] == 'P' && this->E.getr() == 7))
	{
		do
		{
			Piece::changeColor(bwhite);
			Piece::gotoRowCol(30, 85);
			cout << "Congratulations!!!You can Now Promote Your Pawn to Queen,Rook,Horse,or Bishop(Q,R,H,B)";
			Piece::gotoRowCol(31, 85);
			cout << "Answer : ";
			cin >> select;
		} while (select != 'Q' && select != 'R' && select != 'H' && select != 'B' && select != 'q' && select != 'h' && select != 'r' && select != 'b');
		switch (select)
		{
		case 'Q':
		case 'q':
			if (arr[this->E.getr()][this->E.getc()] == 'p')
				arr[this->E.getr()][this->E.getc()] = 'q';
			else
				arr[this->E.getr()][this->E.getc()] = 'Q';
			break;
		case 'R':
		case 'r':
			if (arr[this->E.getr()][this->E.getc()] == 'p')
				arr[this->E.getr()][this->E.getc()] = 'r';
			else
				arr[this->E.getr()][this->E.getc()] = 'R';
			break;
		case 'H':
		case 'h':
			if (arr[this->E.getr()][this->E.getc()] == 'p')
				arr[this->E.getr()][this->E.getc()] = 'h';
			else
				arr[this->E.getr()][this->E.getc()] = 'H';
			break;
		case 'B':
		case 'b':
			if (arr[this->E.getr()][this->E.getc()] == 'p')
				arr[this->E.getr()][this->E.getc()] = 'b';
			else
				arr[this->E.getr()][this->E.getc()] = 'B';
			break;
		}
		Piece::gotoRowCol(30, 85);
		cout << "                                                                                      ";
		Piece::gotoRowCol(31, 85);
		cout << "             ";
		this->game.LoadBoard(arr);
	}

}
void Chess::play()
{
	int tgi = 0;
	bool ch = this->startScreen();
	if (ch == true)
	{
		this->InitFile();
	}
	else
	{
		this->game.init();
		this->game.setTurn((rand() % 2 == 0) ? white : black);
	}
	
	int t1;
	while (1)
	{
		do
		{ 
			this->game.displayBoard();
			this->game.DisplayButtons();
			displaymsg();
			t1 = time(0);
			do
			{
				game.selectPiece(this->S);
			} while (game.PieceSelectedIsValid(this->S)==false);
			if ((S.getr() >= 5 && S.getr() <= 6) && ((S.getc() >= 9 && S.getc() <= 10) || (S.getc() >= 11 && S.getc() <= 12) || (S.getc() >= 13 && S.getc() <= 14)))
				break;
			this->game.Highlight(this->S);
			this->game.PrintHighlight();
			Piece::gotoRowCol(84, 0);
			cout << "Select Destination\n";
			game.selectDestination(this->E);
			if (game.DestinationSelectedIsValid(this->S, this->E) == false)
			{
				Piece::gotoRowCol(84, 0);
				cout << "\wrong destination";
			}
		} while (game.DestinationSelectedIsValid(this->S, this->E)==false);
		int t2 = time(0);
		if ((t2 - t1) > 60)
		{
			Piece::gotoRowCol(40, 85);
			cout << "More than 60 seconds taken for turn\n";
			Sleep(3000);
			break;
		}
		if (S.getc() >= 9 && S.getc() <= 10)
		{
			if (this->SGI-1 < 0)
			{
				Piece::gotoRowCol(61, 90);
				cout << "Undo Denied";
			}
			else
			{
				Piece::gotoRowCol(61, 85);
				cout << "           ";
				this->game.LoadBoard(this->savedG[this->SGI - 1]);
				this->SGI--;
			}
		}
		else if (S.getc() >= 11 && S.getc() <= 12)
		{
			if (this->SGI + 1 > tgi)
			{
				Piece::gotoRowCol(61, 110);
				cout << "Redo Denied";
			}
			else
			{
				Piece::gotoRowCol(61, 85);
				cout << "           ";
				this->game.LoadBoard(this->savedG[this->SGI + 1]);
				this->SGI++;
			}
		}
		else if (S.getc() >= 13 && S.getc() <= 14)
		{
			this->Replay();
		}
		else
		{
			if (this->game.GetPiece(this->S.getr(), this->S.getc())->islegal(this->E))
			{
				game.GetPiece(this->S.getr(), this->S.getc())->move(this->E);
				int sr = this->S.getr() * 10, sc = this->S.getc() * 10;
				if (this->S.getr() == 0 || this->S.getr() % 2 == 0)
				{
					if (this->S.getc() == 0 || this->S.getc() % 2 == 0)
						this->game.PrintfilBox(sr, sc, 10, bwhite);
					else
						this->game.PrintfilBox(sr, sc, 10, bblack);
				}
				else
				{
					if (this->S.getc() == 0 || this->S.getc() % 2 == 0)
						this->game.PrintfilBox(sr, sc, 10, bblack);
					else
						this->game.PrintfilBox(sr, sc, 10, bwhite);
				}
				this->game.SaveBoard(this->savedG[this->SGI]);
				this->PawnPromotion(this->savedG[this->SGI]);
				this->saveTurnfile(this->savedG[this->SGI]);
				this->SGI++;
				tgi++;
				game.AlterTurn();
			}
			else
			{
				cout << "\nInvalid move\n";
			}
		}
		
	}
	system("Cls");
	if (this->game.getTurn() == black)
		cout << "white wins";
	else
		cout << "black wins";
}