#include "ComoboBoxWin.h"

ComoboBoxWin::ComoboBoxWin()
:Window()
{
	this->options = new vector<Button*>();
	this->currentOptionContext = new char[40];
	strcpy(this->currentOptionContext,"");
	this->ifShow = false; 
}
ComoboBoxWin::ComoboBoxWin(int win_startX,int win_startY,int win_width,int win_height)
:Window(win_startX, win_startY, win_width, win_height)
{
	this->options = new vector<Button*>();
	this->currentOptionContext = new char[40];
	strcpy(this->currentOptionContext,"");
	this->ifShow = false;
}
ComoboBoxWin::~ComoboBoxWin()
{
	for(this->iter = this->options->begin();this->iter != this->options->end();this->iter++)
	{
		delete *(this->iter);
	}
	this->options->clear();
	delete this->options;
	delete[] this->currentOptionContext;
}
	
void ComoboBoxWin::SetShow(bool show)
{
	this->ifShow = show;
}

bool ComoboBoxWin::GetShow()
{
	return this->ifShow;
}

void ComoboBoxWin::SetPosition(int x,int y)
{
	this->win_startX = x;
	this->win_startY = y;
}

void ComoboBoxWin::addOption(int Ox, int Oy, int Owidth, int Oheight,char* OContext)
{
	Button* Obtn = new Button(BUTTON, Ox, Oy, Owidth, Oheight, OContext);
    this->options->push_back(Obtn);
    this->addControl(Obtn);
}

void ComoboBoxWin::clearOptions()
{
    if (options == NULL) return;
    
    // 释放每个Button的内存
    for (iter = options->begin(); iter != options->end(); ++iter)
    {
        delete *iter;  // 释放单个按钮
    }
    options->clear();  // 清空向量
    strcpy(currentOptionContext, "");
}

int ComoboBoxWin::doAction()
{
	if (this->flag == -1)
    {
        this->ifShow = false;
        return -1;
    }
    
    if (this->options->empty())
    {
        return -2;
    }
    //只有显示时才驱动
    if (this->ifShow && this->flag >= 0 && (size_t)this->flag < this->options->size())
    {
        strcpy(this->currentOptionContext, this->options->at(this->flag)->GetContext().c_str());
        this->ifShow = false;
        return -2;  
    }
    else
    {
        this->ifShow = !this->ifShow;
    }
    
    return 0;
}
	
char* ComoboBoxWin::GetOptionContext()
{
	return this->currentOptionContext;
}

void ComoboBoxWin::paintWindow()
{
	if (this->ifShow)
    {   
		for (this->iter = this->options->begin(); this->iter != this->options->end(); this->iter++)
	    {
	        (*iter)->showCtrl();
	    }
    }
}


void ComoboBoxWin::winRun()
{
    if (this->options->empty()) 
		return;

    int currentIndex = 0;
    
    Tool::gotoxy(this->options->at(currentIndex)->GetX() + 2, this->options->at(currentIndex)->GetY() + 1);

    while (true)
    {
        int key = Tool::getkey();
        switch (key)
        {
            case KEY_ESC:
                this->flag = -1;
                return;
            case KEY_ENTER:
                this->flag = currentIndex;
                return;
            case KEY_UP:
                currentIndex = (currentIndex - 1 + this->options->size()) % this->options->size();
                break;
            case KEY_DOWN:
                currentIndex = (currentIndex + 1) % this->options->size();
                break;
            default:
                continue;
        }
        
        Tool::gotoxy(this->options->at(currentIndex)->GetX() + 2, this->options->at(currentIndex)->GetY() + 1);
    }
}
