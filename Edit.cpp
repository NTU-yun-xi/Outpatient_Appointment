#include "Edit.h"

Edit::Edit():Ctrl()
{
	this->maxLength = 0;
	this->ips = 0;
	this->inputType = 0;
	this->HighByte = 0;
    this->hasWaitingHighByte = false;
}

Edit::Edit(int type,int startx, int starty, int width, int height, char* context,
		int maxLength, int ips, int inputType)
:Ctrl( type, startx, starty, width, height, context)
{
	this->maxLength = maxLength;
	this->ips = ips;
	this->inputType = inputType;
}

Edit::~Edit()
{
	
}

int Edit::getMaxLength()
{
	return this->maxLength;
}
int Edit::getIps()
{
	return this->ips;
}
int Edit::getInputType()
{
	return this->inputType;
}

void Edit::setMaxLength(int maxLength)
{
	this->maxLength = maxLength;
}
void Edit::setIps(int ips)
{
	this->ips = ips;
}
void Edit::setInputType(int inputType)
{
	this->inputType = inputType;
}

//-------------------Show---------------------------------------
void Edit::showCtrl()
{
	Tool::gotoxy(this->startx, this->starty);
	Tool::paintBoder(this->startx, this->starty, this->width, this->height);
	Tool::gotoxy(this->startx + 2, this->starty + 1);
	if (this->ips == 1) {
        for (size_t i = 0; i < this->context.size(); ++i) {
            cout << '*';
        }
    } else {
        cout << this->context;
    }
}

void Edit::inputControl(int key)
{
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT) 
	{
        return;
    }
	int count = this->context.size();
	bool isBackspace = (key == '\b');
	if(isBackspace)
	{
		if(count > 0)
        {
            unsigned char last = static_cast<unsigned char>(this->context[count - 1]);
            if(last >= 0x81 && last <= 0xFE && count >= 2)
            {
                this->context.erase(count-2,2);
                cout<<"\b\b  \b\b";
            }else
            {
                this->context.erase(count-1,1);
                cout<<"\b \b";
            }
        }
        return ;
	} 
	
	if(count >= this->maxLength)
	{
		return ;
	}
	
	unsigned char c = static_cast<unsigned char>(key);
	bool isGBKHigh = (c >= 0x81 && c <= 0xFE);
    bool isGBKLow = (c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFE);
    
    bool allowInput = false;	//允许输入
	if (this->inputType == 1) // 数字
    {
        allowInput = (key >= '0' && key <= '9');
    }
    else if (this->inputType == 2) // 字母
    {
        allowInput = ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'));
    }
    else if (this->inputType == 3) // 数字字母
    {
        allowInput = ((key >= '0' && key <= '9') || 
                     (key >= 'a' && key <= 'z') || 
					 (key >= 'A' && key <= 'Z'));
    }
    else if (this->inputType == 4 && this->ips == 0) // 中文(GBK)：仅非密码模式允许
    {
        allowInput = (isGBKHigh || isGBKLow || (key >= '0' && key <= '9') || 
                     (key >= 'a' && key <= 'z') || 
					 (key >= 'A' && key <= 'Z'));
    }	//处理是否允许输入 
	
	if(!allowInput)
	{
		return ;
	}
	
	//存入context 
	if (this->ips == 0) // 非密码模式
    {
    	// 判断是否是GBK高字节（0x81-0xFE）
        bool isGBKHigh = (key >= 0x81 && key <= 0xFE);
        // 判断是否是GBK低字节（0x40-0x7E 或 0x80-0xFE）
        bool isGBKLow = (key >= 0x40 && key <= 0x7E) || (key >= 0x80 && key <= 0xFE);
        if (this->hasWaitingHighByte) {
            // 已有待处理高字节，当前是低字节，拼接后回显完整中文
            if (isGBKLow) {
                // 拼接双字节字符
                this->context += static_cast<char>(this->HighByte);
                this->context += static_cast<char>(key);
                // 立即回显完整中文字符
                cout << static_cast<char>(this->HighByte) << static_cast<char>(key);
                // 重置高字节缓存
                this->hasWaitingHighByte = false;
                this->HighByte = 0;
            } else {
                // 低字节无效，放弃高字节，按单字节处理
                this->context += static_cast<char>(key);
                cout << static_cast<char>(key);
                this->hasWaitingHighByte = false;
                this->HighByte = 0;
            }
        } else if (isGBKHigh) {
            // 收到高字节，缓存并标记，等待低字节
            this->HighByte = key;
            this->hasWaitingHighByte = true;
            // 此处不输出任何字符，等待低字节后一次性输出
        } else {
            // 单字节（英文/数字），直接回显
            this->context += static_cast<char>(key);
            cout << static_cast<char>(key);
        }
    } else {
        // 密码模式：隐藏回显
        this->context += static_cast<char>(key);
        cout << '*';
    }
} 
