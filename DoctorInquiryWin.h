#ifndef DOCTORINQUIRYWIN_H
#define DOCTORINQUIRYWIN_H

#include "Window.h"
#include "PopWin.h"

class DoctorInquiryWin:public Window
{
public:
	DoctorInquiryWin();
	DoctorInquiryWin(int win_startX,int win_startY,int win_width,int win_height);
	~DoctorInquiryWin();
	
	void paintWindow();
	int doAction();
	
	vector<Doctor*> setcurrentDoctors();
	
	void clearEdits();
	
	void doCombo(ComoboBoxWin* combo);
	
	void prevPage();
	void nextPage();
	
	int doCheck();
	int doRsetDoctor();

private:
	Ctrl* lab1;
	Ctrl* lab2;
	Ctrl* edit1;
	Ctrl* btn1;
	Ctrl* btn2;
	Ctrl* btn3;
	Ctrl* btn4;
	Ctrl* btn5;
	Ctrl* table1;
	PopWin* pop1;
	PopWin* pop2;
	
	static const int PAGE_SIZE = 3;  
    int current_page;                
    int total_pages;                 
    int index;
};

#endif
