#include "Ctrl.h"

Ctrl::Ctrl()
{
	this->type = 0;
	this->startx = 0;
	this->starty = 0;
	this->width = 0;
	this->height = 0;
	this->context = "";
}

Ctrl::Ctrl(int type,int startx, int starty, int width, int height, string context)
{
	this->type = type;
	this->startx = startx;
	this->starty = starty;
	this->width = width;
	this->height = height;
	this->context = context;
}

Ctrl::~Ctrl()
{
	
}
//--------Geter-----------------------------------------------
int Ctrl::GetType()
{
	return this->type;
}
int Ctrl::GetX()
{
	return this->startx;
}
int Ctrl::GetY()
{
	return this->starty;
}
int Ctrl::GetWidth()
{
	return this->width;
}
int Ctrl::GetHeight()
{
	return this->height;
}
string Ctrl::GetContext()
{
	return this->context;
}

//--------Seter-----------------------------------------------
void Ctrl::SetType(int type)
{
	this->type = type;
}
void Ctrl::SetX(int startx)
{
	this->startx = startx;
}
void Ctrl::SetY(int starty)
{
	this->starty = starty;
}
void Ctrl::SetWidth(int width)
{
	this->width = width;
}
void Ctrl::SetHeight(int height)
{
	this->height = height;
}
void Ctrl::SetContext(string context)
{
	this->context = context;
}

