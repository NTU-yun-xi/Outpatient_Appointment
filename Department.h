#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Department
{
public:
	Department();
	Department(string depID,string depName);
	~Department();
	
	string GetDepID();
	string GetDepName();
	string GetDepContext();
	map<string,Doctor*>* GetDepDoctors();
	
	void SetDepID(string depID);
	void SetDepName(string depName);
	void SetDepContext(string depContext);
	void AddDoctor(Doctor* doctor);
	void RemoveDoctor(string doctorAccount);
	
	void updateFrom(Department* other);
    void SaveToFile(ofstream& file);
	
private:
	string depID;
	string depName;
	string depContext;
	map<string,Doctor*>* depDoctors;
};

#endif 
