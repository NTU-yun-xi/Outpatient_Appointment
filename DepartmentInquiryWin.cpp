#include "DepartmentInquiryWin.h"
#include "DepartmentManager.h"
#include "Tool.h"
#include <time.h>
#include <iostream>

using namespace std;

DepartmentInquiryWin::DepartmentInquiryWin()
: Window()
{
    this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

DepartmentInquiryWin::DepartmentInquiryWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
    // 初始化控件
    this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎使用医院预约挂号系统");
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "请输入科室ID:");
    this->edit1 = new Edit(EDIT, 45, 7, 10, 3, "", 11, 0, 3);  // 科室ID输入框
    this->btn1 = new Button(BUTTON, 65, 7, 8, 3, "查询");      // 查询按钮
    this->btn2 = new Button(BUTTON, 30, 22, 8, 3, "返回");     // 返回按钮
    this->table1 = new Table(TABLE, 26, 10, 0, 0, "", 3, PAGE_SIZE + 1, 9, 1);  // 表格控件

    // 添加控件到窗口
    this->addControl(this->lab1);
    this->addControl(this->lab2);
    this->addControl(this->edit1);
    this->addControl(this->btn1);
    this->addControl(this->btn2);
    this->addControl(this->table1);
    
    // 新增：初始化无结果提示弹窗
    this->pop1 = new PopWin(30, 10, 20, 10);  // 设置弹窗位置和大小
    this->pop1->setTitle("提示:");             // 弹窗标题
    // 添加"确定"按钮
    this->pop1->addControl(new Label(LABEL,36,12,0,0,"科室信息不存在，请重新输入！"));
    this->pop1->addControl(new Button(BUTTON, 44, 15, 5, 3, "确定"));

    // 初始化分页参数
    this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

DepartmentInquiryWin::~DepartmentInquiryWin()
{
    // 释放控件内存
    delete this->lab1;
    delete this->lab2;
    delete this->edit1;
    delete this->btn1;
    delete this->btn2;
    delete this->table1;
    delete this->pop1;
}

vector<Department*> DepartmentInquiryWin::setcurrentDepartments()
{
    vector<Department*> displayDepartments = DepartmentManager::GetInstance()->getAllDepartments();
    string depID = ((Edit*)edit1)->GetContext();

    if (!depID.empty())
    {
        // 精确查找科室
        Department* exactDept = DepartmentManager::GetInstance()->findDepartment(depID);
        if (exactDept)
        {
            displayDepartments.clear();
            displayDepartments.push_back(exactDept);
        }
        else
        {
            // 模糊查找（根据科室名称）
            displayDepartments = DepartmentManager::GetInstance()->fuzzyFindByDepID(depID);
        }
    }

    return displayDepartments;
}

void DepartmentInquiryWin::clearEdits()
{
    ((Edit*)edit1)->SetContext("");
}

void DepartmentInquiryWin::paintWindow()
{
    Window::paintWindow();
    
    // 显示当前登录用户信息
    BaseUser* user = GetCurrentUser();
    if (user != NULL)
    {
        Tool::gotoxy(30, 6);
        cout << "欢迎," << user->GetName() << ",管理员!";
    }

    // 显示当前日期
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char date[20];
    sprintf(date, "日期:%d-%02d-%02d",
            1900 + localTime->tm_year,
            1 + localTime->tm_mon,
            localTime->tm_mday);
    Tool::gotoxy(60, 6);
    cout << date;

    // 显示表格标题
    Tool::gotoxy(34, 11);
    cout << "科室ID";
    Tool::gotoxy(51, 11);
    cout << "科室名称";
    Tool::gotoxy(70, 11);
    cout << "科室说明";

    // 获取科室数据并处理分页
    vector<Department*> departments = setcurrentDepartments();
    int deptCount = departments.size();

    // 计算总页数
    if (deptCount == 0)
    {
        this->total_pages = 1;
        this->current_page = 1;
    }
    else
    {
        this->total_pages = (deptCount % this->PAGE_SIZE == 0) 
            ? (deptCount / this->PAGE_SIZE) 
            : (deptCount / this->PAGE_SIZE + 1);
    }

    // 边界处理
    if (this->current_page > this->total_pages) this->current_page = this->total_pages;
    if (this->current_page < 1) this->current_page = 1;
    this->index = (this->current_page - 1) * this->PAGE_SIZE;

    // 绘制当前页数据
    int displayCount = 0;
    for (int i = this->index; i < deptCount && displayCount < this->PAGE_SIZE; i++)
    {
        Department* dept = departments[i];
        int rowY = 11 + 2 * (displayCount + 1);  // 行坐标计算

        Tool::gotoxy(33, rowY);
        cout << dept->GetDepID();

        Tool::gotoxy(48, rowY);
        cout << dept->GetDepName();

        Tool::gotoxy(65, rowY);
        cout << dept->GetDepContext();

        displayCount++;
    }

    // 显示分页信息
    Tool::gotoxy(45, 20);
    cout << "第 " << this->current_page << " 页 / 共 " << this->total_pages << " 页";
}

int DepartmentInquiryWin::doAction()
{
    // 上一页（flag=-100对应上一页按钮事件）
    if (this->flag == -100)
    {
        if (this->current_page > 1)
        {
            this->current_page--;
        }
        else
        {
            Tool::gotoxy(45, 19);
            cout << "已经是第一页!";
            Sleep(1000);
        }
        return 9;  // 返回当前窗口标识（假设9为科室查询窗口标识）
    }
    // 下一页（flag=-101对应下一页按钮事件）
    else if (this->flag == -101)
    {
        vector<Department*> departments = setcurrentDepartments();
        if (this->current_page < (departments.size() + this->PAGE_SIZE - 1) / this->PAGE_SIZE)
        {
            this->current_page++;
        }
        else
        {
            Tool::gotoxy(45, 19);
            cout << "已经是最后一页!";
            Sleep(1000);
        }
        return 9;
    }
    // 查询按钮（flag=3对应查询按钮）
    else if (this->flag == 3)
    {
    	vector<Department*> departments = setcurrentDepartments();
        if (departments.empty())
        {
            // 无结果时显示弹窗
            this->pop1->paintWindow();  // 绘制弹窗
            this->pop1->winRun();       // 运行弹窗消息循环
            int res = this->pop1->getResult();  // 获取按钮结果（确定按钮）
            if (res == 1)  // 假设"确定"按钮的结果为0
            {
                this->clearEdits();  // 清空输入框
                return 9;      // 返回科室查询界面
            }
        }
        this->current_page = 1;  // 重新查询时回到第一页
        return 9;
    }
    // 返回按钮（flag=4对应返回按钮）
    else if (this->flag == 4)
    {
        this->clearEdits();
        return 3;  // 返回主窗口（假设0为主窗口标识）
    }
    // 窗口关闭事件
    else if (this->flag == -1)
    {
        this->clearEdits();
        return 3;
    }

    return 9;
}
