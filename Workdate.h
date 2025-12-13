#ifndef WORKDATE_H
#define WORKDATE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
using namespace std;

class Workdate
{
public:
	Workdate();
	~Workdate();
	
	void SaveToFile(ofstream& file);
	vector<string> GetSevenDays();
private:
	vector<string> sevenDays;
	
};

#endif
