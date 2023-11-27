#include "position.h"
position::position(int x, int y)
{
	this->r = y;
	this->c = x;
}
void position::setr(int r)
{
	this->r = r;
}
void position::setc(int c)
{
	this->c = c;
}
int position::getr() { return this->r; }
int position::getc() { return this->c; }