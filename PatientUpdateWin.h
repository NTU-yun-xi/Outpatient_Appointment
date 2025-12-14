#ifndef PATIENTUPDATEWIN_H
#define PATIENTUPDATEWIN_H

#include "Window.h"

class PatientUpdateWin:public Window
{
public:
	PatientUpdateWin();
	PatientUpdateWin(int win_startX,int win_startY,int win_width,int win_height);
	~PatientUpdateWin();
	
	void paintWindow();
	int doAction();
	void clearEdits();
    void updatePatientInfo(); 
	
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* lab3;
	Ctrl* lab4;
	Ctrl* lab5;
	Ctrl* edit1;
	Ctrl* edit2;
	Ctrl* btn1;
	Ctrl* btn2;
};

#endif
