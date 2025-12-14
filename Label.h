#ifndef LABEL_H
#define LABEL_H

#include "Tool.h"
#include "Ctrl.h"

class Label:public Ctrl
{
public:
	Label();
    Label(int type,int startx, int starty, int width, int height, char* context);
    ~Label();

    void showCtrl();
     
};

#endif
