#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"

class Doctor:public BaseUser
{
public:
	Doctor();
	Doctor(string account,string password,int role,string username,
			string position,string department,string hospital,string context);
	~Doctor();
	
	string GetPosition();
	string GetDepartment();
	string GetHospital();
	string GetContext();
	
	void SetPosition(string position);
	void SetDepartment(string department);
	void SetHospital(string hospital);
	void SetContext(string context);
	//用户信息数据及文件更新 
	void updateFrom(BaseUser* other);
	void SaveToFile(ofstream& file);

	
private:
	//医生用户信息比父类新增职位、科室、医院、简历  统一由管理员修改 
	string position;	//职位 
	string department;	//科室 
	string hospital;	//医院 
	string context;		//简介 
};


#endif
