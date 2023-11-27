#pragma once
class position
{
protected:
	int r, c;
public:
	position() { r = 0, c = 0; }
	position(int x, int y);
	void setr(int r);
	void setc(int c);
	int getr();
	int getc();
	~position(){}

};

