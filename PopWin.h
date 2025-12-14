#ifndef POPWIN_H
#define POPWIN_H

#include "Window.h"
#include "ComoboBoxWin.h"
#include <vector>
using namespace std;

class PopWin:public Window
{
public:
	PopWin();
	PopWin(int win_startX,int win_startY,int win_width,int win_height);
	~PopWin();
	
	void paintWindow();
	int doAction();
	void winRun();
	void addControl(Ctrl* con);
	void addComboBox(ComoboBoxWin* combo);
	void setTitle(char* title);
	int getResult();
	vector<Ctrl*>* getCtrls();
	vector<ComoboBoxWin*>* getComboBoxes();
private:
	vector<Ctrl*>* ctrls;
	vector<ComoboBoxWin*>* comboBoxes;
	char* title;
	int result;
	vector<Ctrl*>::iterator iter1;
	vector<ComoboBoxWin*>::iterator iter2;
	bool isCompleted;
	int currentIndex;
	bool isComboOpen;
};




#endif
