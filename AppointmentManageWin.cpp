#include "AppointmentManageWin.h"
#include "WindowManager.h"
#include "UserManager.h"

AppointmentManageWin::AppointmentManageWin()
:Window()
{
	
}

AppointmentManageWin::AppointmentManageWin(int win_startX,int win_startY,int win_width,int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 47, 5, 0, 0, "欢迎来到门诊预约管理系统");
    
    this->btn1 = new Button(BUTTON, 30, 10, 10, 3, "预约门诊");
    this->btn2 = new Button(BUTTON, 60, 10, 10, 3, "预约疫苗");
    this->btn3 = new Button(BUTTON, 30, 15, 10, 3, "疫苗接种列表");
    this->btn4 = new Button(BUTTON, 60, 15, 10, 3, "返回");
    
    this->addControl(lab1);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(btn3);
    this->addControl(btn4);
}

AppointmentManageWin::~AppointmentManageWin()
{
	delete this->lab1;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
}

void AppointmentManageWin::paintWindow()
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

int AppointmentManageWin::doAction()
{
	switch(this->flag)
	{
		case 1:
			return 14;
		case 2:
			return 13;
		case 3:
			return 13;
		case 4:
			return 5;
		case -1:
			return 5;
		default:
			return 13;
	}
}
