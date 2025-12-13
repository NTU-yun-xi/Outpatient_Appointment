#include "UserManager.h"

UserManager* UserManager::Ousermanager = NULL;

UserManager::UserManager()
{
    this->loadAllUsers();
}

UserManager::~UserManager()
{
	this->clearAllUsers();
}

//单例获取全局用户管理器 
UserManager* UserManager::GetOusermanager()
{
    if (Ousermanager == NULL) {
        Ousermanager = new UserManager();
    }
    return Ousermanager;
}

//销毁单例全局用户管理器 
void UserManager::DestroyOusermanager()
{
	if(Ousermanager != NULL)
	{
		delete Ousermanager;
		Ousermanager = NULL;
	}
} 

//新增用户 
bool UserManager::addUser(BaseUser* user)
{
	if (user == NULL) return false;
    string account = user->GetAccount();
     
    map<string, BaseUser*>::iterator iter = this->users.find(account);
	//查找是否存在重合账号  重合则新增失败 
    if (iter != this->users.end()) {
        return false;
    }
    //不重合则新增用户 
    this->users[account] = user;
    //写入文件 
    this->saveAllUsers();
    return true;
}

//注销用户 
bool UserManager::deleteUser(string account)
{ 
	map<string, BaseUser*>::iterator iter = this->users.find(account);
    //查找是否存在该账号  不存在则注销失败 
	if (iter == this->users.end()) {
        return false;
    }
    //存在则注销账号 
    delete iter->second;
    this->users.erase(iter);
    //写入文件 
    this->saveAllUsers();
    return true;
}

//精确查询  返回用户变量 
BaseUser* UserManager::findUser(string account) 
{  
	map<string, BaseUser*>::iterator iter = this->users.find(account);
    if (iter != this->users.end()) {
        return iter->second;
    }
    return NULL;
}

//模糊查询，返回向量数组 
vector<BaseUser*> UserManager::fuzzyByAccount(string keyword)
{
	vector<BaseUser*> res;
    map<string, BaseUser*>::iterator iter;
    for (iter = this->users.begin(); iter != this->users.end(); ++iter) {
        string account = iter->first; 
        //相较于C，C++中string::find可以高效判断是否包含关键字 
        if (account.find(keyword) != string::npos) {
            res.push_back(iter->second);
        }
    }
    return res;
}

//更新用户数据 
bool UserManager::updateUser(BaseUser* updatedUser) 
{
	if (updatedUser == NULL) return false;
	//根据账号找到需要修改的用户 
    string account = updatedUser->GetAccount();
    map<string, BaseUser*>::iterator iter = this->users.find(account);
    if (iter == this->users.end()) {
        return false;
    }
    iter->second->updateFrom(updatedUser);
    //写入文件 
	this->saveAllUsers();
    return true;
}

//获取全用户向量 
vector<BaseUser*> UserManager::getAllUsers() 
{
    vector<BaseUser*> userList;
    map<string, BaseUser*>::iterator iter;
    //依次赋值 
	for (iter = this->users.begin(); iter != this->users.end(); ++iter) {
        userList.push_back(iter->second);
    }
    return userList;
}

//获取全部医生用户
vector<Doctor*> UserManager::getAllDoctors()
{
	vector<Doctor*> doctorList;
	map<string,BaseUser*>::iterator iter;
	for(iter = this->users.begin();iter != this->users.end();++iter)
	{
		if(iter->second->GetRole() == 2)
		{
			Doctor* doc = static_cast<Doctor*>(iter->second);
			doctorList.push_back(doc);
		}else
		{
			continue;
		}
	}
	return doctorList;
} 

string UserManager::getTempstring()
{
	return this->tempstr;
}
    
void UserManager::setTempstring(string tempstr)
{
	this->tempstr = tempstr; 
}

