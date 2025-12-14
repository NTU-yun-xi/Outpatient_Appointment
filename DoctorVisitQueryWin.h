#ifndef DOCTORVISITQUERYWIN_H
#define DOCTORVISITQUERYWIN_H

#include "Window.h"
#include "PopWin.h"
#include "Appointment.h"
#include "AppointmentManager.h"

class DoctorVisitQueryWin : public Window
{
public:
    DoctorVisitQueryWin();
    DoctorVisitQueryWin(int win_startX, int win_startY, int win_width, int win_height);
    ~DoctorVisitQueryWin();
    
    void paintWindow();
    int doAction();
    
    vector<Appointment*> setcurrentVisits();
    void prevPage();
    void nextPage();
    void selctapp();
    Appointment* getselectedapp();
    
private:
    Ctrl* lab1;          // 标题
    Ctrl* btn1;       // 返回按钮
    Ctrl* btn2;
    Ctrl* btn3;
    Ctrl* btn4;
    Ctrl* table;         // 表格
    
    static const int PAGE_SIZE = 3;  
    int current_page;                
    int total_pages;                  
    int index;
    
    vector<Appointment*> showVisits;  // 显示的就诊记录
	Appointment* selctedapp; 
};

#endif
