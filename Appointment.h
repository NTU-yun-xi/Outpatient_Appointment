#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
using namespace std;

class Appointment
{
public:
	Appointment();
	Appointment(int day, int time, string doctorId, string patientId, string desc);
	~Appointment();
	
	int getDay();
	int getTime();
	string getDoctorId();
	string getPatientId();
	string getDesc();
	string getVisitDesc();
	int getState();
	
	void setDay(int day);
    void setTime(int time);
    void setDoctorId(string doctorId);
    void setPatientId(string patientId);
    void setDesc(string desc);
    void setVisitDesc(string visitDesc);
    void setState(int state);
    
private:
	int day;           // 1-7（对应7天）
    int time;          // 1-12（对应12个时段）
    string doctorId;   // 医生ID
    string patientId;  // 患者账号（电话号码）
    string desc;       // 患者预约描述
    string visitDesc;  // 就诊描述
    int state; 		   // 就诊状态 0-未就诊 1-等待就诊 2-已取消 3-已就诊 
};

#endif
