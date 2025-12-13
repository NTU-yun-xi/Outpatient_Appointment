#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin:public BaseUser
{
public:
	Admin();
	Admin(string account,string password,int role,string username);
	~Admin();
	//更新用户数据及文件 
	void updateFrom(BaseUser* other);
	void SaveToFile(ofstream& file);
//相较于父类BaseUser无数据变化 
};


#endif 
