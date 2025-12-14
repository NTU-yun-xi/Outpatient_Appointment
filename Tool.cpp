#include "Tool.h"

/*********************************
函数名称：gotoxy
函数功能：光标定位
函数参数：int x：x坐标
		  int y：y坐标
函数返回值类型：void
**********************************/ 
void Tool::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*********************************
函数名称：paintBoder
函数功能：绘制边框 
函数参数：int startX：起始x坐标
		  int startY：起始y坐标
		  int width：边框宽度
		  int length：边框高度 
函数返回值类型：void
**********************************/ 
void Tool::paintBoder(int startX,int startY,int width,int height)
{
	gotoxy(startX,startY);
    int i,j;
    for(i = 1;i <= height;i++)
	{
		if(i == 1)
		{
			for(j = 1;j <= width;j++)
			{
				if(j == 1)printf("┌");
				else if(j == width)printf("┐\n");
				else printf("──");
			}
		}
		else if(i == height)
		{
			for(j = 1;j <= width;j++)
			{
				if(j == 1)printf("└");
				else if(j == width)printf("┘\n");
				else printf("──");
			}
		}
		else
		{
			for(j = 1;j <= width;j++)
			{
				if(j == 1 || j == width)printf("│");
				else printf("  ");
			}
			printf("\n");
		}
		gotoxy(startX,startY+i);
	} 
}

int Tool::getkey()
{
	int key = getch();
	// 处理扩展键(如方向键)
    if (key == 0xE0 || key == 0)
    {
        key = getch();
        switch (key)
        {
            case 72: return KEY_UP;
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
            // 可以在这里添加其他需要处理的扩展键
            default: return key + 256; // 用高位置位标识扩展键
        }
    }
    // 处理ASCII控制键
    else if (key == 13) return KEY_ENTER;
    else if (key == 27) return KEY_ESC;
    // 中文字符高位字节(0x81-0xFE)需要保留原值用于中文处理
    else if (key >= 0x81 && key <= 0xFE) return key;
    // 其他普通字符直接返回
    else return key;
}

string Tool::intToString(int num) 
{
   char buf[20]; 
   sprintf(buf, "%d", num);
   return string(buf);
}

string Tool::keepOnlyDigits(string input) {
    string result;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (isdigit(static_cast<unsigned char>(c))) 
		{
            result.push_back(c);  
        }
    }
    return result;
}
