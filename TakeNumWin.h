#ifndef TAKENUMWIN_H
#define TAKENUMWIN_H

#include "Window.h"
#include "PopWin.h"
#include "Appointment.h"
#include "AppointmentManager.h"

class TakeNumWin:public Window
{
public:
	TakeNumWin();
	TakeNumWin(int win_startX,int win_startY,int win_width,int win_height);
	~TakeNumWin();
	
	void paintWindow();
	int doAction();
	
	void clearEdits();
	
	void prevPage();
	void nextPage();
	
	vector<Appointment*> setcurrentapps();
	bool parseDate(string dateStr, tm& tmDate); 
    double timeDiff(tm& t1, tm& t2); 
	
	int doCheck();//查询，查到对应时间段的预约信息，表格分页显示，未查到提示未查到 
	
private:
	Ctrl* lab1;//欢迎词
	Ctrl* lab2;//"输入就诊日期"
	Ctrl* lab3;//"至"
	Ctrl* edit1;//起始日期输入框，输入格式为“xxxx-xx-xx” 
	Ctrl* edit2;//结束日期输入框，输入格式同上 
	Ctrl* btn1;//"查询"按钮，ENTER后执行查询 
	Ctrl* btn2;//"◎" 按钮，作用见DoctorInquiryWin里的相同按钮 
	Ctrl* btn3;//"◎"按钮 
	Ctrl* btn4;//"◎"按钮 
	Ctrl* btn5;//"返回"按钮 ENTER后返回上一级界面 
	Ctrl* table;//数据显示表格（只显示就诊状态为未就诊和已取消的记录）  表头："预约编号"（读取所有预约类表单存入容器，默认1、2、3编号）
			   //"预约时间" "预约就诊时间" "预约医院"（默认省立医院） "预约科室" "预约医生" "就诊状态"（默认未就诊） 
	
	PopWin* pop1;//"◎"按钮ENTER后，弹出提示框：提示： 当前正在排队人数x人，x为就诊状态是等待就诊的人数
				 //包含按钮"取号"ENTER后，所选行记录的用户状态改为等待就诊，返回TakeNumWin， "取消预约"ENTER后判断当前时间与预约时间是否超过24h，超过则取消成功，就诊状态改为"已取消",否则取消失败 "返回"ENTER后回到TakeNumWin 
	
	static const int PAGE_SIZE = 3;  
    int current_page;                
    int total_pages;                 
    int index;

};


#endif
