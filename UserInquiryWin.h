#ifndef USERINQUIRY_H
#define USERINQUIRY_H

#include "window.h"

class UserInquiryWin:public Window
{
public:
	UserInquiryWin();
	UserInquiryWin(int win_startX,int win_startY,int win_width,int win_height);
	~UserInquiryWin();
	
	void paintWindow();
	int doAction();
	
	vector<BaseUser*> setcurrentUsers();
	
	void clearEdits();
	
private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* edit1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* table1;
	
	static const int PAGE_SIZE = 3;  
    int current_page;                
    int total_pages;                 
    int index;
}; 

#endif
