#include "User.h"

BaseUser::BaseUser()
{
	this->account = "";
	this->password = "";
	this->role = 0;
	this->username = "";
	this->iflogin = false;
}
BaseUser::BaseUser(string account,string password,int role,string username)
{
	this->account = account;
	this->password = password;
	this->role = role;
	this->username = username;
	this->iflogin = false;
}
BaseUser::BaseUser(string account,string password,int role)
{
	this->account = account;
	this->password = password;
	this->role = role;
	this->username = "";
	this->iflogin = false;
}
BaseUser::~BaseUser()
{
	
}
	
string BaseUser::GetAccount()
{
	return this->account;
}
string BaseUser::GetPassword()
{
	return this->password;
}
int BaseUser::GetRole()
{
	return this->role;
}
string BaseUser::GetName()
{
	return this->username;
}
bool BaseUser::GetIfLogin()
{
	return this->iflogin;
}

void BaseUser::SetAccount(string account)
{
	this->account = account;
}
void BaseUser::SetPassword(string password)
{
	this->password = password;
}
void BaseUser::SetRole(int role)
{
	this->role = role;
}
void BaseUser::SetName(string username)
{
	this->username = username;
}
void BaseUser::SetIfLogin(bool iflogin)
{
	this->iflogin = iflogin;
}

