#ifndef INITWIN_H
#define INITWIN_H

#include "Window.h"
#include "PopWin.h"

class InitWin:public Window
{
public:
	InitWin();
	InitWin(int win_startX,int win_startY,int win_width,int win_height);
	~InitWin();
	
	int doAction();
	
private:
	Ctrl* lab1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	Ctrl* lab2;
	PopWin* confirmPop;
};

#endif
