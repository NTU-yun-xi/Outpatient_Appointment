#ifndef ADMINWIN_H
#define ADMINWIN_H

#include "Window.h"
#include "WindowManager.h"
#include <ctime>
#include <iostream>
using namespace std;

class AdminWin:public Window
{
public:
	AdminWin();
	AdminWin(int win_startX,int win_startY,int win_width,int win_height);
	~AdminWin();
	
	void paintWindow();
	int doAction();
	
private:
	Ctrl* lab1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	Ctrl* btn4;
	Ctrl* btn5;
};


#endif 
