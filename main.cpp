#include <iostream>

#include "Window.h"
#include "WindowManager.h"
#include "DepartmentManager.h"
#include "Doctor.h"
#include "WorkDate.h"

#include "Tool.h"
using namespace std;

int main(int argc, char** argv)
{
	WindowManager::GetInstance()->toShow();
	
	WindowManager::DestroyInstance();
//    Workdate workdate;
//    ofstream outFile;
//
//    // 显式打开文件（C++98兼容）
//    outFile.open("./data/day/days.txt");
//
//    if (outFile.is_open()) {
//        workdate.SaveToFile(outFile);
//        outFile.close();
//        cout << "带编号的日期写入成功！" << endl;
//    } else {
//        cerr << "无法打开文件./day/days.txt，请检查路径是否存在！" << endl;
//        return 1;
//    }
	return 0;
}

