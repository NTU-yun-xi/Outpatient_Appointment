#ifndef LOGINWIN_H
#define LOGINWIN_H

#include "Window.h"
#include "WindowManager.h"
#include "ComoboBoxWin.h"

class LoginWin:public Window
{
public:
	LoginWin();
	LoginWin(int win_startX,int win_startY,int win_width,int win_height);
	~LoginWin();
	
	int doAction();
	
	void paintWindow();
	
	int GetCombo();
	int LoginCheck();
	
	void clearEdits();
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* lab3;
	Ctrl* lab4;
	Ctrl* edit1;
	Ctrl* edit2;
	Ctrl* edit3;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	ComoboBoxWin* combo;
};

#endif
