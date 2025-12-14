#include "WindowManager.h"

WindowManager* WindowManager::instance = NULL;

WindowManager::WindowManager()
{
	this->initwin = new InitWin(20, 5, 40, 20);
	this->registerwin = new RegisterWin(30, 5, 25, 20);
	this->loginwin = new LoginWin(20, 5, 40, 25);
	this->adminwin = new AdminWin(20, 5, 40, 25);
	this->doctorwin = new DoctorWin(20,5,40,25);
	this->patientwin = new PatientWin(20,5,40,25);
	this->userinquirywin = new UserInquiryWin(12,5,50,25);
	this->doctorinquirywin = new DoctorInquiryWin(12,5,50,25);
	this->adddoctorwin = new AddDoctorWin(12,0,40,25);
	this->departmentinquirywin = new DepartmentInquiryWin(12,5,45,25);
	this->patientperwin = new PatientPerWin(20,5,40,25);
	this->patientupdatewin = new PatientUpdateWin(20,5,40,25);
	this->patientresetpasswordwin = new PatientResetPasswordWin(20,5,40,25);
	this->appointmentmanagewin = new AppointmentManageWin(20,5,40,25);
	this->appointmentwin = new AppointmentWin(20,0,40,30);
	this->takenumwin = new TakeNumWin(12,5,50,25);
	this->WinInit();
	this->index = 0;
	this->currentUser = NULL;
	this->userManager = UserManager::GetOusermanager();
}

WindowManager::~WindowManager()
{
	delete this->initwin;
    delete this->registerwin;
    delete this->loginwin;
    delete this->adminwin;
    delete this->doctorwin;
    delete this->patientwin;
    delete this->userinquirywin;
    delete this->doctorinquirywin;
    delete this->adddoctorwin;
    delete this->departmentinquirywin;
    delete this->patientperwin;
    delete this->patientupdatewin;
    delete this->patientresetpasswordwin;
    delete this->appointmentmanagewin;
    delete this->appointmentwin;
    delete this->takenumwin;
    UserManager::DestroyOusermanager();
}

WindowManager* WindowManager::GetInstance() 
{
    if (instance == NULL) {
        instance = new WindowManager();
    }
    return instance;
}

void WindowManager::DestroyInstance() 
{
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void WindowManager::dataInit()
{
	
}

UserManager* WindowManager::GetUserManager()
{
    return this->userManager;
}

void WindowManager::SetCurrentUser(BaseUser* user)
{
    this->currentUser = user;
}

BaseUser* WindowManager::GetCurrentUser()
{
    return this->currentUser;
}

void WindowManager::UpdateCurrentUser(BaseUser* user)
{
    this->currentUser = user;
}

void WindowManager::ClearCurrentUser()
{
    this->currentUser = NULL;
}

void WindowManager::WinInit()
{
	this->winArr[0] = this->initwin;
	this->winArr[1] = this->registerwin;
	this->winArr[2] = this->loginwin; 
	this->winArr[3] = this->adminwin;
	this->winArr[4] = this->doctorwin;
	this->winArr[5] = this->patientwin;
	this->winArr[6] = this->userinquirywin;
	this->winArr[7] = this->doctorinquirywin;
	this->winArr[8] = this->adddoctorwin;
	this->winArr[9] = this->departmentinquirywin;
	this->winArr[10] = this->patientperwin;
	this->winArr[11] = this->patientupdatewin;
	this->winArr[12] = this->patientresetpasswordwin;
	this->winArr[13] = this->appointmentmanagewin;
	this->winArr[14] = this->appointmentwin;
	this->winArr[15] = this->takenumwin;
}

void WindowManager::toShow()
{
	while(true)
	{
		system("cls");
		Window * currentWin = this->winArr[this->index];
		currentWin->SetCurrentUser(GetCurrentUser());
		currentWin->paintWindow();
		currentWin->winRun();
		this->index = currentWin->doAction();
	}
}
