#ifndef APPOINTMENTWIN_H
#define APPOINTMENTWIN_H

#include "Window.h"
#include "ComoboBoxWin.h"
#include "DepartmentManager.h"
#include "AppointmentManager.h"
#include "WorkDate.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <vector>
#include <map>
#include <string>
using namespace std;

class AppointmentWin:public Window
{
public:
	AppointmentWin();
	AppointmentWin(int win_startX,int win_startY,int win_width,int win_height);
	~AppointmentWin();
	
	void paintWindow();
	int doAction();
	
	void loadDeptOptions();
	void loadDayOptions();
	void loadTimeOptions();
	void updateDoctorOptions(string deptName);
	string getSelectedDoctorId();
	int getSelectedTime();
	int getSelectedDay();
	int getAvailableTimeId(string doctorId, int day, string timeSlot);
	
	void clearEdits();
	
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* lab3;
	Ctrl* lab4;
	Ctrl* lab5;
	Ctrl* lab6;
	Ctrl* lab7;
	Ctrl* edit1;
	Ctrl* edit2;
	Ctrl* btn1;
	Ctrl* edit3;
	Ctrl* btn2;
	Ctrl* edit4;
	Ctrl* btn3;
	Ctrl* edit5;
	Ctrl* btn4;
	Ctrl* edit6;
	Ctrl* btn5;
	Ctrl* btn6;
	
	ComoboBoxWin* comboDep;
	ComoboBoxWin* comboDoc;
	ComoboBoxWin* comboDay;
	ComoboBoxWin* comboTime;
	
	map<string,int> timeMap;
};

#endif
