#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include "Window.h"
#include "WindowManager.h"

class RegisterWin:public Window
{
public:
	RegisterWin();
	RegisterWin(int win_startX,int win_startY,int win_width,int win_height);
	~RegisterWin();
	
	int doAction();
	
	int CheckPhone();
	int CheckRegister();
	
	void CleanEdits();
	
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* lab3;
	Ctrl* edit1;
	Ctrl* edit2;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	Ctrl* labCode;
	string CheckCode; 
};

#endif
