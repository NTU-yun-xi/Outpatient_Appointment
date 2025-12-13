#ifndef PATIENTRESETPASSWORD_H
#define PATIENTRESETPASSWORD_H

#include "Window.h"

class PatientResetPasswordWin:public Window
{
public:
	PatientResetPasswordWin();
	PatientResetPasswordWin(int win_startX,int win_startY,int win_width,int win_height);
	~PatientResetPasswordWin();
	
	void paintWindow();
	int doAction();
	void clearEdits();
	
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* lab3;
	Ctrl* lab4;
	Ctrl* lab5;
	Ctrl* lab6;
	Ctrl* edit1;
	Ctrl* edit2;
	Ctrl* edit3;
	Ctrl* btn1;
	Ctrl* btn2;
};

#endif
