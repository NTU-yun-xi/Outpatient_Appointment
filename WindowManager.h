#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "InitWin.h"
#include "RegisterWin.h"
#include "LoginWin.h"
#include "AdminWin.h"
#include "DoctorWin.h"
#include "PatientWin.h" 
#include "UserInquiryWin.h"
#include "DoctorInquiryWin.h" 
#include "AddDoctorWin.h"
#include "DepartmentInquiryWin.h"
#include "PatientPerWin.h"
#include "PatientUpdateWin.h"
#include "PatientResetPasswordWin.h"
#include "AppointmentManageWin.h"
#include "AppointmentWin.h"
#include "TakeNumWin.h"
#include "UserManager.h"

#include <stdlib.h>
#include <map>
#include <vector>
#include <map>
#include <list>
using namespace std;

class WindowManager
{
public:
	static WindowManager* GetInstance();
	static void DestroyInstance();
	
	void WinInit();
	void toShow();
	
	void dataInit();
	
	void SetCurrentUser(BaseUser* user);
    BaseUser* GetCurrentUser();
    void UpdateCurrentUser(BaseUser* user);
    void ClearCurrentUser();
    
    UserManager* GetUserManager();

private:
	WindowManager();
	~WindowManager();
	
	WindowManager(const WindowManager&);
    WindowManager& operator=(const WindowManager&);
	
	static WindowManager* instance;
	
	Window * initwin;
	Window * registerwin;
	Window * loginwin;
	Window * adminwin;
	Window * doctorwin;
	Window * patientwin;
	Window * userinquirywin;
	Window * doctorinquirywin; 
	Window * adddoctorwin;
	Window * departmentinquirywin; 
	Window * patientperwin;
	Window * patientupdatewin;
	Window * patientresetpasswordwin;
	Window * appointmentmanagewin;
	Window * appointmentwin;
	Window * takenumwin;
	Window * winArr[20];
	int index;
	
	BaseUser* currentUser;
	UserManager* userManager;
};

#endif
