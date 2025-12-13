#include "Doctor.h"

Doctor::Doctor()
:BaseUser()
{

}

Doctor::Doctor(string account, string password, int role, string username,string position,
				 string department, string hospital, string context)
: BaseUser(account, password, role, username)
{
	this->position = position;
	this->department = department;
	this->hospital = hospital;
	this->context = context;
	this->iflogin = false;
}

Doctor::~Doctor()
{

}

string Doctor::GetPosition()
{
	return position;
}
string Doctor::GetDepartment()
{
	return department;
}
string Doctor::GetHospital()
{
	return hospital;
}
string Doctor::GetContext()
{
	return context;
}

void Doctor::SetPosition(string position)
{
	this->position = position;
}
void Doctor::SetDepartment(string department)
{
	this->department = department;
}
void Doctor::SetHospital(string hospital)
{
	this->hospital = hospital;
}
void Doctor::SetContext(string context)
{
	this->context = context;
}
void Doctor::updateFrom(BaseUser* other)
{
	//确认用户角色为医生 
    if (other->GetRole() != 2)
	{
		return;
	} 
    //拷贝用户数据 
    this->SetPassword(other->GetPassword());
    this->SetName(other->GetName());
    this->SetIfLogin(other->GetIfLogin());
	//静态转化数据类型 
    Doctor* otherDoctor = static_cast<Doctor*>(other); 
    //初始化医生信息 
	this->SetPosition(otherDoctor->GetPosition());
    this->SetDepartment(otherDoctor->GetDepartment());
    this->SetHospital(otherDoctor->GetHospital());
    this->SetContext(otherDoctor->GetContext());
}

void Doctor::SaveToFile(ofstream& file)
{
    file << this->GetAccount() << " "
         << this->GetPassword() << " "
         << this->GetRole() << " "
         << (this->GetName().empty() ? "*" : this->GetName()) << " "	//空则置 * ，非空写入 
         << this->GetIfLogin() << " "
         << (this->GetPosition().empty() ? "*" : this->GetPosition()) << " "	//空则置 * ，非空写入
         << (this->GetDepartment().empty() ? "*" : this->GetDepartment()) << " "	//空则置 * ，非空写入
         << (this->GetHospital().empty() ? "*" : this->GetHospital()) << " "	//空则置 * ，非空写入
         << (this->GetContext().empty() ? "*" : this->GetContext()) << endl;	//空则置 * ，非空写入
}
