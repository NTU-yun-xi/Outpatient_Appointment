#ifndef TOOL_H
#define TOOL_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
using namespace std;

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Tool
{
public:
	static void gotoxy(int x,int y);
	static void paintBoder(int startX,int startY,int width,int height);
	static int getkey();
	static string intToString(int num);
};

#endif
