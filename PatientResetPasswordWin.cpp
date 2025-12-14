#include "PatientResetPasswordWin.h"
#include "UserManager.h"
#include "Tool.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cctype>
#include <windows.h>
using namespace std;

PatientResetPasswordWin::PatientResetPasswordWin()
: Window()
{
    this->lab1 = NULL; 
	this->lab2 = NULL; 
	this->lab3 = NULL; 
	this->lab4 = NULL; 
	this->lab5 = NULL; 
	this->lab6 = NULL;  
    this->edit1 = NULL; 
	this->edit2 = NULL; 
	this->edit3 = NULL;
    this->btn1 = NULL; 
	this->btn2 = NULL;
}

PatientResetPasswordWin::PatientResetPasswordWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
    // 初始化标签
    this->lab1 = new Label(LABEL, 45, 5, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "手机号码：");
    this->lab3 = new Label(LABEL, 42, 8, 0, 0, "");
    this->lab4 = new Label(LABEL, 30, 11, 0, 0, "原 密 码：");
    this->lab5 = new Label(LABEL, 30, 15, 0, 0, "新 密 码：");
    this->lab6 = new Label(LABEL, 30, 19, 0, 0, "确认密码：");
    
    // 初始化输入框
    this->edit1 = new Edit(EDIT, 42, 10, 15, 3, "", 6, 1, 1);
    this->edit2 = new Edit(EDIT, 42, 14, 15, 3, "", 6, 1, 1);
    this->edit3 = new Edit(EDIT, 42, 18, 15, 3, "", 6, 1, 1);
    
    // 初始化按钮
    this->btn1 = new Button(BUTTON, 35, 23, 8, 3, "确认");
    this->btn2 = new Button(BUTTON, 55, 23, 8, 3, "返回");
    
    // 添加控件到窗口
    this->addControl(this->lab1);
    this->addControl(this->lab2);
    this->addControl(this->lab3);
    this->addControl(this->lab4);
    this->addControl(this->lab5);
    this->addControl(this->lab6);
    this->addControl(this->edit1);
    this->addControl(this->edit2);
    this->addControl(this->edit3);
    this->addControl(this->btn1);
    this->addControl(this->btn2);
}

PatientResetPasswordWin::~PatientResetPasswordWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->lab4;
    delete this->lab5;
    delete this->lab6;
    delete this->edit1;
    delete this->edit2;
    delete this->edit3;
    delete this->btn1;
    delete this->btn2;

}

void PatientResetPasswordWin::paintWindow()
{
    // 绘制窗口边框
    Tool::paintBoder(win_startX, win_startY, win_width, win_height);
    BaseUser* user = GetCurrentUser();
    // 显示当前用户账号（手机号码）
    ((Label*)lab3)->SetContext(user->GetAccount());
    // 显示所有控件
    for(int i = 0; i < count; i++)
    {
        this->arr[i]->showCtrl();
    }
    if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎，"<<user->GetName()<<",普通用户!";
		
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
}

void PatientResetPasswordWin::clearEdits()
{
    ((Edit*)edit1)->SetContext("");
    ((Edit*)edit2)->SetContext("");
    ((Edit*)edit3)->SetContext("");
}

int PatientResetPasswordWin::doAction()
{
    // 确认按钮
    if(this->flag == 9)
    {
        BaseUser* currentUser = this->GetCurrentUser();
        if(currentUser == NULL)
        {
            Tool::gotoxy(35, 27);
            cout << "未获取到当前用户信息！";
            Sleep(1000);
            return 10;
        }
        
        // 获取输入内容
        string oldPwd = ((Edit*)edit1)->GetContext();
        string newPwd = ((Edit*)edit2)->GetContext();
        string confirmPwd = ((Edit*)edit3)->GetContext();
        
        // 1. 验证密码非空
        if(oldPwd.empty() || newPwd.empty() || confirmPwd.empty())
        {
            Tool::gotoxy(35, 27);
            cout << "密码不能为空！";
            Sleep(1000);
            return 10;
        }
        
        // 2. 验证密码长度为 6 位
        if(oldPwd.length() != 6 || newPwd.length() != 6 || confirmPwd.length() != 6)
        {
            Tool::gotoxy(35, 27);
            cout << "密码必须为6位数字！";
            Sleep(1000);
            return 10;
        }
        
        // 3. 验证原密码正确性
        if(currentUser->GetPassword() != oldPwd)
        {
            Tool::gotoxy(35, 27);
            cout << "原密码不正确！";
            Sleep(1000);
            return 12;
        }
        
        // 4. 验证新密码与确认密码一致
        if(newPwd != confirmPwd)
        {
            Tool::gotoxy(35, 27);
            cout << "两次输入的新密码不一致！";
            Sleep(1000);
            return 12;
        }
        
        // 5. 验证新密码与原密码不同
        if(newPwd == oldPwd)
        {
            Tool::gotoxy(35, 27);
            cout << "新密码不能与原密码相同！";
            Sleep(1000);
            return 12;
        }
        
        // 6. 修改密码并保存到文件
        this->currentUser->SetPassword(newPwd);
        UserManager::GetOusermanager()->saveAllUsers();
        
        Tool::gotoxy(35, 27);
        cout << "密码修改成功！";
        Sleep(1000);
        
        // 清空输入框
        this->clearEdits();
        return 10;
    }
    
    // 返回按钮（假设 btn2 的 flag 为 10）
    if(this->flag == 10)
    {
        this->clearEdits();
        return 10;
    }
    
    // 窗口关闭（flag = -1）
    if(this->flag == -1)
    {
        this->clearEdits();
        return 10;
    }
    
    return 10;
}
