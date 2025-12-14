#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <map>
#include <vector>
#include <fstream>
#include <string>
#include "User.h"
#include "Admin.h"
#include "Doctor.h"
#include "Patient.h"
using namespace std;

class UserManager {
public:
	//静态获取单例实例 （初始化时执行loadAllUsers） 
	static UserManager* GetOusermanager(); 
	//静态销毁单例 
	static void DestroyOusermanager();
	//新增用户并更新文件（内含saveAllUsers） 
    bool addUser(BaseUser* user);
	//注销用户 并更新文件（内含saveAllUsers） 
    bool deleteUser(string account);
	//精确查询 
    BaseUser* findUser(string account);
    //模糊查询
	vector<BaseUser*> fuzzyByAccount(string keyword); 
	//更新用户数据并更新文件（内含saveAllUsers，修改用户信息时调用） 
    bool updateUser(BaseUser* updatedUser);
	//获取全部用户信息 
    vector<BaseUser*> getAllUsers();
    //获取全部医生信息 
    vector<Doctor*> getAllDoctors();
    //从文件加载所有用户信息（读文件） 
	void loadAllUsers();
	//将所有信息写入文件（写文件） 
    void saveAllUsers();
	//清空用户数据 
    void clearAllUsers();
    
    string getTempstring(); 
    
    void setTempstring(string tempstr);

private:
	//单例不允许带参、拷贝构造 
	UserManager(const UserManager&);
    UserManager& operator=(const UserManager&);
	//以账号为键存储全部用户，便于精确查询 
    map<string,BaseUser*> users;
	string tempstr;
	static UserManager* Ousermanager;//静态单例实例 
	
	//私有构造、析构 
	UserManager(); 

    ~UserManager();
};

#endif 
