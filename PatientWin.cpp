#include "PatientWin.h"

PatientWin::PatientWin()
:Window()
{
	
}
PatientWin::PatientWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 47, 5, 0, 0, "欢迎来到门诊预约管理系统");
    
    this->btn1 = new Button(BUTTON, 30, 10, 10, 3, "个人中心");
    this->btn2 = new Button(BUTTON, 60, 10, 10, 3, "预约管理");
    this->btn3 = new Button(BUTTON, 30, 15, 10, 3, "取号");
    this->btn4 = new Button(BUTTON, 60, 15, 10, 3, "就诊信息");
    this->btn5 = new Button(BUTTON, 50, 20, 8, 3, "退出");
    
    this->addControl(lab1);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(btn3);
    this->addControl(btn4);
    this->addControl(btn5);
}

PatientWin::~PatientWin()
{
	delete this->lab1;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
    delete this->btn5;
}

void PatientWin::paintWindow()
{
	Tool::paintBoder(win_startX, win_startY, win_width, win_height);
	for(int i = 0;i<this->count;i++)
	{
		this->arr[i]->showCtrl();
	}
	
	BaseUser* user = this->GetCurrentUser();
	if(user != NULL)
	{
		Tool::gotoxy(30,7);
		cout<<"欢迎，"<<user->GetName()<<",普通用户!";
		
		time_t now = time(0);
		tm* LocalTime = localtime(&now);
		char date[20];
		sprintf(date,"日期：%d-%02d-%02d",
				1900+LocalTime->tm_year,
				1+LocalTime->tm_mon,
				LocalTime->tm_mday);
		Tool::gotoxy(60,7);
		cout<<date;
	}
}
	
int PatientWin::doAction()
{
	switch(this->flag)
	{
		case 1:
			return 10;
		case 2:
			return 13;
		case 3:
			return 5;
		case 4:
			return 5;
		case 5:
			return 0;
		case -1:
			return 0;
		default:
			return 5;
	}
}
