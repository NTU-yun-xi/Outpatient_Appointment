#ifndef DEPARTMENTINQUIRYWIN_H
#define DEPARTMENTINQUIRYWIN_H

#include "Window.h"
#include "PopWin.h"
#include <vector>
#include "Department.h"
using namespace std;

class DepartmentInquiryWin : public Window
{
public:
    DepartmentInquiryWin();
    DepartmentInquiryWin(int win_startX, int win_startY, int win_width, int win_height);
    ~DepartmentInquiryWin();

    void paintWindow();
    int doAction();

    vector<Department*> setcurrentDepartments();

    void clearEdits();

private:
    Ctrl* lab1;       // 欢迎标题
    Ctrl* lab2;       // 输入提示标签
    Ctrl* edit1;      // 科室ID输入框
    Ctrl* btn1;       // 查询按钮
    Ctrl* btn2;       // 返回按钮
    Ctrl* table1;     // 表格控件
    PopWin* pop1; 

    static const int PAGE_SIZE = 3;  // 每页显示数量
    int current_page;                // 当前页码
    int total_pages;                 // 总页数
    int index;                       // 当前页起始索引
};

#endif
