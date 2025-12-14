#ifndef VISITRECORDWIN_H
#define VISITRECORDWIN_H

#include "Window.h"
#include "DoctorVisitQueryWin.h"
#include "Appointment.h"

class VisitRecordWin : public Window
{
public:
    VisitRecordWin();
    VisitRecordWin(int win_startX, int win_startY, int win_width, int win_height);
    ~VisitRecordWin();
    
    void paintWindow();
    int doAction();
    
    void clearEdits();
    void saveVisitRecord();
    
	void setAppointment();
    
private:
    Ctrl* lab1;      // 标题
    Ctrl* lab2;      // 用户ID标签
    Ctrl* lab3;   	 // 用户ID值
    Ctrl* lab4;      // 预约描述标签
    Ctrl* lab5;      // 预约描述值
    Ctrl* edit1;     // 就诊描述标签
    Ctrl* edit2; 	 // 就诊描述编辑框
    Ctrl* btn1;      // 确定按钮
    Ctrl* btn2;      // 返回按钮
    
    Appointment* currentAppointment;  // 当前就诊记录
};

#endif
