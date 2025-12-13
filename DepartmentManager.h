#ifndef DEPARTMENTMANAGER_H
#define DEPARTMENTMANAGER_H

#include "Department.h"
#include "UserManager.h"
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class DepartmentManager
{
public:
	static DepartmentManager* GetInstance();
    static void DestroyInstance();

    bool addDepartment(Department* department);
    bool deleteDepartment(string depID);
    Department* findDepartment(string depID);
    vector<Department*> fuzzyFindByDepID(string keyword);
    bool updateDepartment(Department* updatedDep);
    vector<Department*> getAllDepartments();

    void loadAllDepartments();
    void saveAllDepartments();
    
private:
	DepartmentManager();
    ~DepartmentManager();
    DepartmentManager(const DepartmentManager&);
    DepartmentManager& operator=(const DepartmentManager&);

    static DepartmentManager* instance;
    map<string, Department*> departments;
    UserManager* userManager;
};

#endif
