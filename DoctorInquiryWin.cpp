#include "DoctorInquiryWin.h"

DoctorInquiryWin::DoctorInquiryWin()
:Window()
{
	this->current_page = 1;
	this->total_pages = 1;
	this->index = 0;
}

DoctorInquiryWin::DoctorInquiryWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "请输入医生ID:");
    this->edit1 = new Edit(EDIT, 45, 7, 10, 3, "", 11, 0, 3);  
    this->btn1 = new Button(BUTTON, 65, 7, 8, 3, "查询"); 
	this->btn2 = new Button(BUTTON, 20, 12, 2, 1, "");
	this->btn3 = new Button(BUTTON, 20, 14, 2, 1, "");
	this->btn4 = new Button(BUTTON, 20, 16, 2, 1, "");
    dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	dynamic_cast<Button*>(this->btn4)->setShowMode(1);
	this->btn5 = new Button(BUTTON, 30, 22, 8, 3, "返回");     
    this->table1 = new Table(TABLE, 25, 10, 0, 0, "", 6, PAGE_SIZE + 1, 5, 1);
    
    this->addControl(lab1);
    this->addControl(lab2);
    this->addControl(edit1);
    this->addControl(btn1);
    this->addControl(btn2);
    this->addControl(btn3);
    this->addControl(btn4);
    this->addControl(btn5);
    this->addControl(table1);
    
    this->pop1 = new PopWin(40, 10, 20, 10);
    this->pop1->setTitle("提示：医生不存在");
	this->pop1->addControl(new Button(BUTTON, 50, 12, 8, 3, "重新输入"));
	this->pop1->addControl(new Button(BUTTON, 50, 15, 8, 3, "新增医生"));
    
    this->pop2 = new PopWin(40,10,20,10);
    this->pop2->setTitle("提示：修改职位");
	this->pop2->addControl(new Label(LABEL,42,12,0,0,"医生ID:"));
	this->pop2->addControl(new Label(LABEL,50,12,0,0,"")); 
	this->pop2->addControl(new Label(LABEL,42,14,0,0,"职  位:"));
	this->pop2->addControl(new Edit(EDIT,50,13,10,3,"",4,0,4));
	this->pop2->addControl(new Button(BUTTON,70,13,4,3,"↓"));
	this->pop2->addComboBox(new ComoboBoxWin(50,16,4,10));
	vector<ComoboBoxWin*>* combos = this->pop2->getComboBoxes();
	if(!combos->empty())
	{
		ComoboBoxWin* combo1 = combos->at(0);
		combo1->addOption(50,16,10,3,"专家");
		combo1->addOption(50,19,10,3,"主任医师");
		combo1->addOption(50,22,10,3,"副主任医师");
		combo1->addOption(50,25,10,3,"主治医师");
	    combo1->SetShow(false);
	}
	this->pop2->addControl(new Button(BUTTON,44,16,5,3,"确定"));
	this->pop2->addControl(new Button(BUTTON,54,16,5,3,"返回"));
    
	this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

DoctorInquiryWin::~DoctorInquiryWin()
{
	delete this->lab1;
    delete this->lab2;
    delete this->edit1;
    delete this->btn1;
    delete this->btn2;
    delete this->table1;
    delete this->pop1; 
}

vector<Doctor*> DoctorInquiryWin::setcurrentDoctors()
{
	vector<Doctor*> displayDoctors = UserManager::GetOusermanager()->getAllDoctors();
    string account = ((Edit*)edit1)->GetContext();
    if (account.empty()) {
        // 为空时显示所有医生
        displayDoctors = UserManager::GetOusermanager()->getAllDoctors();
    } else {
        // 只进行精确查询
        BaseUser* exactUser = UserManager::GetOusermanager()->findUser(account);
        if (exactUser && exactUser->GetRole() == 2) {
        	displayDoctors.clear();
            displayDoctors.push_back(static_cast<Doctor*>(exactUser));
        }else
        {
        	displayDoctors.clear();
		}
    }
    return displayDoctors;
}
	
