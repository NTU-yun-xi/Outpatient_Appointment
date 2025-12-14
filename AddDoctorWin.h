#ifndef ADDDOCTORWIN_H
#define ADDDOCTORWIN_H

#include "Window.h"
#include "ComoboBoxWin.h"
#include "DepartmentManager.h"

class AddDoctorWin:public Window
{
public:
	AddDoctorWin();
	AddDoctorWin(int win_startX,int win_startY,int win_width,int win_height);
	~AddDoctorWin();
	
	void paintWindow();
	int doAction();
	
	void clearEdits();
    
private:
	Ctrl* lab1;  // 欢迎语
    Ctrl* lab2;  // 医生ID标签
    Ctrl* lab3;  // 自动生成的ID显示
    Ctrl* lab4;  // 医生姓名标签
    Ctrl* lab5;  // 所属医院标签
    Ctrl* lab6;  // 所属科室标签
    Ctrl* lab7;  // 医生职位标签
    Ctrl* lab8;  // 简介标签
    Ctrl* edit1; // 医生姓名输入框
    Ctrl* edit2; // 所属医院输入框(固定)
    Ctrl* edit3; // 所属科室显示框
    Ctrl* edit4; // 医生职位显示框
    Ctrl* edit5; // 简介输入框
    Ctrl* btn1;  // 科室下拉按钮
    Ctrl* btn2;  // 职位下拉按钮
    Ctrl* btn3;  // 确认按钮
    Ctrl* btn4;  // 返回按钮
    ComoboBoxWin* comboDept; // 科室下拉框
    ComoboBoxWin* comboPos;  // 职位下拉框
};

#endif
