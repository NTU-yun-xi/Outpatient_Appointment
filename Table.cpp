#include "Table.h"

Table::Table():Ctrl()
{
	this->cols = 0;
	this->rows = 0;
	this->colWidth = 0;
	this->rowHeight = 0;
}

Table::Table(int type,int startx, int starty, int width, int height, char* context,
		 int cols, int rows, int colWidth, int rowHeight)
:Ctrl(type, startx, starty, 0, 0, "")
{
	this->cols = cols;
	this->rows = rows;
	this->colWidth = colWidth;
	this->rowHeight = rowHeight;
}

Table::~Table()
{
	
}

//--------Geter-----------------------------------------------
int Table::GetCols()
{
	return this->cols;
}
int Table::GetRows()
{
	return this->rows;
}
int Table::GetColWidth()
{
	return this->colWidth;
}
int Table::GetRowHeight()
{
	return this->rowHeight;
}
//--------Seter-----------------------------------------------
void Table::SetCols(int cols)
{
	this->cols = cols;
}
void Table::SetRows(int rows)
{
	this->rows = rows;
}
void Table::SetColWidth(int colWidth)
{
	this->colWidth = colWidth;
}
void Table::SetRowHeight(int rowHeight)
{
	this->rowHeight = rowHeight;
}
//-------------------Show---------------------------------------
void Table::showCtrl()
{
	int i, j, k, l;
	int currentY; 

	for (i = 1; i <= this->rows; i++)
	{
		currentY = this->starty + (i - 1) * (this->rowHeight + 1); 

		Tool::gotoxy(this->startx, currentY);
		for (j = 1; j <= this->cols; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					printf("©°"); 
				}
				else
				{
					printf("©Ð"); 
				}
			}
			else
			{
				if (j == 1)
				{
					printf("©À"); 
				}
				else
				{
					printf("©à"); 
				}
			}

			for (k = 1; k <= this->colWidth; k++)
			{
				printf("©¤©¤");
			}
		}
	
		if (i == 1)
		{
			printf("©´"); 
		}
		else
		{
			printf("©È"); 
		}
		currentY++; 

		for (l = 1; l <= this->rowHeight; l++)
		{
			Tool::gotoxy(this->startx, currentY);
			for (j = 1; j <= this->cols; j++)
			{
				printf("©¦"); 
				for (k = 1; k <= this->colWidth; k++)
				{
					printf("  "); 
				}
			}
			printf("©¦"); 
			currentY++; 
		}
	}

	Tool::gotoxy(this->startx, currentY);
	for (j = 1; j <= this->cols; j++)
	{
		if (j == 1)
		{
			printf("©¸"); 
		}
		else
		{
			printf("©Ø"); 
		}
		for (k = 1; k <= this->colWidth; k++)
		{
			printf("©¤©¤");
		}
	}
	printf("©¼"); 
}

