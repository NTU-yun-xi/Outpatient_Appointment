#include "InitWin.h"

InitWin::InitWin():Window()
{
	
}
InitWin::InitWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL,49,6,0,0,"欢迎来到门诊预约系统");
	this->btn1 = new Button(BUTTON,52,10,8,3,"注      册");
	this->btn2 = new Button(BUTTON,52,13,8,3,"登      录");
	this->btn3 = new Button(BUTTON,52,16,8,3,"退      出");
	this->lab2 = new Label(LABEL,80,23,0,0,"学号：OMO250903");
	this->addControl(lab1);
	this->addControl(btn1);
	this->addControl(btn2);
	this->addControl(btn3);
	this->addControl(lab2);
	
	this->confirmPop = new PopWin(40, 10, 20, 10);
    this->confirmPop->setTitle("是否确认退出？");
    
    this->confirmPop->addControl(new Button(BUTTON, 45, 13, 6, 3, "YES"));
    this->confirmPop->addControl(new Button(BUTTON, 55, 13, 6, 3, "NO"));
}
InitWin::~InitWin()
{
	delete this->lab1;
	delete this->btn1;
	delete this->btn2;
	delete this->btn3;
	delete this->lab2;
	delete this->confirmPop;
	
	//delete [] this->arr;
}

int InitWin::doAction()
{
	if(this->flag == 1)
	{
		return 1;
	}else if(this->flag == 2)
	{
		return 2;
	}else if(this->flag == 3)
	{
        this->confirmPop->paintWindow();
        this->confirmPop->winRun();
        
        int result = this->confirmPop->getResult();
        if (result == 0) // YES按钮
        {
            exit(0);
        }
        else // NO按钮或取消
        {
            return 0; // 回到主页面
        }
	}else if(this->flag == -1)
	{
		exit(0);
	}
}

