#ifndef BUTTON_H
#define BUTTON_H

#include <cstring>
#include "Tool.h"
#include "Ctrl.h"

class Button:public Ctrl
{
public:
	Button();
    Button(int type,int startx, int starty, int width, int height, char* context);
    ~Button();

    void showCtrl();
    //设置聚焦状态（用于仅光标跳转时） 
    void setFocused(bool focused);
	//获取、设置显示模式 
	int getShowMode();
	void setShowMode(int showmode);
	
private:
	int showmode;//0-一般按钮，1-表格行按钮 
    bool isFocused;
};

#endif
