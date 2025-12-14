#include "DoctorVisitQueryWin.h"

DoctorVisitQueryWin::DoctorVisitQueryWin()
:Window() 
{
	this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
}

DoctorVisitQueryWin::DoctorVisitQueryWin(int win_startX, int win_startY, int win_width, int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎来到门诊预约管理系统");
	this->btn1 = new Button(BUTTON, 25, 12, 2, 1, "");
	this->btn2 = new Button(BUTTON, 25, 14, 2, 1, "");
	this->btn3 = new Button(BUTTON, 25, 16, 2, 1, "");
	this->btn4 = new Button(BUTTON,30,22,8,3,"返回");
	this->table = new Table(TABLE,30,10,0,0,"",3,this->PAGE_SIZE+1,6,1);

	this->addControl(this->lab1);
	this->addControl(this->btn1);
	this->addControl(this->btn2);
	this->addControl(this->btn3);
	this->addControl(this->btn4);
	this->addControl(this->table);
	
	this->current_page = 1;
    this->total_pages = 1;
    this->index = 0;
    
}

DoctorVisitQueryWin::~DoctorVisitQueryWin()
{
	delete this->lab1;
	delete this->btn1;
	delete this->btn2;
	delete this->btn3;
	delete this->btn4;
	delete this->table;
}

void DoctorVisitQueryWin::paintWindow()
{
	dynamic_cast<Button*>(this->btn1)->setShowMode(1);
	dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	Window::paintWindow();
	BaseUser* user = this->GetCurrentUser();
	if(user != NULL)
	{
		Tool::gotoxy(30,6);
		cout<<"欢迎您"<<user->GetName()<<",医生!";
		
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
	
	Tool::gotoxy(35, 11);
	cout << "编号";
    Tool::gotoxy(45, 11);
    cout << "就诊用户ID";
    Tool::gotoxy(57, 11);
    cout << "状态";	
	
	this->showVisits = this->setcurrentVisits();
	int appcount = this->showVisits.size();
	 
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
	
	int displayCount = 0;
	for(int i = this->index; i < appcount && displayCount < this->PAGE_SIZE; i++)
	{
		Appointment* app = this->showVisits[i];
        int rowY = 11 + 2 * (displayCount + 1);
        
        Tool::gotoxy(35, rowY);
        cout << i+1;

        Tool::gotoxy(44, rowY);
        cout<<app->getPatientId();
        
        Tool::gotoxy(58, rowY);
        if(app->getState() == 1)
        {
        	cout<<"等待就诊"; 
		}else if(app->getState() == 3)
		{
			cout<<"已就诊";
		}
		
		displayCount++; 
	}
	Tool::gotoxy(45, 20);
    cout << "第 " << this->current_page << " 页 / 共 " << this->total_pages << " 页"; 
}

int DoctorVisitQueryWin::doAction()
{
	switch(this->flag)
	{
		case -100:
			this->prevPage();
			return 16;
		case-101:
			this->nextPage();
			return 16;
		case 1:
		case 2:
		case 3:
			this->selctapp(); 
			return 17;
		case 4:
			return 4;
		default:
			return 16;
	}
}

vector<Appointment*> DoctorVisitQueryWin::setcurrentVisits()
{
	BaseUser* user = this->GetCurrentUser();
	string DocId = user->GetAccount();
	vector<Appointment*> allapps = AppointmentManager::getInstance()->getallAppointments();
	vector<Appointment*> thisdocapp;
	vector<Appointment*>::iterator iter1 = allapps.begin();
	for(iter1; iter1!=allapps.end();++iter1)
	{
		Appointment* tempapp = *iter1;
		if(tempapp->getDoctorId() == DocId)
		{
			thisdocapp.push_back(tempapp);
		}
	}
	vector<Appointment*> showapps;
	vector<Appointment*>::iterator iter2 = thisdocapp.begin();
	for(iter2;iter2!=thisdocapp.end();++iter2)
	{
		Appointment* tempapp = *iter2;
		if(tempapp->getState() == 1 || tempapp->getState() == 3)
		{
			showapps.push_back(tempapp);
		}
	}
	return showapps;
}

void DoctorVisitQueryWin::prevPage()
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

void DoctorVisitQueryWin::nextPage()
{
	if(this->current_page < (this->showVisits.size() + this->PAGE_SIZE - 1) / this->PAGE_SIZE)
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

void DoctorVisitQueryWin::selctapp()
{
	int rowIndex = this->flag - 1;
	int globalIndex = this->index + rowIndex;
	if(globalIndex < 0 || globalIndex >= (int)this->showVisits.size())
	{
		return ;
	}
	Appointment* selectedApp = this->showVisits[globalIndex];
    if(selectedApp == NULL)
    {
        return ;
    }
    this->SetCurrentApp(selectedApp);
	WindowManager::GetInstance()->UpdateMainApp(this->mainApp); 
    
}
