#include "VisitRecordWin.h"

VisitRecordWin::VisitRecordWin()
:Window()
{
	this->currentAppointment = NULL;
}

VisitRecordWin::VisitRecordWin(int win_startX, int win_startY, int win_width, int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->lab1 = new Label(LABEL, 44, 5, 0, 0, "欢迎来到门诊预约管理系统");
	this->lab2 = new Label(LABEL,30,8,0,0,"用户  ID:");
	this->lab3 = new Label(LABEL,39,8,0,0,"");
	this->lab4 = new Label(LABEL,30,11,0,0,"预约描述");
	this->lab5 = new Label(LABEL,30,16,0,0,"就诊描述"); 
	this->edit1 = new Edit(EDIT,39,10,20,4,"",10,0,4);
	this->edit2 = new Edit(EDIT,39,15,20,4,"",10,0,4);
	this->btn1 = new Button(BUTTON,30,20,8,3,"确认");
	this->btn2 = new Button(BUTTON,40,20,8,3,"返回"); 
	
	this->addControl(this->lab1);
	this->addControl(this->lab2);
	this->addControl(this->lab3);
	this->addControl(this->lab4);
	this->addControl(this->lab5);
	this->addControl(this->edit1);
	this->addControl(this->edit2);
	this->addControl(this->btn1);
	this->addControl(this->btn2);
	
	this->currentAppointment = NULL;
}

VisitRecordWin::~VisitRecordWin()
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
	delete this->currentAppointment;
}

void VisitRecordWin::paintWindow()
{
	this->lab3->SetContext(this->currentAppointment->getPatientId());
	this->edit1->SetContext(this->currentAppointment->getDesc());
	this->edit2->SetContext(this->currentAppointment->getVisitDesc());
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
}

int VisitRecordWin::doAction()
{
	switch(this->flag)
	{
		case 7:
			this->saveVisitRecord();
			this->clearEdits();
			return 16;
		case 8:
			this->clearEdits();
			return 16;
	} 
}

void VisitRecordWin::clearEdits()
{
	((Edit*)this->edit2)->SetContext("");
}

void VisitRecordWin::saveVisitRecord()
{
	vector<Appointment*> apps = AppointmentManager::getInstance()->getallAppointments();
	this->currentAppointment->setVisitDesc(this->edit2->GetContext());
	this->currentAppointment->setState(3);
	string doctorId = this->currentAppointment->getDoctorId();
	vector<Appointment*> thisdocapps;
	vector<Appointment*>::iterator saveIter = apps.begin();
	for(saveIter; saveIter != apps.end(); ++saveIter)
    {
        Appointment* app = *saveIter;
        if(app != NULL && app->getDoctorId() == doctorId)
        {
        	if(app->getDay() == this->currentAppointment->getDay() && app->getTime() == this->currentAppointment->getTime())
			{
				thisdocapps.push_back(this->currentAppointment);
			}
			else
			{
				thisdocapps.push_back(app); 
			} 
        }
    }
    AppointmentManager::getInstance()->saveAppointments(doctorId, thisdocapps);
}

void VisitRecordWin::setAppointment(Appointment* app)
{
	this->currentAppointment = app;
}
