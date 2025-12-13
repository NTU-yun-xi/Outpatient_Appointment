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
    this->lab2 = new Label(LABEL, 30, 8, 0, 0, "输入就诊日期");
    this->lab3 = new Label(LABEL, 50, 8, 0, 0, "至");
    this->edit1 = new Edit(EDIT, 45, 7, 10, 3, "", 11, 0, 3);
	this->edit2 = new Edit(EDIT,55,7,10,3,"",11,0,3);  
    this->btn1 = new Button(BUTTON, 75, 7, 8, 3, "查询"); 
	this->btn2 = new Button(BUTTON, 20, 12, 2, 1, "");
	this->btn3 = new Button(BUTTON, 20, 14, 2, 1, "");
	this->btn4 = new Button(BUTTON, 20, 16, 2, 1, "");
	dynamic_cast<Button*>(this->btn2)->setShowMode(1);
	dynamic_cast<Button*>(this->btn3)->setShowMode(1);
	dynamic_cast<Button*>(this->btn4)->setShowMode(1);
	this->btn5 = new Button(BUTTON,30,22,8,3,"返回");
	this->table = new Table(TABLE,25,10,0,0,"",7,this->PAGE_SIZE+1,5,1);
	
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
	vector<Appointment*> displayapps = AppointmentManager::getInstance();
	string startday = ((Edit*)edit1)->GetContext();
	string endday = ((Edit*)edit2)->GetContext();
	//找"./data/day/days.txt"中有没有startday到endday的时间
	// "./data/day/days.txt"内容格式： 1 2025年12月14日（换行） 2 2025年12月15日...共7天 
	//如果有匹配的日期，再找所有的"./data/appointments/医生ID（例：D1001、D1002）.txt" 
	//"./data/appointments/医生ID（例：D1001、D1002）.txt"内容格式：1（1-7对应day） 1（1-12对应time） 用户账号（例：12345678912） 医生ID（D1001与该文件名保持一致） 预约描述 就诊记录（初始为*） 就诊状态 
	//"./data/time/times.txt"内容： 1 9:00-10:00 1
	/*								2 9:00-10:00 2
									3 10:00-11:00 1
									4 10:00-11:00 2
									5 11:00-12:00 1
									6 11:00-12:00 2
									7 13:00-14:00 1
									8 13:00-14:00 2
									9 14:00-15:00 1
									10 14:00-15:00 2
									11 15:00-16:00 1
									12 15:00-16:00 2
	*/
}

//绘制窗体 
void TakeNumWin::paintWindow()
{
	int num = //获取当前表单中未就诊且时间在btn2-4所选项时间之前的人数 
	string pop1Title = "提示：当前排队人数："+num+"人"; 
	this->pop1->setTitle(pop1Title);
	
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
	
	Tool::gotoxy(28, 11);
	cout << "预约编号";
    Tool::gotoxy(38, 11);
    cout << "预约时间";
    Tool::gotoxy(51, 11);
    cout << "预约就诊时间";
    Tool::gotoxy(60, 11);
    cout << "预约医院";
    Tool::gotoxy(71, 11);
    cout << "预约科室";
    Tool::gotoxy(84, 11);
    cout << "预约医生";
    Tool::gotoxy(94, 11);
    cout << "就诊状态";
    
    vector<Appointment*> apps = this->setcurrentapps();
	int appcount = apps.size();
	
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
    for (int i = this->index; i < appcount && displayCount < this->PAGE_SIZE; i++)
    {
        Appointment* app = apps[i];
        int rowY = 11 + 2 * (displayCount + 1);  

        Tool::gotoxy(26, rowY);
        cout << i+1;

        Tool::gotoxy(37, rowY);
        cout << app->getDay();

        Tool::gotoxy(48, rowY);
        cout << app->getTime();

        Tool::gotoxy(59, rowY);
        cout << "省立医院";

        Tool::gotoxy(70, rowY);
        cout << //app->getDoctorId()获取医生ID,通过用户管理器 的map容器获取 医生科室 

        Tool::gotoxy(81, rowY);
        cout << //app->getDoctorId()获取医生ID,通过用户管理器 的map容器获取 医生姓名 
        
        Tool::gotoxy(91,rowY);
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
		case 5:
			//执行查询
		case 6-8:
			//更具所在行数据弹出弹窗
		case 9:
			//返回
		case -1:
			//返回
		default:
			//当前页面 
	}
}

void TakeNumWin::clearEdits()
{
	
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

//查询，按照输入的startday和endday执行setcurrentDoctors获取需要 显示的数据记录 
int TakeNumWin::doCheck()
{
	
}

