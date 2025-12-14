#include "Label.h"

Label::Label():Ctrl()
{
	
}

Label::Label(int type,int startx, int starty, int width, int height, char* context)
:Ctrl( type, startx, starty, width, height, context)
{
	
}

Label::~Label()
{
	
}

//-------------------Show---------------------------------------
void Label::showCtrl()
{
	Tool::gotoxy(this->startx, this->starty);
	cout<< this->context;
}
