#ifndef APPOINTMENTMANAGER_H
#define APPOINTMENTMANAGER_H

#include "Appointment.h"
#include "DepartmentManager.h"
#include "Doctor.h"
#include <iostream>
#include <vector>
#include <string>
#include <map> 
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <windows.h>
#include <tchar.h>
using namespace std;

class AppointmentManager
{
public:
	static AppointmentManager* getInstance();
    bool isTimeSlotFull(string doctorId, int day, string slot);  
    bool saveAppointment(Appointment app);
    void saveAppointments(const string& doctorId, const vector<Appointment*>& apps); 
    vector<Appointment> loadAppointments(string doctorId);
    int getSlotAppointmentCount(string doctorId, int day, string timeSlot);  
    vector<int> getTimeIdsForSlot(string timeSlot);
    void loadTimeSlots();
    vector<Appointment*> getallAppointments();
	
private:
	AppointmentManager();
	static AppointmentManager* instance;
	string getDoctorFilePath(string doctorId); 
    map<string, vector<int> > timeSlotMap;
    map<int, string> timeIdToSlotMap;
    bool checkPatientAppointmented(string patientId, int day);
};


#endif
