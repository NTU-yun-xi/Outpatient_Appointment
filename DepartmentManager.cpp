#include "DepartmentManager.h"

DepartmentManager* DepartmentManager::instance = NULL;

DepartmentManager::DepartmentManager() 
{
    this->userManager = UserManager::GetOusermanager();
    this->loadAllDepartments();
}

DepartmentManager::~DepartmentManager() 
{
    map<string, Department*>::iterator iter = departments.begin();
    for (; iter != departments.end(); ++iter) 
	{
        delete iter->second;
    }
    departments.clear();
}

DepartmentManager* DepartmentManager::GetInstance() 
{
    if (instance == NULL) 
	{
        instance = new DepartmentManager();
    }
    return instance;
}

void DepartmentManager::DestroyInstance() 
{
    if (instance != NULL) 
	{
        delete instance;
        instance = NULL;
    }
}

bool DepartmentManager::addDepartment(Department* department) 
{
    if (department == NULL) return false;
    string depID = department->GetDepID();
    map<string, Department*>::iterator iter = departments.find(depID);
    if (iter != departments.end()) 
	{
        return false;
    }
    departments.insert(std::make_pair(depID, department));
    saveAllDepartments();
    return true;
}

bool DepartmentManager::deleteDepartment(string depID) 
{
    map<string, Department*>::iterator iter = departments.find(depID);
    if (iter == departments.end()) 
	{
        return false;
    }
    delete iter->second;
    departments.erase(iter);
    saveAllDepartments();
    return true;
}

Department* DepartmentManager::findDepartment(string depID) 
{ 
    map<string, Department*>::iterator iter = departments.find(depID);
    return (iter != departments.end()) ? iter->second : NULL;
}

vector<Department*> DepartmentManager::fuzzyFindByDepID(string keyword) 
{
    vector<Department*> res;
    map<string, Department*>::iterator iter = departments.begin();
    for (; iter != departments.end(); ++iter) 
	{
        if (iter->second->GetDepID().find(keyword) != string::npos) 
		{
            res.push_back(iter->second);
        }
    }
    return res;
}

bool DepartmentManager::updateDepartment(Department* updatedDep) 
{
    if (updatedDep == NULL) return false;
    string depID = updatedDep->GetDepID();
    map<string, Department*>::iterator iter = departments.find(depID);
    if (iter == departments.end()) 
	{
        return false;
    }
    iter->second->updateFrom(updatedDep);
    saveAllDepartments();
    return true;
}

vector<Department*> DepartmentManager::getAllDepartments() 
{
    vector<Department*> res;
    map<string, Department*>::iterator iter = departments.begin();
    for (; iter != departments.end(); ++iter) 
	{
        res.push_back(iter->second);
    }
    return res;
}

void DepartmentManager::loadAllDepartments() 
{
    ifstream file("./data/Department/departments.txt");
    if (!file.is_open()) 
    {
        std::cout << "无法打开文件departments.txt进行读取" << std::endl;
        return;
    }

    // 清空现有数据
    map<string, Department*>::iterator iter = departments.begin();
    for (; iter != departments.end(); ++iter) 
    {
        delete iter->second;
    }
    departments.clear();

    string line;
    // 按行读取每个科室的数据
    while (getline(file, line)) 
    {
        if (line.empty()) continue; // 跳过空行

        istringstream iss(line); // 用字符串流解析当前行
        string depID, depName, depContext, doctorAccount;

        // 读取科室基本信息（ID、名称、描述）
        if (!(iss >> depID >> depName >> depContext)) 
        {
            continue; // 数据格式错误，跳过此行
        }

        Department* dep = new Department(depID, depName);
        dep->SetDepContext(depContext);

        // 读取当前科室下的所有医生账号
        while (iss >> doctorAccount) 
        {
            BaseUser* user = userManager->findUser(doctorAccount);
            if (user != NULL && user->GetRole() == 2) 
            {
                Doctor* doctor = static_cast<Doctor*>(user);
                dep->AddDoctor(doctor);
            }
        }

        departments.insert(std::make_pair(depID, dep));
    }
    file.close();
}

void DepartmentManager::saveAllDepartments() {
    ofstream file("./data/Department/departments.txt", std::ios::out);
    if (!file.is_open()) 
	{
        std::cout << "无法打开科室文件departments.txt进行写入" << std::endl;
        return;
    }

    map<string, Department*>::iterator iter = departments.begin();
    for (; iter != departments.end(); ++iter) 
	{
        iter->second->SaveToFile(file);
    }
    file.close();
}

