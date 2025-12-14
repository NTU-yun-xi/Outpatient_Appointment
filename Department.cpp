#include "Department.h"

Department::Department()
{
	this->depID = "";
	this->depName = "";
	this->depContext = "";
	this->depDoctors = new map<string , Doctor*>();
}

Department::Department(string depID,string depName)
{
	this->depID = depID;
	this->depName = depName;
	this->depContext = "нч";
	this->depDoctors = new map<string , Doctor*>();
}

Department::~Department()
{
	if (this->depDoctors != NULL)
	{
		this->depDoctors->clear();
		delete this->depDoctors;
		this->depDoctors = NULL;
	}
}
	
string Department::GetDepID()
{
	return this->depID;
}

string Department::GetDepName()
{
	return this->depName;
}

string Department::GetDepContext()
{
	return this->depContext;
} 

map<string,Doctor*>* Department::GetDepDoctors()
{
	return this->depDoctors;
}

void Department::SetDepID(string depID)
{
	this->depID = depID;
}

void Department::SetDepName(string depName)
{
	this->depName = depName;
}

void Department::SetDepContext(string depContext)
{
	this->depContext = depContext;
} 

void Department::AddDoctor(Doctor* doctor)
{
	if(doctor == NULL)  return;
	string account = doctor->GetAccount();
	this->depDoctors->insert(make_pair(account,doctor));	
}

void Department::RemoveDoctor(string doctorAccount)
{
	this->depDoctors->erase(doctorAccount);
}

void Department::updateFrom(Department* other)
{
	if(other == NULL) return;
	this->SetDepID(other->GetDepID());
	this->SetDepName(other->GetDepName());
	this->SetDepContext(other->GetDepContext());
	this->depDoctors->clear();
	map<string ,Doctor*>* otherDoctors = other->GetDepDoctors();
	map<string ,Doctor*>::iterator iter = otherDoctors->begin();
	for(iter;iter != otherDoctors->end();++iter)
	{
		this->AddDoctor(iter->second);
	}
}

void Department::SaveToFile(ofstream& file)
{
	file << this->depID << " " 
		 << this->depName << " "
		 << this->depContext;
	map<string ,Doctor*>::iterator iter = this->depDoctors->begin();
	for(iter; iter != this->depDoctors->end(); ++iter)
	{
		file << " " << iter->first; 
	}
	file << endl;
}
