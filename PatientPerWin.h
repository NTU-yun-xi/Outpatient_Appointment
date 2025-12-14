#ifndef PATIENTPERWIN_H
#define PATIENTPERWIN_H

#include "Window.h"

class PatientPerWin:public Window
{
public:
	PatientPerWin();
	PatientPerWin(int win_startX,int win_startY,int win_width,int win_height);
	~PatientPerWin();
	
	void paintWindow();
	int doAction(); 
	
private:
	Ctrl* lab1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
};

#endif
