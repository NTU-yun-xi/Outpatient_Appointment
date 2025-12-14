#ifndef EDIT_H
#define EDIT_H

#include "Tool.h"
#include "Ctrl.h"

class Edit:public Ctrl
{
public:
	Edit();
    Edit(int type,int startx, int starty, int width, int height, char* context,int maxLength, int ips, int inputType);
    ~Edit();

	int getMaxLength();
    int getIps();
    int getInputType();
    
    void setMaxLength(int maxLength);
    void setIps(int ips);
    void setInputType(int inputType);

    void showCtrl();
    void inputControl(int key);
    
private:
	int maxLength;
    int ips;//0-明文，1-密文 
    int inputType;//1-数字，2-字母，3-混合，4-中文 
    unsigned char HighByte;  // 缓存GBK高字节
    bool hasWaitingHighByte;    // 标记是否有待处理的高字节
};

#endif

