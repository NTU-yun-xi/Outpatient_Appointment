#ifndef APPOINTMENTMANAGEWIN_H
#define APPOINTMENTMANAGEWIN_H

#include "Window.h"

class AppointmentManageWin:public Window
{
public:
	AppointmentManageWin();
	AppointmentManageWin(int win_startX,int win_startY,int win_width,int win_height);
	~AppointmentManageWin();
	
	void paintWindow();
	int doAction();
	
private:
	Ctrl* lab1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	Ctrl* btn4;
};

#endif
