#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"
#include <fstream>

class Patient:public BaseUser
{
public:
    Patient();
    Patient(string account, string password, int role, string username, string idCard);
    ~Patient();
    
    string GetIdCard();
    void SetIdCard(string idCard);
    //用户数据及文件更新 
    void updateFrom(BaseUser* other);
    void SaveToFile(ofstream& file);

private:
	//患者数据增加身份证，可后续修改 
    string idCard;	
};

#endif
