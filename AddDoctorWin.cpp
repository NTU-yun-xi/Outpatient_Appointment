#include "AddDoctorWin.h"

AddDoctorWin::AddDoctorWin()
:Window()
{
	
}

AddDoctorWin::AddDoctorWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 45, 1, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 30, 4, 0, 0, "医生ID：");
    this->lab3 = new Label(LABEL, 40, 4, 0, 0, "");
    
	

    this->lab4 = new Label(LABEL, 30, 6, 0, 0, "医生姓名：");
    this->lab5 = new Label(LABEL, 30, 9, 0, 0, "所属医院：");
    this->lab6 = new Label(LABEL, 30, 12, 0, 0, "所属科室：");
    this->lab7 = new Label(LABEL, 30, 15, 0, 0, "医生职位：");
    this->lab8 = new Label(LABEL, 30, 18, 0, 0, "简介：");

    // 输入框初始化
    this->edit1 = new Edit(EDIT, 40, 5, 15, 3, "", 10, 0, 4); // 中文姓名(2-10位)
    this->edit2 = new Edit(EDIT, 40, 8, 15, 3, "省立医院", 0, 0, 0); // 固定医院,不可编辑
    this->edit3 = new Edit(EDIT, 40, 11, 10, 3, "", 0, 0, 4); // 科室(不可直接输入)
    this->edit4 = new Edit(EDIT, 40, 14, 10, 3, "", 0, 0, 4); // 职位(不可直接输入)
    this->edit5 = new Edit(EDIT, 40, 17, 20, 4, "", 50, 0, 4); // 中文简介

    // 按钮初始化
    this->btn1 = new Button(BUTTON, 60, 11, 4, 3, "↓"); // 科室下拉按钮
    this->btn2 = new Button(BUTTON, 60, 14, 4, 3, "↓"); // 职位下拉按钮
    this->btn3 = new Button(BUTTON, 40, 21, 8, 3, "确认");
    this->btn4 = new Button(BUTTON, 55, 21, 8, 3, "返回");

    // 下拉框初始化
    this->comboDept = new ComoboBoxWin(40, 17, 10, 2);
    this->comboPos = new ComoboBoxWin(40, 17, 10, 2);
    
    DepartmentManager* deptMgr = DepartmentManager::GetInstance();
    vector<Department*> allDepartments = deptMgr->getAllDepartments();
    vector<Department*>::iterator deptIter;
    int yPos = 14;
    
    for (deptIter = allDepartments.begin(); deptIter != allDepartments.end(); ++deptIter) 
	{
        Department* dept = *deptIter;
        string deptName = dept->GetDepName(); 
    
    	char* deptNameChar = new char[deptName.length() + 1]; 
    	strcpy(deptNameChar, deptName.c_str()); 
    	this->comboDept->addOption(40, yPos, 8, 3, deptNameChar);
        yPos += 3;
        
		delete[] deptNameChar;
    }
	
	this->comboPos->addOption(40,14,10,3,"专家");
	this->comboPos->addOption(40,17,10,3,"主任医师");
	this->comboPos->addOption(40,20,10,3,"副主任医师");
	this->comboPos->addOption(40,23,10,3,"主治医师"); 

    // 添加控件到窗口
    this->addControl(this->lab1);//0
    this->addControl(this->lab2);//1
    this->addControl(this->lab3);//2
    this->addControl(this->lab4);//3
    this->addControl(this->lab5);//4
    this->addControl(this->lab6);//5
    this->addControl(this->lab7);//6
    this->addControl(this->lab8);//7
    this->addControl(this->btn1);//8
    this->addControl(this->btn2);//9
    this->addControl(this->edit1);//10
    this->addControl(this->edit2);//11
    this->addControl(this->edit3);//12
    this->addControl(this->edit4);//13
    this->addControl(this->edit5);//14
    this->addControl(this->btn3);//15
    this->addControl(this->btn4);//16
}

AddDoctorWin::~AddDoctorWin() 
{
    delete this->lab1;
	delete this->lab2; 
	delete this->lab3; 
	delete this->lab4;
    delete this->lab5; 
	delete this->lab6; 
	delete this->lab7; 
	delete this->lab8;
    delete this->edit1; 
	delete this->edit2; 
	delete this->edit3; 
	delete this->edit4; 
	delete this->edit5;
    delete this->btn1; 
	delete this->btn2; 
	delete this->btn3; 
	delete this->btn4;
    delete this->comboDept; 
	delete this->comboPos;
}

void AddDoctorWin::clearEdits()
{
	((Edit*)this->edit1)->SetContext("");  
    ((Edit*)this->edit3)->SetContext("");  
    ((Edit*)this->edit4)->SetContext("");
    ((Edit*)this->edit5)->SetContext("");
}

