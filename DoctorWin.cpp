#include "DoctorWin.h"

DoctorWin::DoctorWin()
:Window()
{
	
}

DoctorWin::DoctorWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 47, 5, 0, 0, "欢迎来到门诊预约管理系统");

    this->btn1 = new Button(BUTTON, 30, 10, 10, 3, "个人中心");
    this->btn2 = new Button(BUTTON, 60, 10, 10, 3, "就诊信息查询");
    this->btn3 = new Button(BUTTON, 50, 15, 8, 3, "退出");
    
    this->addControl(this->lab1);
    this->addControl(this->btn1);
    this->addControl(this->btn2);
    this->addControl(this->btn3);
}

DoctorWin::~DoctorWin()
{
	delete this->lab1;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
}

void DoctorWin::paintWindow()
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
		cout<<"欢迎，"<<user->GetName()<<",医生!";
		
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

int DoctorWin::doAction()
{
	switch(this->flag)
	{
		case 1:
			return 4;
		case 2:
			return 4;
		case 3:
			return 0;
		case -1:
			return 0;
		default:
			return 4;
	}
}
