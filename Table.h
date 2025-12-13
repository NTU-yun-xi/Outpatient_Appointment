#ifndef TABLE_H
#define TABLE_H

#include "Tool.h"
#include "Ctrl.h"

class Table:public Ctrl 
{
public:
	Table();
    Table(int type,int startx, int starty, int width, int height, char* context,
		 int cols, int rows, int colWidth, int rowHeight);
    ~Table(); 
	//--------Geter----------------------------	
    int GetCols();
    int GetRows();
    int GetColWidth();
    int GetRowHeight();
    //--------Seter----------------------------
    void SetCols(int cols);
    void SetRows(int rows);
    void SetColWidth(int colWidth);
    void SetRowHeight(int rowHeight);

    void showCtrl();
    
private:
    int cols;
    int rows;
    int colWidth;
    int rowHeight;
};

#endif