// 绘制窗口
void AddDoctorWin::paintWindow() 
{
	string tempaccount = UserManager::GetOusermanager()->getTempstring();
	this->lab3->SetContext(tempaccount);
	
    Window::paintWindow();
     
    // 显示当前登录用户信息
    BaseUser* user = this->GetCurrentUser();
    if (user != NULL) {
        Tool::gotoxy(30, 2);
        cout << "欢迎您" << user->GetName() << ",管理员!";
    }
    
    // 显示当前日期
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char date[20];
    sprintf(date, "日期:%d-%02d-%02d",
            1900 + localTime->tm_year,
            1 + localTime->tm_mon,
            localTime->tm_mday);
    Tool::gotoxy(60, 2);
    cout << date;
}

// 处理用户操作
int AddDoctorWin::doAction() 
{
    if (this->flag == 8) 
	{
        this->comboDept->SetShow(!comboDept->GetShow());
        if (this->comboDept->GetShow()) 
		{
            //comboDept->SetPosition(edit3->GetX(), edit3->GetY() + edit3->GetHeight());
            this->comboDept->paintWindow();
            this->comboDept->winRun();
            int comboDeptRes = this->comboDept->doAction();
            if(comboDeptRes != -1)
            {
            	string dept = this->comboDept->GetOptionContext();
            	((Edit*)this->edit3)->SetContext(dept);
			}
            this->comboDept->SetShow(false);
        }
        return 8; // 保持在当前窗口
    }
    
    // 处理职位选择按钮（btn2）
    if (this->flag == 9) 
	{ 
        this->comboPos->SetShow(!comboPos->GetShow());
        if (this->comboPos->GetShow()) 
		{
            //comboPos->SetPosition(edit4->GetX(), edit4->GetY() + edit4->GetHeight());
            this->comboPos->paintWindow();
            this->comboPos->winRun();
            int comboPosRes = this->comboPos->doAction();
            if(comboPosRes != -1)
            {
            	string pos = this->comboPos->GetOptionContext();
            	((Edit*)this->edit4)->SetContext(pos);
			}
            this->comboPos->SetShow(false);
        }
        return 8; // 保持在当前窗口
    }
    
    // 处理确定按钮（btn3）
    if (this->flag == 15) 
	{ 
        // 获取表单数据
        string doctorId = lab3->GetContext();
        string name = dynamic_cast<Edit*>(edit1)->GetContext();
        string hospital = dynamic_cast<Edit*>(edit2)->GetContext();
        string dept = dynamic_cast<Edit*>(edit3)->GetContext();
        string position = dynamic_cast<Edit*>(edit4)->GetContext();
        string intro = dynamic_cast<Edit*>(edit5)->GetContext();
        
        // 验证
        if (name.empty() || dept.empty() || position.empty()) 
		{
            Tool::gotoxy(40, 22);
            cout << "姓名、科室和职位不能为空！";
            Sleep(1500);
            return 8; // 保持在当前窗口
        }
        
        // 创建医生对象并添加到系统
        Doctor* newDoctor = new Doctor();
        newDoctor->SetAccount(doctorId);
        newDoctor->SetName(name);
        newDoctor->SetHospital(hospital);
        newDoctor->SetDepartment(dept);
        newDoctor->SetPosition(position);
        newDoctor->SetContext(intro);
        newDoctor->SetRole(2); 
        newDoctor->SetPassword("123456");
        
        UserManager::GetOusermanager()->addUser(newDoctor);
        UserManager::GetOusermanager()->saveAllUsers();
        
        DepartmentManager* deptMgr = DepartmentManager::GetInstance();
        vector<Department*> allDepartments = deptMgr->getAllDepartments();
        vector<Department*>::iterator deptIter;
        
        for (deptIter = allDepartments.begin(); deptIter != allDepartments.end(); ++deptIter) 
		{
            Department* deptObj = *deptIter;
            if (deptObj->GetDepName() == dept) 
			{ 
                deptObj->AddDoctor(newDoctor); 
                break;
            }
        }
        
        deptMgr->saveAllDepartments();
        
        Tool::gotoxy(40, 22);
        cout << "医生信息添加成功！";
        Sleep(1500);
        this->clearEdits();
        return 7; // 返回医生查询窗口
    }
    
    // 处理取消按钮（btn4）
    if (this->flag == 16) 
	{ 
        return 7; // 返回医生查询窗口
    }
    
    // 处理窗口关闭
    if (this->flag == -1) 
	{
        return 7; // 返回医生查询窗口
    }
    
    return 8; // 默认保持在当前窗口
}
