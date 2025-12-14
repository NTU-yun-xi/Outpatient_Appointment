#ifndef PATIENTWIN_H
#define PATIENTWIN_H

#include "Window.h"
#include "WindowManager.h"
#include <ctime>
#include <iostream>
using namespace std;

class PatientWin:public Window
{
public:
	PatientWin();
	PatientWin(int win_startX,int win_startY,int win_width,int win_height);
	~PatientWin();
	
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
