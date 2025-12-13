#include "PatientUpdateWin.h"
#include "WindowManager.h"
#include "UserManager.h"
#include "Tool.h"
#include <string>

PatientUpdateWin::PatientUpdateWin() 
: Window()
{
    this->lab1 = NULL;
	this->lab2 = NULL;
	this->lab3 = NULL;
	this->lab4 = NULL;
	this->lab5 = NULL;
    this->edit1 = NULL;
	this->edit2 = NULL;
    this->btn1 = NULL;
	this->btn2 = NULL;
}

PatientUpdateWin::PatientUpdateWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
    // 初始化控件
    this->lab1 = new Label(LABEL, 45, 5, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 30, 9, 0, 0, "手机号码：");
    this->lab3 = new Label(LABEL, 45, 9, 0, 0, "");  // 后续显示当前用户账号
    this->lab4 = new Label(LABEL, 30, 12, 0, 0, "姓    名：");
    this->lab5 = new Label(LABEL, 30, 16, 0, 0, "身份证号：");
    
    this->edit1 = new Edit(EDIT, 45, 11, 15, 3, "", 20, 0, 4);  // 中文限制
    this->edit2 = new Edit(EDIT, 45, 15, 20, 3, "", 18, 0, 3);  // 身份证号（数字+字母）
    
    this->btn1 = new Button(BUTTON, 35, 20, 8, 3, "确认");
    this->btn2 = new Button(BUTTON, 55, 20, 8, 3, "返回");
    
    // 添加控件到窗口
    this->addControl(this->lab1);
    this->addControl(this->lab2);
    this->addControl(this->lab3);
    this->addControl(this->lab4);
    this->addControl(this->lab5);
    this->addControl(this->edit1);
    this->addControl(this->edit2);
    this->addControl(this->btn1);
    this->addControl(this->btn2);
}

PatientUpdateWin::~PatientUpdateWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->lab4;
    delete this->lab5;
    delete this->edit1;
    delete this->edit2;
    delete this->btn1;
    delete this->btn2;
}

void PatientUpdateWin::paintWindow()
{
    // 绘制窗口边框
    Tool::paintBoder(win_startX, win_startY, win_width, win_height);
    // 获取当前用户信息并显示手机号码
    BaseUser* user = GetCurrentUser();
    // 显示当前用户账号（手机号码）
    ((Label*)lab3)->SetContext(user->GetAccount());
    // 显示所有控件
    for (int i = 0; i < count; i++)
    {
        this->arr[i]->showCtrl();
    }
	if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎，"<<user->GetName()<<",普通用户";
		
		time_t now = time(0);
		tm* LocalTime = localtime(&now);
		char date[20];
		sprintf(date,"日期:%d-%02d-%02d",
				1900+LocalTime->tm_year,
				1+LocalTime->tm_mon,
				LocalTime->tm_mday);
		Tool::gotoxy(60,6);
		cout<<date;
	}
}

void PatientUpdateWin::clearEdits()
{
    ((Edit*)edit1)->SetContext("");
    ((Edit*)edit2)->SetContext("");
}

void PatientUpdateWin::updatePatientInfo()
{
    BaseUser* baseUser = GetCurrentUser();
    if (baseUser == NULL || baseUser->GetRole() != 3)
        return;
    
    Patient* patient = dynamic_cast<Patient*>(baseUser);
    if (patient == NULL)
        return;
    
    // 获取输入框内容
    string name = ((Edit*)edit1)->GetContext();
    string idCard = ((Edit*)edit2)->GetContext();
    
    // 简单验证（可根据需求扩展）
    if (name.empty() || idCard.empty())
    {
        Tool::gotoxy(40, 23);
        cout << "姓名和身份证号不能为空！";
        Sleep(1000);
        return;
    }
    
    // 更新患者信息
    patient->SetName(name);
    patient->SetIdCard(idCard);
    
    // 保存到文件
    UserManager::GetOusermanager()->updateUser(patient);
    
    Tool::gotoxy(40, 23);
    cout << "信息更新成功！";
    Sleep(1000);
    clearEdits();
}

int PatientUpdateWin::doAction()
{
    switch (this->flag)
    {
        case 7:  // 确认按钮（索引对应btn1）
            this->updatePatientInfo();
            return 10;  // 更新后返回个人中心
        case 8:  // 返回按钮（索引对应btn2）
            this->clearEdits();
            return 10;  // 返回个人中心
        case -1:  // 窗口关闭
            this->clearEdits();
            return 10;
        default:
            return 11;  // 当前窗口标识（假设11为PatientUpdateWin）
    }
}
