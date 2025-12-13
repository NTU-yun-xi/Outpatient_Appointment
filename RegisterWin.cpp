#include "RegisterWin.h"

RegisterWin::RegisterWin()
:Window()
{
	
}

RegisterWin::RegisterWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL,52,6,0,0,"注册界面");
	this->lab2 = new Label(LABEL,35,9,0,0,"手机号码：");
	this->lab3 = new Label(LABEL,35,13,0,0,"验 证 码：");
	this->edit1 = new Edit(EDIT,49,8,14,3,"",11,0,1);
	this->edit2 = new Edit(EDIT,49,12,14,3,"",6,0,1);
	this->btn1 = new Button(BUTTON,49,15,10,3,"获取验证码");
	this->btn2 = new Button(BUTTON,39,18,8,3,"确定");
	this->btn3 = new Button(BUTTON,59,18,8,3,"返回");
	
	this->labCode = new Label(LABEL,39,22,0,0,"");
    
	this->addControl(lab1);
    this->addControl(lab2);
    this->addControl(lab3);
    this->addControl(edit1);
    this->addControl(edit2);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(btn3);
    this->addControl(labCode);
}

RegisterWin::~RegisterWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->edit1;
    delete this->edit2;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->labCode; 
}

void RegisterWin::CleanEdits()
{
	((Edit*)this->edit1)->SetContext("");  
    ((Edit*)this->edit2)->SetContext("");
    ((Label*)this->labCode)->SetContext("");
}

int RegisterWin::CheckPhone()
{
	string phone = ((Edit*)this->edit1)->GetContext();
	if(phone.empty() || phone.size()<11)
	{
		Tool::gotoxy(36,21);
		cout<<"请先输入完整手机号！";
		Sleep(1000); 
		return 1;
	}
	
	UserManager* userMgr = UserManager::GetOusermanager();
    if(userMgr->findUser(phone) != NULL)
    {
        Tool::gotoxy(36,21);
        cout<<"该手机号已注册！";
        Sleep(1000); 
        return 1;
    }
    
    srand((unsigned int)time(NULL));
	int code = rand()%900000 + 100000;
	this->CheckCode = Tool::intToString(code);;
	
	this->labCode->SetContext("验证码信息为：" + this->CheckCode);
	Tool::gotoxy(36, 21);
	cout << "                ";
	this->paintWindow();
	if (edit2 != NULL) {
	    Tool::gotoxy(edit2->GetX() + 2, edit2->GetY() + 1);
	}
	return 1;
}

int RegisterWin::CheckRegister()
{
	UserManager* userMgr = UserManager::GetOusermanager();
	string phone = ((Edit*)this->edit1)->GetContext();
	string inputCode = ((Edit*)this->edit2)->GetContext();
	if(phone.empty() || inputCode.empty())
    {
        Tool::gotoxy(36, 21);
        cout << "请完善所有信息!";
        Sleep(1000); 
        return 1;
    }
    
    if(inputCode != this->CheckCode)
    {
        Tool::gotoxy(36, 21);
        cout << "验证码错误!";
        Sleep(1000); 
        return 1;
    }
    
    Patient* newPatient = new Patient(phone, "123456", 3, "", "");
     
    if(userMgr->addUser(newPatient))
    {
        Tool::gotoxy(36, 21);
        cout << "注册成功!默认密码:123456";
        Sleep(1000); 
        this->CleanEdits();
        return 2;
    }
    else
    {
        Tool::gotoxy(36, 21);
        cout << "注册失败!";
        Sleep(1000); 
        delete newPatient;
        return 1;
    }
}

int RegisterWin::doAction()
{
	if(this->flag == 5)
	{
		return this->CheckPhone();
	}
	if(this->flag == 6)
	{
		return this->CheckRegister();
	}
	
	if(this->flag == 7)
	{
		this->CleanEdits();
		return 0;
	}
	
	if(this->flag == -1)
	{
		this->CleanEdits();
		return 0;
	}
}