void DoctorInquiryWin::clearEdits()
{
	((Edit*)this->edit1)->SetContext("");
}

void DoctorInquiryWin::paintWindow()
{
	dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	dynamic_cast<Button*>(this->btn4)->setShowMode(1);
	Window::paintWindow();
	BaseUser* user = this->GetCurrentUser();
	if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎您"<<user->GetName()<<",管理员!";
		
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
	Tool::gotoxy(60,22);
	cout<<"按←→键翻页";
	Tool::gotoxy(60,23);
	cout<<"按↑↓键选择数据";
	
	// 绘制表格标题
	Tool::gotoxy(28, 11);
	cout << "医生ID";
    Tool::gotoxy(38, 11);
    cout << "医生姓名";
    Tool::gotoxy(51, 11);
    cout << "职位";
    Tool::gotoxy(60, 11);
    cout << "所属科室";
    Tool::gotoxy(71, 11);
    cout << "所属医院";
    Tool::gotoxy(84, 11);
    cout << "简介";
    
    vector<Doctor*> doctors = this->setcurrentDoctors();
    int doctorCount = doctors.size();
    
    // 计算总页数
    if (doctorCount == 0)
    {
        this->total_pages = 1;
        this->current_page = 1;
    }
    else
    {
        this->total_pages = (doctorCount % this->PAGE_SIZE == 0) 
            ? (doctorCount / this->PAGE_SIZE) 
            : (doctorCount / this->PAGE_SIZE + 1);
    }
    
    // 边界处理
    if (this->current_page > this->total_pages) 
	{
		this->current_page = this->total_pages;
	}
    if (this->current_page < 1)
	{
		this->current_page = 1;
	} 
    this->index = (this->current_page - 1) * this->PAGE_SIZE;
    
    // 绘制当前页数据
    int displayCount = 0;
    for (int i = this->index; i < doctorCount && displayCount < this->PAGE_SIZE; i++)
    {
        Doctor* doctor = doctors[i];
        int rowY = 11 + 2 * (displayCount + 1);  

        Tool::gotoxy(26, rowY);
        cout << doctor->GetAccount();

        Tool::gotoxy(37, rowY);
        cout << doctor->GetName();

        Tool::gotoxy(48, rowY);
        cout << doctor->GetPosition();

        Tool::gotoxy(59, rowY);
        cout << doctor->GetDepartment();

        Tool::gotoxy(70, rowY);
        cout << doctor->GetHospital();

        Tool::gotoxy(81, rowY);
        cout << doctor->GetContext();

        displayCount++;
    }
    
    // 显示分页信息
    Tool::gotoxy(45, 20);
    cout << "第 " << this->current_page << " 页 / 共 " << this->total_pages << " 页";
}

void DoctorInquiryWin::prevPage()
{
	if (this->current_page > 1)
    {
        this->current_page--;
    }
    else
    {
    	Tool::gotoxy(45,19);
        cout << "已经是第一页了!";
        Sleep(1000);
    }
} 

void DoctorInquiryWin::nextPage()
{
	vector<Doctor*> doctors = this->setcurrentDoctors();
    if (this->current_page < (doctors.size() + this->PAGE_SIZE - 1) / this->PAGE_SIZE)
    {
        this->current_page++;
    }
    else
    {
    	Tool::gotoxy(45,19);
        cout << "已经是最后一页了!";
        Sleep(1000);
    }
}

int DoctorInquiryWin::doCheck()
{
	string account = ((Edit*)edit1)->GetContext();
	vector<Doctor*> doctors = this->setcurrentDoctors();
    if(doctors.empty() && !account.empty())
    {
    	
    	this->pop1->paintWindow();
    	this->pop1->winRun();
    	int res = this->pop1->getResult();
    	if(res == 0)
    	{
    		this->clearEdits();
			return 7;
		}else if(res == 1)
		{
			UserManager::GetOusermanager()->setTempstring(account);
			this->clearEdits();
			return 8; 
		}
	}
	this->current_page = 1; // 重新查询时回到第一页
	return 7;
}

