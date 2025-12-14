#include "Patient.h"

Patient::Patient()
: BaseUser()
{
    this->idCard = "";
}

Patient::Patient(string account, string password, int role, string username, string idCard)
: BaseUser(account, password, role, username)
{
    this->idCard = idCard;
    this->iflogin = false;
}

Patient::~Patient()
{
    
}

string Patient::GetIdCard()
{
    return idCard;
}

void Patient::SetIdCard(string idCard)
{
    this->idCard = idCard;
}

void Patient::updateFrom(BaseUser* other)
{
	//确认用户角色为患者 
    if (other->GetRole() != 3)
    {
        return;
    }
    //拷贝用户数据 
    this->SetPassword(other->GetPassword());
    this->SetName(other->GetName());
    this->SetIfLogin(other->GetIfLogin());
	//静态转换数据类型 
    Patient* otherPatient = static_cast<Patient*>(other);
    //初始化身份证信息 
	this->SetIdCard(otherPatient->GetIdCard());
}

void Patient::SaveToFile(ofstream& file)
{
    file << this->GetAccount() << " "
         << this->GetPassword() << " "
         << this->GetRole() << " "
         << (this->GetName().empty() ? "*" : this->GetName()) << " "		//用户姓名是否为空 ，空则置 * ，非空写入 
         << this->GetIfLogin() << " "
         << (this->GetIdCard().empty() ? "*" : this->GetIdCard()) << endl;	//用户身份信息是否为空，空则置 * ，非空写入 
}
