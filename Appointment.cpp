#include "Appointment.h"

Appointment::Appointment()
{
	this->day = 0;
	this->time = 0; 
	this->doctorId = "";
	this->patientId = "";
	this->desc = "";
	this->visitDesc = "*";
	this->state = 0; 
}

Appointment::Appointment(int day, int time, string doctorId, string patientId, string desc,string visitDesc,int state)
{
	this->day = day;
	this->time = time;
	this->doctorId = doctorId;
	this->patientId = patientId;
	this->desc = desc;
	this->visitDesc = visitDesc;
	this->state = state;
}

Appointment::~Appointment()
{
	
}

int Appointment::getDay()
{
	return this->day;
}

int Appointment::getTime()
{
	return this->time;
}

string Appointment::getDoctorId()
{
	return this->doctorId;
}

string Appointment::getPatientId()
{
	return this->patientId; 
}

string Appointment::getDesc()
{
	return this->desc;
}

string Appointment::getVisitDesc()
{
	return this->visitDesc;
}

int Appointment::getState()
{
	return this->state;
}

void Appointment::setDay(int day)
{
	this->day = day;
}

void Appointment::setTime(int time)
{
	this->time = time;
}

void Appointment::setDoctorId(string doctorId)
{
	this->doctorId = doctorId;
}

void Appointment::setPatientId(string patientId)
{
	this->patientId = patientId;
}

void Appointment::setDesc(string desc)
{
	this->desc = desc;
}

void Appointment::setVisitDesc(string visitDesc)
{
	this->visitDesc = visitDesc;
}

void Appointment::setState(int state)
{
	this->state = state;
}
