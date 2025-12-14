#include "Window.h"

Window::Window()
{
	this->win_startX = 0;
	this->win_startY = 0;
	this->win_width = 0;
	this->win_height = 0;
	this->count = 0;
	this->flag = 0;
	memset(this->arr,0,sizeof(this->arr));
	this->currentUser = NULL;
	this->mainApp = NULL;
}
Window::Window(int win_startX,int win_startY,int win_width,int win_height)
{
	this->win_startX = win_startX;
	this->win_startY = win_startY;
	this->win_width = win_width;
	this->win_height = win_height;
	this->count = 0;
	this->flag = 0;
	memset(this->arr,0,sizeof(this->arr));
	this->currentUser = NULL;
	this->mainApp = NULL;
}
Window::~Window()
{
	
}

int Window::GetWinX()
{
	return this->win_startX;
}
int Window::GetWinY()
{
	return this->win_startY;
}
int Window::GetWinWidth()
{
	return this->win_width;
}
int Window::GetWinHeight()
{
	return this->win_height;
}
Ctrl* Window::GetConByIndex(int index)
{
	if(index >= 0 && index<this->count)
	{
		return this->arr[index];
	}
}
int Window::GetCount()
{
	return this->count;
}
int Window::GetFlag()
{
	return this->flag;
}

void Window::SetWinX(int win_startX)
{
	this->win_startX = win_startX;
}
void Window::SetWinY(int win_startY)
{
	this->win_startY = win_startY;
}
void Window::SetWinWidth(int win_width)
{
	this->win_width = win_width;
}
void Window::SetWinHeight(int win_height)
{
	this->win_height = win_height;
}

void Window::addControl(Ctrl * con)
{
	if(con != NULL)
	{
		this->arr[this->count++] = con;	
	}
}
void Window::paintWindow()
{
	Tool::paintBoder(this->win_startX,this->win_startY,this->win_width,this->win_height);
	for(int i = 0;i<this->count;i++)
	{
		this->arr[i]->showCtrl();
	}
}
void Window::winRun()
{
	int i;
	int ikey;
	for(i = 0;i<this->count;i++)
	{
		if((this->arr[i]->GetType() == EDIT)||(this->arr[i]->GetType() == BUTTON))
		{
			break;
		}
	}
    
    Button* initBtn = dynamic_cast<Button*>(this->arr[i]);
    if (initBtn)
    {
        initBtn->setFocused(true);
        initBtn->showCtrl();
    }
    
	Tool::gotoxy(this->arr[i]->GetX()+2+strlen(this->arr[i]->GetContext().c_str()),this->arr[i]->GetY()+1);
	while(1)
	{
		ikey = Tool::getkey();
		switch(ikey)
		{
			case KEY_ESC:
				this->flag = -1;
				return ;
			case KEY_ENTER:
				if(this->arr[i]->GetType() == BUTTON)
				{
					Button* currBtn = dynamic_cast<Button*>(this->arr[i]);
			        if (currBtn && currBtn->getShowMode() == 1)
			        {
			            currBtn->setFocused(false);
			            currBtn->showCtrl(); // 重新绘制按钮，此时光标会消失
			        }
					this->flag = i;
					return ;
				}
				break;
			case KEY_UP:
			{
				Button* prevBtn = dynamic_cast<Button*>(this->arr[i]);
			    if (prevBtn)
			    {
			        prevBtn->setFocused(false);
			        prevBtn->showCtrl();
			    }
			
			    i--;
			    if (i < 0)
			    {
			        i = this->count - 1;
			    }
			    while (this->arr[i]->GetType() == LABEL || this->arr[i]->GetType() == TABLE)
			    {
			        if (i > 0)
			        {
			            i--;
			        }
			        else
			        {
			            i = this->count - 1;
			        }
			    }
			
			    Button* currBtn = dynamic_cast<Button*>(this->arr[i]);
			    if (currBtn)
			    {
			        currBtn->setFocused(true);
			        currBtn->showCtrl();
			    }
			
			    Tool::gotoxy(this->arr[i]->GetX() + 2 + strlen(this->arr[i]->GetContext().c_str()), this->arr[i]->GetY() + 1);
			    break;
			}
			case KEY_DOWN:
			{
				Button* prevBtn = dynamic_cast<Button*>(this->arr[i]);
			    if (prevBtn)
			    {
			        prevBtn->setFocused(false);
			        prevBtn->showCtrl();
			    }
			
			    i++;
			    if (i >= this->count)
			    {
			        i = 0;
			    }
			    while (this->arr[i]->GetType() == LABEL || this->arr[i]->GetType() == TABLE)
			    {
			        if (i < this->count - 1)
			        {
			            i++;
			        }
			        else
			        {
			            i = 0;
			        }
			    }
			    Button* currBtn = dynamic_cast<Button*>(this->arr[i]);
			    if (currBtn)
			    {
			        currBtn->setFocused(true);
			        currBtn->showCtrl();
			    }
			
			    Tool::gotoxy(this->arr[i]->GetX() + 2 + strlen(this->arr[i]->GetContext().c_str()), this->arr[i]->GetY() + 1);
			    break;
			}
			case KEY_LEFT:
				if(this->arr[i]->GetType() == EDIT)
				{
					this->flag = -100;
                	return;	
                	break; 
				}				
            case KEY_RIGHT:
            	if(this->arr[i]->GetType() == EDIT)
				{
					this->flag = -101;
                	return;
                	break;
				}
			default:
				if(this->arr[i]->GetType() == EDIT)
				{
					Edit* editCtrl = (Edit*)this->arr[i];
					if (editCtrl != NULL) 
					{
						editCtrl->inputControl(ikey);
					}
				}
				break;
		}
	}
	return ;
}

void Window::SetCurrentUser(BaseUser* user)
{
	this->currentUser = user;
}

BaseUser* Window::GetCurrentUser()
{
	return this->currentUser;
}

void Window::SetCurrentApp(Appointment* app)
{
	this->mainApp = app;
}

Appointment* Window::GetCurrentApp()
{
	return this->mainApp;
}
