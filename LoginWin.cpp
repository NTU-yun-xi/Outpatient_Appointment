#include "LoginWin.h"

LoginWin::LoginWin()
:Window()
{
    this->combo = NULL;
}

LoginWin::LoginWin(int win_startX, int win_startY, int win_width, int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
    this->lab1 = new Label(LABEL, 55, 5, 0, 0, "登录界面");
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "账号:");
    this->lab3 = new Label(LABEL, 30, 12, 0, 0, "密码:");
    this->lab4 = new Label(LABEL, 30, 16, 0, 0, "角色:");
    
    this->edit1 = new Edit(EDIT, 38, 7, 20, 3, "", 11, 0, 3);
    this->edit2 = new Edit(EDIT, 38, 11, 20, 3, "", 6, 1, 3);
    this->edit3 = new Edit(EDIT, 38, 15, 10, 3, "", 10, 0, 0);
    
    this->btn1 = new Button(BUTTON, 59, 15, 6, 3, "↓");
    this->btn2 = new Button(BUTTON, 35, 21, 8, 3, "确认");
    this->btn3 = new Button(BUTTON, 55, 21, 8, 3, "返回");
    
    this->combo = new ComoboBoxWin(38, 18, 12, 2);
    this->combo->addOption(38, 18, 10, 3, "管理员");
    this->combo->addOption(38, 21, 10, 3, "医生");
    this->combo->addOption(38, 24, 10, 3, "普通用户");
    this->combo->SetShow(false);
    
    this->addControl(lab1);
    this->addControl(lab2);
    this->addControl(lab3);
    this->addControl(lab4);
    this->addControl(edit1);
    this->addControl(edit2);
    this->addControl(edit3);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(btn3);
}

LoginWin::~LoginWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->lab4;
    delete this->edit1;
    delete this->edit2;
    delete this->edit3;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->combo;
}

void LoginWin::paintWindow()
{
	Tool::paintBoder(this->win_startX,this->win_startY,this->win_width,this->win_height);
	for(int i = 0;i<this->count;i++)
	{
		this->arr[i]->showCtrl();
	}
	if(this->combo != NULL && this->combo->GetShow())
	{
		this->combo->paintWindow(); 
	}
}

int LoginWin::doAction()
{
    if (this->flag == 7)
    {
        this->GetCombo();
        return 2;
    }
    
    if (flag == 8)  
    {
        return this->LoginCheck();
    }
    
    if (flag == 9)  
    {
    	this->clearEdits();
        return 0; 
    }
    
    if(this->flag == -1)
    {
    	this->clearEdits();
    	return 0;
	}
    
    return 2;
}

int LoginWin::GetCombo()
{
	this->combo->SetShow(!this->combo->GetShow());
    if (this->combo->GetShow())
    {
        //this->combo->SetPosition(btn1->GetX(), btn1->GetY() + btn1->GetHeight());
        this->combo->paintWindow();
        this->combo->winRun();
        int selectIndex = this->combo->doAction();
        
        if (selectIndex != -1)
        {
            string roleText = this->combo->GetOptionContext();
            ((Edit*)this->edit3)->SetContext(roleText);
        }
        this->combo->SetShow(false);
    }
    return 0;
}

int LoginWin::LoginCheck()
{
	string account = ((Edit*)this->edit1)->GetContext();
    string password = ((Edit*)this->edit2)->GetContext();
    string role = ((Edit*)this->edit3)->GetContext();
    int rolenum = 0;
    if (role == "管理员")    rolenum = 1;
    else if (role == "医生")    rolenum = 2;
    else if (role == "普通用户")    rolenum = 3;
    if (account.empty() || password.empty() || role.empty())
    {
        Tool::gotoxy(35, 25);
        cout << "账号、密码和角色不能为空!";
        Sleep(1000);
        return 2;
    }
    
    UserManager* userMgr = WindowManager::GetInstance()->GetUserManager();
    BaseUser* user = userMgr->findUser(account);
    if (user && user->GetPassword() == password)
    {
    	if(user->GetRole() == rolenum)
    	{
    		WindowManager::GetInstance()->SetCurrentUser(user);
	        Tool::gotoxy(35, 25);
	        cout << "登录成功!";
	        Sleep(1000);
	        this->clearEdits();
	        if (user->GetRole() == 1)  
	        {
	            return 3;  
	        }
	        else if (user->GetRole() == 2)  
	        {
	            return 4;  
	        }
	        else if (user->GetRole() == 3)  
	        {
	            return 5;  
	        }
		}else
		{
			Tool::gotoxy(35, 25);
	        cout << "用户角色不匹配，登录失败！";
	        Sleep(1000);
        	return 2;
		} 
        return 2; 
    }
    else
    {
        Tool::gotoxy(35, 25);
        cout << "账号或密码错误!";
        Sleep(1000);
        return 2;
    }
}

void LoginWin::clearEdits()
{
    ((Edit*)this->edit1)->SetContext("");  
    ((Edit*)this->edit2)->SetContext("");  
    ((Edit*)this->edit3)->SetContext("");  
}
