#include "UserInquiryWin.h"

UserInquiryWin::UserInquiryWin()
:Window()
{
	this->current_page = 1;
	this->total_pages = 1;
	this->index = 0;
}

UserInquiryWin::UserInquiryWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "请输入用户账号:");
    this->edit1 = new Edit(EDIT, 45, 7, 10, 3, "", 11, 0, 3);  
    this->btn1 = new Button(BUTTON, 65, 7, 8, 3, "查询");     
    this->btn2 = new Button(BUTTON, 30, 22, 8, 3, "返回");     
    this->table1 = new Table(TABLE, 13, 10, 0, 0, "", 5, PAGE_SIZE + 1, 9, 1);
    
    this->addControl(lab1);
    this->addControl(lab2);
    this->addControl(edit1);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(table1);
    
    this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

UserInquiryWin::~UserInquiryWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->edit1;
    delete this->btn1;
    delete this->btn2;
    delete this->table1;
}

vector<BaseUser*> UserInquiryWin::setcurrentUsers()
{
	vector<BaseUser*> displayUsers = UserManager::GetOusermanager()->getAllUsers();
    string account = ((Edit*)edit1)->GetContext();
    if (!account.empty()) {
        BaseUser* exactUser = UserManager::GetOusermanager()->findUser(account);
        if (exactUser) {
            displayUsers.clear();
            displayUsers.push_back(exactUser);
        } else {
            displayUsers = UserManager::GetOusermanager()->fuzzyByAccount(account);
        }
    }
    return displayUsers;
}

void UserInquiryWin::paintWindow()
{
	Window::paintWindow();
	BaseUser* user = this->GetCurrentUser();
	if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎，"<<user->GetName()<<",管理员!";
		
		time_t now = time(0);
		tm* LocalTime = localtime(&now);
		char date[20];
		sprintf(date,"日期：%d-%02d-%02d",
				1900+LocalTime->tm_year,
				1+LocalTime->tm_mon,
				LocalTime->tm_mday);
		Tool::gotoxy(60,6);
		cout<<date;
	}
	Tool::gotoxy(60,22);
	cout<<"按←→翻页";
	Tool::gotoxy(21, 11);
	cout << "序号";
    Tool::gotoxy(40, 11);
    cout << "账号";
    Tool::gotoxy(59, 11);
    cout << "密码";
    Tool::gotoxy(77, 11);
    cout << "名字";
    Tool::gotoxy(95, 11);
    cout << "角色/证件";
    
    vector<BaseUser*> Users = this->setcurrentUsers();
    int userCount = Users.size();
    if (userCount == 0)
    {
        this->total_pages = 1;
        this->current_page = 1;
    }
    else
    {
        this->total_pages = (userCount % this->PAGE_SIZE == 0) 
            ? (userCount / this->PAGE_SIZE) 
            : (userCount / this->PAGE_SIZE + 1);
    }
    
    if (this->current_page > this->total_pages) 
	{
		this->current_page = this->total_pages;
	}
    if (this->current_page < 1)
	{
		this->current_page = 1;
	} 
    this->index = (this->current_page - 1) * this->PAGE_SIZE;
    
    int displayCount = 0;
    for (int i = this->index; i < userCount && displayCount < this->PAGE_SIZE; i++)
    {
        BaseUser* user = Users[i];
        int rowY = 11 + 2 * (displayCount + 1);  

        Tool::gotoxy(23, rowY);
        cout << (i + 1);

        Tool::gotoxy(33, rowY);
        cout << user->GetAccount();

        Tool::gotoxy(53, rowY);
        cout << user->GetPassword();

        Tool::gotoxy(76, rowY);
        cout << user->GetName();

        Tool::gotoxy(90, rowY);
        if (user->GetRole() == 3)
        {
            Patient* patient = dynamic_cast<Patient*>(user);
            if (patient != NULL)
			{
				cout << patient->GetIdCard();
			} 
        }
        else
        {
        	if(user->GetRole() == 1)
        	{
        		cout<<"管理员"; 
			}else if(user->GetRole() == 2)
			{
				cout<<"医生"; 
			}
        }

        displayCount++;
    }
    
    Tool::gotoxy(45, 20);
    cout << "第 " << this->current_page << " 页 / 共 " << this->total_pages << " 页";
}

int UserInquiryWin::doAction()
{
	string account = ((Edit*)edit1)->GetContext();
	
    if (this->flag == -100)  
    {
        if (this->current_page > 1)
        {
            this->current_page--;
        }
        else
        {
        	Tool::gotoxy(45,19);
            cout << "已经是第一页！";
            Sleep(1000);
        }
        return 6;
    }
    else if (this->flag == -101)
    {
    	vector<BaseUser*> Users = this->setcurrentUsers();
        if (this->current_page < (Users.size()+this->PAGE_SIZE-1)/this->PAGE_SIZE)
        {
            this->current_page++;
        }
        else
        {
        	Tool::gotoxy(45,19);
            cout << "已经是最后一页！";
            Sleep(1000);
        }
        return 6;
    }
    
    else if (this->flag == 3) 
    {
        this->current_page = 1;
        return 6;
    }
    else if (this->flag == 4)
    {
    	this->clearEdits();
        return 3;
    }
    else if (this->flag == -1)
    {
    	this->clearEdits();
        return 3;
    }

    return 6;
}

void UserInquiryWin::clearEdits()
{
    ((Edit*)this->edit1)->SetContext("");   
}
