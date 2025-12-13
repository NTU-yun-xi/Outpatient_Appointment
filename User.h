#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class BaseUser
{
public:
	BaseUser();
	BaseUser(string account,string password,int role,string username);//有姓名 初始化（新增医生） 
	BaseUser(string account,string password,int role);//无姓名 初始化  （新增用户） 
	~BaseUser();
	
	string GetAccount();
	string GetPassword();
	int GetRole();
	string GetName();
	bool GetIfLogin();
	
	void SetAccount(string account);
	void SetPassword(string password);
	void SetRole(int role);
	void SetName(string username);
	void SetIfLogin(bool iflogin);
	
	//更新数据及文件   纯虚   子类不同实现逻辑 
	virtual void updateFrom(BaseUser* other) = 0;
	virtual void SaveToFile(ofstream& file) = 0;

protected:
	//User父类基础数据account，password，role，name，iflogin 
	string account;		//账号 
	string password;	//密码 
	int role;			//角色 
	string username;	//姓名 
	bool iflogin;		//登录状态 
};


#endif 
