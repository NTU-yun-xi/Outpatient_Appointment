#ifndef CTRL_H
#define CTRL_H

#include <string>
#include <iostream>

#define LABEL 1
#define BUTTON 2
#define EDIT 3 
#define TABLE 4
#define COMBOBOX 5

using namespace std;

class Ctrl
{
public:
	Ctrl();
    Ctrl(int type,int startx, int starty, int width, int height, string context);
    virtual ~Ctrl();
    //--------Geter----------------------------
    int GetType();
	int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();
    string GetContext();
    //--------Seter----------------------------
    void SetType(int type);
	void SetX(int startx);
    void SetY(int starty);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetContext(string context);
    //--------´¿Ðéshow---------------------------
	virtual void showCtrl()=0;

protected:
	int type;
	int startx;
    int starty;
    int width;
    int height;
    string context;  
};

#endif

