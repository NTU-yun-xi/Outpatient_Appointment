#include "AdminWin.h"

AdminWin::AdminWin()
:Window()
{
	
}
AdminWin::AdminWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	lab1 = new Label(LABEL, 53, 5, 0, 0, "管理员主界面");
    
    btn1 = new Button(BUTTON, 30, 10, 10, 3, "用户管理");
    btn2 = new Button(BUTTON, 60, 10, 10, 3, "医生管理");
    btn3 = new Button(BUTTON, 30, 15, 10, 3, "科室管理");
    btn4 = new Button(BUTTON, 60, 15, 10, 3, "数据统计");
    btn5 = new Button(BUTTON, 50, 20, 8, 3, "退出");
    
    addControl(lab1);
    addControl(btn1);
    addControl(btn2);
    addControl(btn3);
    addControl(btn4);
    addControl(btn5);
}

AdminWin::~AdminWin()
{
	delete lab1;
    delete btn1;
    delete btn2;
    delete btn3;
    delete btn4;
    delete btn5;
}

void AdminWin::paintWindow()
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
		cout<<"欢迎，"<<user->GetName()<<",管理员!";
		
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
	
int AdminWin::doAction()
{
	switch(this->flag)
	{
		case 1:
			return 6;
		case 2:
			return 7;
		case 3:
			return 9;
		case 4:
			return 3;
		case 5:
			return 0;
		case -1:
			return 0;
		default:
			return 3;
	}
}


