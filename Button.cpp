#include "Button.h"

Button::Button():Ctrl()
{
	this->showmode = 0;
	this->isFocused = false;
}
Button::Button(int type,int startx, int starty, int width, int height, char* context)
:Ctrl( type, startx, starty, width, height, context)
{
	this->showmode = 0;
	this->isFocused = false;
}

Button::~Button()
{
	
}

void Button::setFocused(bool focused)
{
	this->isFocused = focused;
}

int Button::getShowMode()
{
	return this->showmode;
}

void Button::setShowMode(int showmode)
{
	if(showmode == 0 || showmode == 1)
	{
		this->showmode = showmode;
	}
}

//-------------------Show---------------------------------------
void Button::showCtrl() 
{
	Tool::gotoxy(this->startx, this->starty);
	
	if(this->showmode == 1)
	{
		if(this->isFocused)
		{
			Tool::gotoxy(startx + 2, starty + 1);
			cout<<"¡ò";
		}
		else
		{
			Tool::gotoxy(startx + 2, starty + 1);
			cout<<" ";
		}
	}else if(this->showmode == 0)
    {
    	Tool::paintBoder(this->startx, this->starty, this->width, this->height);
	    Tool::gotoxy(this->startx + 2, this->starty + 1);
	    cout<< this->context;
	}	
}
