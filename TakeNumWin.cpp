#include "TakeNumWin.h"

TakeNumWin::TakeNumWin()
:Window()
{
	this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

TakeNumWin::TakeNumWin(int win_startX,int win_startY,int win_width,int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎来到门诊预约管理系统");
    this->lab2 = new Label(LABEL, 20, 8, 0, 0, "输入就诊日期");
    this->lab3 = new Label(LABEL, 52, 8, 0, 0, "至");
    this->edit1 = new Edit(EDIT, 33, 7, 10, 3, "", 8, 0, 3);
	this->edit2 = new Edit(EDIT,55,7,10,3,"",8,0,3);  
    this->btn1 = new Button(BUTTON, 75, 7, 8, 3, "查询"); 
	this->btn2 = new Button(BUTTON, 11, 12, 2, 1, "");
	this->btn3 = new Button(BUTTON, 11, 14, 2, 1, "");
	this->btn4 = new Button(BUTTON, 11, 16, 2, 1, "");
	dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	dynamic_cast<Button*>(this->btn4)->setShowMode(1);
	this->btn5 = new Button(BUTTON,30,22,8,3,"返回");
	this->table = new Table(TABLE,16,10,0,0,"",7,this->PAGE_SIZE+1,6,1);
	
	this->addControl(this->lab1);
	this->addControl(this->lab2);
	this->addControl(this->lab3);
	this->addControl(this->edit1);
	this->addControl(this->edit2);
	this->addControl(this->btn1);
	this->addControl(this->btn2);
	this->addControl(this->btn3);
	this->addControl(this->btn4);
	this->addControl(this->btn5);
	this->addControl(this->table);
	
	this->pop1 = new PopWin(40, 10, 20, 10);
	this->pop1->addControl(new Button(BUTTON,50, 12, 4, 3,"取号"));
	this->pop1->addControl(new Button(BUTTON,56, 12, 8, 3,"取消预约"));
	this->pop1->addControl(new Button(BUTTON,70,12,4,3,"返回")); 
	
	this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

TakeNumWin::~TakeNumWin()
{
	delete this->lab1;
	delete this->lab2;
	delete this->lab3;
	delete this->edit1;
	delete this->edit2;
	delete this->btn1;
	delete this->btn2;
	delete this->btn3;
	delete this->btn4;
	delete this->btn5;
	delete this->pop1;
}

//获取显示预约记录（就诊状态为0-未就诊 或 2-已取消 ——即过滤1、3） 
vector<Appointment*> TakeNumWin::setcurrentapps()
{
	vector<Appointment*> allapps = AppointmentManager::getInstance()->getallAppointments();
	vector<Appointment*>::iterator iter = allapps.begin();
	vector<Appointment*> displayapps;
	string startday = ((Edit*)edit1)->GetContext();
	string endday = ((Edit*)edit2)->GetContext();
	Workdate workdate;
	vector<string> sevendays = workdate.GetSevenDays(); // 通过实例调用
	vector<string>::iterator sevenIter = sevendays.begin();
	vector<string> checkdays;
	for (sevenIter; sevenIter != sevendays.end(); ++sevenIter) {
        checkdays.push_back(Tool::keepOnlyDigits(*sevenIter));
    }
	int startIdx = -1, endIdx = -1;
	for (int i = 0; i < 7; ++i) {
        if (startday == checkdays[i]) {
            startIdx = i;
        }
        if (endday == checkdays[i]) {
            endIdx = i;
        }
    }
    
    bool dateValid = false;
    if (startday.empty() && endday.empty()) {
        dateValid = true;
    } else if (startIdx != -1 && endIdx != -1 && startIdx <= endIdx) {
        dateValid = true;
    } else {
        return displayapps; 
    }
    
	for (iter = allapps.begin(); iter != allapps.end(); ++iter) {
        Appointment* app = *iter; 
        if (app == NULL) { 
            continue;
        }
		
        // 状态筛选：只保留0（未就诊）或2（已取消） 
        if (app->getState() == 1 || app->getState() == 3) {
            continue;
        }

        int appDay = app->getDay();
        if (appDay < 1 || appDay > 7) {
            continue;
        }
        int appIdx = appDay - 1;

        if (dateValid) 
		{
            if (startday.empty() || endday.empty()) 
			{
                displayapps.push_back(app);
            } else 
			{
                if (appIdx >= startIdx && appIdx <= endIdx) 
				{
                    displayapps.push_back(app);
                }
            }
        }
    }
    return displayapps;
}

//绘制窗体 
void TakeNumWin::paintWindow()
{	
	this->showapps = this->setcurrentapps();
	dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	dynamic_cast<Button*>(this->btn4)->setShowMode(1);
	Window::paintWindow();
	BaseUser* user = this->GetCurrentUser();
	if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎您"<<user->GetName()<<",用户!";
		
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
	
	Tool::gotoxy(19, 11);
	cout << "预约编号";
    Tool::gotoxy(32, 11);
    cout << "预约时间";
    Tool::gotoxy(43, 11);
    cout << "预约就诊时间";
    Tool::gotoxy(58, 11);
    cout << "预约医院";
    Tool::gotoxy(71, 11);
    cout << "预约科室";
    Tool::gotoxy(84, 11);
    cout << "预约医生";
    Tool::gotoxy(96, 11);
    cout << "就诊状态";
    
	int appcount = this->showapps.size();
	
	// 计算总页数
    if (appcount == 0)
    {
        this->total_pages = 1;
        this->current_page = 1;
    }
    else
    {
        this->total_pages = (appcount % this->PAGE_SIZE == 0) 
            ? (appcount / this->PAGE_SIZE) 
            : (appcount / this->PAGE_SIZE + 1);
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
    for (int i = this->index; i < appcount && displayCount < this->PAGE_SIZE; i++)
    {
        Appointment* app = this->showapps[i];
        int rowY = 11 + 2 * (displayCount + 1);  

        Tool::gotoxy(23, rowY);
        cout << i+1;

        Tool::gotoxy(31, rowY);
        Workdate workDate;
    	vector<string> allDays = workDate.GetSevenDays();
        int dayIndex = app->getDay() - 1;
		cout<< allDays[dayIndex]; 

        Tool::gotoxy(44, rowY);
        string timeSlot = "";
        // 修正：声明文件流、行变量和字符串流（C++98 需在块开头声明）
        ifstream timeFile;       // 声明timeFile
        string line;             // 声明line
        istringstream iss;       // 声明iss

        timeFile.open("./data/time/times.txt");
        if (timeFile.is_open())
        {
            while (getline(timeFile, line))
            {
                iss.clear();      // 清空流状态
                iss.str(line);    // 绑定当前行
                int id = 0;
                string timeStr = "";
                string num = "";
                if (iss >> id >> timeStr >> num && id == app->getTime())
                {
                    timeSlot = timeStr;
                    break;
                }
            }
            timeFile.close();
        }
        if (timeSlot.empty())
        {
            cout << "未知时段";
        }
        else
        {
            cout << timeSlot;
        }


        Tool::gotoxy(58, rowY);
        cout << "省立医院";

        Tool::gotoxy(71, rowY);
        BaseUser* baseUser = UserManager::GetOusermanager()->findUser(app->getDoctorId()); 
        Doctor* doctor = NULL;
		if (baseUser != NULL && baseUser->GetRole() == 2) { // 角色2为医生（根据代码逻辑）
		    doctor = dynamic_cast<Doctor*>(baseUser);
		}
		if (doctor != NULL) 
        {
            cout << doctor->GetDepartment(); 
        }
        else
        {
            cout << "未知科室";
        }

        Tool::gotoxy(84, rowY);
        if (doctor != NULL)
        {
            cout << doctor->GetName();
        }
        else
        {
            cout << "未知医生";
        }
        
        Tool::gotoxy(96,rowY);
        if(app->getState() == 0)
        {
        	cout<<"未就诊"; 
		}else if(app->getState() == 2)
		{
			cout<<"已取消";
		}
        

        displayCount++;
    }
    
    // 显示分页信息
    Tool::gotoxy(45, 20);
    cout << "第 " << this->current_page << " 页 / 共 " << this->total_pages << " 页"; 
}

int TakeNumWin::doAction()
{
	switch(this->flag)
	{
		case -100:
			this->prevPage();
			return 15;
		case -101:
			this->nextPage();
			return 15;
		case 5:
			this->doCheck();
			this->clearEdits();
			return 15;
		case 6:
		case 7:
		case 8:
			return this->doPop();
		case 9:
		case -1:
			this->clearEdits();
			return 5;
		default:
			return 15; 
	}
}

void TakeNumWin::clearEdits()
{
	((Edit*)this->edit1)->SetContext("");
	((Edit*)this->edit2)->SetContext("");
}

void TakeNumWin::prevPage()
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

void TakeNumWin::nextPage()
{
	vector<Appointment*> apps = this->setcurrentapps();
    if (this->current_page < (apps.size() + this->PAGE_SIZE - 1) / this->PAGE_SIZE)
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

//查询，按照输入的startday和endday执行setcurrentDoctors获取需要 显示的数据记录 
int TakeNumWin::doCheck()
{
	this->showapps = this->setcurrentapps();
}

int TakeNumWin::doPop()
{
	int rowIndex = this->flag - 6;
	
	vector<Appointment*> apps = this->setcurrentapps();
	vector<Appointment*>::iterator iter = apps.begin(); 
	int globalIndex = this->index + rowIndex;
	if(globalIndex < 0 || globalIndex >= (int)apps.size())
	{
		return 15;
	}
	
	Appointment* targetApp  = apps[globalIndex];
	if(targetApp == NULL)
	{
		return 15;
	}

	int num = 0;
	vector<Appointment*>::iterator countIter = apps.begin();
	for(countIter ; countIter  != apps.end(); ++countIter )
	{
		Appointment* app = *iter;
		if(app == NULL) continue;
        
        // 条件1：仅统计状态为0（未就诊）的预约
        if(app->getState() != 0)
        {
            continue;
        }
        
        // 条件2：时间在当前选中预约之前
        int targetDay = targetApp->getDay();
        int targetTime = targetApp->getTime();
        int currDay = app->getDay();
        int currTime = app->getTime();
        
        if(currDay < targetDay)
        {
            num++; // 日期更早，计入排队
        }
        else if(currDay == targetDay)
        {
            if(currTime < targetTime)
            {
                num++; // 日期相同，时间更早，计入排队
            }
        }
	}
	string pop1Title = "提示：当前排队人数：" + Tool::intToString(num) + "人";
    this->pop1->setTitle(const_cast<char*>(pop1Title.c_str()));
    
    vector<Ctrl*>* popCtrls = this->pop1->getCtrls();
    int popRes;
    while(true)
    {
    	this->pop1->paintWindow();
    	this->pop1->winRun();
    	popRes = this->pop1->getResult();
    	if(popRes == 0)
    	{
    		targetApp->setState(1);
    		string doctorId = targetApp->getDoctorId();
    		vector<Appointment*> thisdocapps;
    		vector<Appointment*>::iterator saveIter = apps.begin();
			for(saveIter; saveIter != apps.end(); ++saveIter)
            {
                Appointment* app = *saveIter;
                if(app != NULL && app->getDoctorId() == doctorId)
                {
                    thisdocapps.push_back(app); 
                }
            }
            AppointmentManager::getInstance()->saveAppointments(doctorId, thisdocapps);
            break;
		}else if(popRes == 1)
		{
			targetApp->setState(2);
			string doctorId = targetApp->getDoctorId();
            vector<Appointment*> thisdocapps;
    		vector<Appointment*>::iterator saveIter = apps.begin();
			for(saveIter; saveIter != apps.end(); ++saveIter)
            {
                Appointment* app = *saveIter;
                if(app != NULL && app->getDoctorId() == doctorId)
                {
                    thisdocapps.push_back(app); 
                }
            }
            AppointmentManager::getInstance()->saveAppointments(doctorId, thisdocapps);
            break;
		}else if(popRes == 2)
		{
			break;
		} 
	}
	return 15;
}	
