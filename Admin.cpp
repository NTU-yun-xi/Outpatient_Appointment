#include "Admin.h"

Admin::Admin()
:BaseUser()
{
	
}

Admin::Admin(string account,string password,int role,string username)
:BaseUser(account,password,role,username)
{
	this->iflogin = false;
}

Admin::~Admin()
{
	
}

void Admin::updateFrom(BaseUser* other)
{
	//确认用户角色为管理员 
    if (other->GetRole() != 1)
    {
    	return;	
	}
	//拷贝用户数据 
    this->SetPassword(other->GetPassword());
    this->SetName(other->GetName());
    this->SetIfLogin(other->GetIfLogin());
}

void Admin::SaveToFile(ofstream& file)
{
    file << this->GetAccount() << " "
         << this->GetPassword() << " "
         << this->GetRole() << " "
         << (this->GetName().empty() ? "*" : this->GetName()) << " "	//用户姓名是否为空，空则置 * 非空则写入 
         << this->GetIfLogin() << endl;
}