//从文件中加载所有用户数据 
void UserManager::loadAllUsers()
{
	this->clearAllUsers(); // 清空内存旧数据，避免重复加载

    ifstream adminFile("./data/User/admins.txt");
    if (adminFile.is_open()) {
        string account, password, name, iflogin;
        // 按行读取管理员数据：账号 密码 姓名 登录状态
        while (adminFile >> account >> password >> name >> iflogin) {
            // 创建管理员对象并加入内存map
            Admin* admin = new Admin(account, password, 1, name);
            admin->SetIfLogin(iflogin == "1"); // 恢复登录状态
            this->users[account] = admin;
        }
        adminFile.close();
    } else {
        cout << "admins.txt不存在/无法打开，暂不加载管理员数据" << endl;
    }

    ifstream doctorFile("./data/User/doctors.txt");
    if (doctorFile.is_open()) {
        string account, password, name, iflogin;
        string position, department, hospital, context;
        // 按行读取医生数据：基础字段 + 职位/科室/医院/简介
        while (doctorFile >> account >> password >> name >> iflogin
                          >> position >> department >> hospital >> context) {
            // 创建医生对象并加入内存map
            Doctor* doctor = new Doctor(account, password, 2, name, position, department, hospital, context);
            doctor->SetIfLogin(iflogin == "1");
            this->users[account] = doctor;
        }
        doctorFile.close();
    } else {
        cout << "doctors.txt不存在/无法打开，暂不加载医生数据" << endl;
    }

    ifstream patientFile("./data/User/patients.txt");
    if (patientFile.is_open()) {
        string account, password, name, iflogin, idCard;
        // 按行读取病人数据：基础字段 + 身份证
        while (patientFile >> account >> password >> name >> iflogin >> idCard) {
            // 创建病人对象并加入内存map
            Patient* patient = new Patient(account, password, 3, name, idCard);
            patient->SetIfLogin(iflogin == "1");
            this->users[account] = patient;
        }
        patientFile.close();
    } else {
        cout << "patients.txt不存在/无法打开，暂不加载病人数据" << endl;
    }
}

//所有信息写入文件（写文件） 
void UserManager::saveAllUsers() 
{
	ofstream adminFile("./data/User/admins.txt", ios::out);
    ofstream doctorFile("./data/User/doctors.txt", ios::out);
    ofstream patientFile("./data/User/patients.txt", ios::out);

    if (!adminFile.is_open() || !doctorFile.is_open() || !patientFile.is_open()) {
        cout << "无法打开用户文件进行写入" << endl;
        return;
    }

    map<string, BaseUser*>::iterator iter;
    for (iter = users.begin(); iter != users.end(); ++iter) {
        BaseUser* user = iter->second;
        int role = user->GetRole();
        string account = user->GetAccount();
        string password = user->GetPassword();
        string name = user->GetName();
        string iflogin = user->GetIfLogin() ? "1" : "0";

        if (role == 1) { 
            adminFile << account << " " << password << " " << name << " " << iflogin << endl;
        } else if (role == 2) { 
            Doctor* doc = dynamic_cast<Doctor*>(user);
            if (doc) {
                adminFile.close(); 
                doctorFile << account << " " << password << " " << name << " " << iflogin
                           << " " << doc->GetPosition() << " " << doc->GetDepartment()
                           << " " << doc->GetHospital() << " " << doc->GetContext() << endl;
            }
        } else if (role == 3) { 
            Patient* pat = dynamic_cast<Patient*>(user);
            if (pat) {
                patientFile << account << " " << password << " " << name << " " << iflogin
                            << " " << pat->GetIdCard() << endl;
            }
        }
    }

    adminFile.close();
    doctorFile.close();
    patientFile.close();
}

//清空容器 
void UserManager::clearAllUsers() 
{
    map<string, BaseUser*>::iterator iter;
    for (iter = this->users.begin(); iter != this->users.end(); ++iter) {
        delete iter->second;
    }
    this->users.clear();
}
