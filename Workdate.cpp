#include "Workdate.h"

Workdate::Workdate()
{
	time_t now = time(NULL);
    tm localTime = *localtime(&now);
    for(int i = 0; i < 7; i++)
    {
        tm tempTm = localTime;
        tempTm.tm_mday += i+1;
        mktime(&tempTm);
        char buf[20];
        // 格式化为"XXXX-XX-XX"
        sprintf(buf, "%04d-%02d-%02d", 
                tempTm.tm_year + 1900, 
                tempTm.tm_mon + 1, 
                tempTm.tm_mday);
        this->sevenDays.push_back(string(buf));
    }
}

Workdate::~Workdate()
{
	
}

void Workdate::SaveToFile(ofstream& file)
{
    if (!file.is_open()) 
	{
        cerr << "文件未打开，无法写入！" << endl;
        return;
    }
    int index = 1;
    vector<string>::iterator iter;
    for (iter = sevenDays.begin(); iter != sevenDays.end(); ++iter) 
	{
        file << index << " " << *iter << endl;
        index++;
    }
}

vector<string> Workdate::GetSevenDays()
{
    return this->sevenDays;  
}