int DoctorInquiryWin::doRsetDoctor()
{
	int rowIndex = this->flag - 4;
	
	vector<Doctor*> doctors = this->setcurrentDoctors();
	
	int globalIndex = this->index + rowIndex;
	if(globalIndex < 0 || globalIndex >= (int)doctors.size())
	{
		return 7;
	}
	
	Doctor* currentDoctor = doctors[globalIndex];
	if(currentDoctor == NULL)
	{
		return 7;
	}
	
	vector<Ctrl*>* popCtrls = this->pop2->getCtrls();
	Label* idLab = dynamic_cast<Label*>(popCtrls->at(1));
	Edit* posEdit = dynamic_cast<Edit*>(popCtrls->at(3));
	if(!popCtrls->empty())
	{
		if(idLab != NULL)
		{
			idLab->SetContext(currentDoctor->GetAccount());
		}	
		if(posEdit != NULL)
		{
			posEdit->SetContext(currentDoctor->GetPosition());		
		}
	}
	
	vector<ComoboBoxWin*>* combos = this->pop2->getComboBoxes();
	ComoboBoxWin* combo1 = NULL;
	if(!combos->empty())
	{
		combo1 = combos->at(0);
	}
	
	int pop2Res;
	while(true)
	{
		this->pop2->paintWindow();
		this->pop2->winRun();
		pop2Res = this->pop2->getResult();
        
        if(pop2Res == 4)
        {
            // 处理下拉框逻辑，继续循环保持弹窗
            this->doCombo(combo1);
            this->paintWindow();
            this->pop2->paintWindow();
        }
        else if(pop2Res == 5)
        {
            if(posEdit != NULL && currentDoctor != NULL)
            {
            	// 更新当前医生的职位信息
                currentDoctor->SetPosition(posEdit->GetContext());
                // 调用UserManager保存所有用户信息到文件
        		UserManager::GetOusermanager()->saveAllUsers();
            }
            // 处理完成后退出循环
            break;
        }
        else if(pop2Res == 6)
        {
            // 直接退出循环
            break;
        }
    }
    
    // 确认和返回时均返回7
    return 7;
}

void DoctorInquiryWin::doCombo(ComoboBoxWin* combo)
{
	Ctrl* posEdit = this->pop2->getCtrls()->at(3);
	combo->SetShow(!combo->GetShow());
	if(combo->GetShow())
	{
		//combo->SetPosition(posEdit->GetX(),posEdit->GetY()+posEdit->GetHeight());
		combo->paintWindow();
		combo->winRun();
		int comboRes = combo->doAction();
		if(comboRes != -1)
		{
			string updatePosition = combo->GetOptionContext();
			((Edit*)posEdit)->SetContext(updatePosition);
		}
		combo->SetShow(false);
	}
}

int DoctorInquiryWin::doAction()
{
    // 左键：上一页
    if (this->flag == -100)  
    {
        this->prevPage();
        return 7; // 返回医生管理页面标识（根据实际业务调整）
    }
    // 右键：下一页
    else if (this->flag == -101)
    {
    	this->nextPage();
        return 7;
    }
    
	// 查询按钮
    else if (this->flag == 3) 
    {
        return this->doCheck();
    }
    
    //  表格行按钮 
    else if(this->flag >= 4 && this->flag <= 6)
    {
    	return this->doRsetDoctor();
	}
    // 返回按钮
    else if (this->flag == 7)
    {
    	this->clearEdits();
        return 3; // 返回管理员主页面（根据实际业务调整）
    }
    
	// ESC键返回
    else if (this->flag == -1)
    {
    	this->clearEdits();
        return 3;
    }

    return 7;
}
