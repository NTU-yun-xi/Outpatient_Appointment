#ifndef COMOBOBOXWIN_H
#define COMOBOBOXWIN_H

#include "Window.h"
#include "Button.h"
#include "Ctrl.h"
#include <string>
#include <vector>
using namespace std;

class ComoboBoxWin:public Window
{
public:
	ComoboBoxWin();
	ComoboBoxWin(int win_startX,int win_startY,int win_width,int win_height);
	~ComoboBoxWin();
	
	void SetShow(bool show);	//设置是否显示 
	bool GetShow(); 	//获取显示状态 
	void SetPosition(int x,int y);
	
	void addOption(int Ox, int Oy, int Owidth, int Oheight,char* OContext);		//添加下拉框选项 
	
	void clearOptions();
	
	int doAction();		//选择下拉框 
	
	char* GetOptionContext();
	
	void paintWindow();
	
	void winRun();		//下拉框驱动 
	
private:
	vector<Button*> * options;	//存储下拉选项 
	vector<Button*>::iterator iter; 
	char* currentOptionContext;		//存储选项文本 
	bool ifShow;	//是否显示 
};


#endif
