#ifndef WINDOW_H
#define WINDOW_H

#include "Ctrl.h"
#include "Button.h"
#include "Edit.h"
#include "Label.h"
#include "Table.h"
#include "Tool.h"
#include "User.h"
#include "Admin.h"
#include "Doctor.h"
#include "Patient.h"
#include "UserManager.h"

#include <windows.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <list> 
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sstream> 
using namespace std;

class Window
{
public:
	Window();
	Window(int win_startX,int win_startY,int win_width,int win_height);
	virtual ~Window();
	
	int GetWinX();
	int GetWinY();
	int GetWinWidth();
	int GetWinHeight();
	int GetCount();
	int GetFlag();
	Ctrl* GetConByIndex(int index);
	
	void SetWinX(int win_startX);
	void SetWinY(int win_startY);
	void SetWinWidth(int win_width);
	void SetWinHeight(int win_height);
	
	void addControl(Ctrl * con);
	virtual void paintWindow();
	virtual void winRun();
	
	virtual int doAction() = 0; 
	
	void SetCurrentUser(BaseUser* user);
	BaseUser* GetCurrentUser();
	
protected:
	int win_startX;
	int win_startY;
	int win_width;
	int win_height;
	int count;
	int flag;
	Ctrl * arr[30];
	BaseUser* currentUser; 
};

#endif
