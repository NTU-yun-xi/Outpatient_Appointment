#ifndef DOCTORWIN_H
#define DOCTORWIN_H

#include "Window.h"
#include "WindowManager.h"
#include <ctime>
#include <iostream>
using namespace std;

class DoctorWin:public Window
{
public:
	DoctorWin();
	DoctorWin(int win_startX,int win_startY,int win_width,int win_height);
	~DoctorWin();
	
	void paintWindow();
	int doAction();
	
private:
	Ctrl* lab1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
};


#endif
