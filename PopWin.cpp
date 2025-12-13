#include "PopWin.h"

PopWin::PopWin()
:Window()
{
	this->title = new char[32]; 
    strcpy(this->title, "提示");
	this->result = -1;
	this->isCompleted = false;
	this->currentIndex = 0;
	this->isComboOpen = false;
	this->ctrls = new vector<Ctrl*>();  
    this->comboBoxes = new vector<ComoboBoxWin*>();
}

PopWin::PopWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	this->title = new char[32];
    strcpy(this->title, "提示");
    this->result = -1;
    this->isCompleted = false;
    this->currentIndex = 0;
    this->isComboOpen = false;
    this->ctrls = new vector<Ctrl*>();
    this->comboBoxes = new vector<ComoboBoxWin*>();
}

PopWin::~PopWin()
{
	for(this->iter1 = this->ctrls->begin();this->iter1 != this->ctrls->end();++this->iter1)
	{
		delete *(this->iter1);
	}
	delete this->ctrls;
	this->ctrls = NULL;
	for(this->iter2 = this->comboBoxes->begin();this->iter2 != this->comboBoxes->end();++this->iter2)
	{
		delete *(this->iter2);
	}
	delete this->comboBoxes;
	this->comboBoxes = NULL;
	
	delete[] this->title;
	this->title = NULL;
}

void PopWin::addControl(Ctrl* con)
{
	if(con!=NULL)
	{
		Window::addControl(con);
		this->ctrls->push_back(con);
	}
}

void PopWin::addComboBox(ComoboBoxWin* combo)
{
	if(combo != NULL)
	{
		this->comboBoxes->push_back(combo);
	}
}

void PopWin::setTitle(char* title)
{
	if(title != NULL)
	{
		strncpy(this->title, title, 31);
		this->title[31] = '\0';
	}
}

int PopWin::getResult()
{
	return this->result;
}

void PopWin::paintWindow()
{
	Tool::paintBoder(this->win_startX,this->win_startY,this->win_width,this->win_height);
	if(title!=NULL)
	{
		int titleX = this->win_startX + (this->win_width*2-strlen(this->title))/2;
		Tool::gotoxy(titleX,this->win_startY+1);
		cout<<title;
	}
	for(this->iter1 = this->ctrls->begin();this->iter1 != this->ctrls->end();++this->iter1)
	{
		(*this->iter1)->showCtrl();
	}
	for(this->iter2 = this->comboBoxes->begin();this->iter2 != this->comboBoxes->end();++this->iter2)
	{
		if((*this->iter2)->GetShow())
		{
			(*this->iter2)->paintWindow();
		}
	}
}

int PopWin::doAction()
{
	if(this->flag == -1)
	{
		this->isCompleted = true;
		this->result = -1;
		return -1;
	}
	
	if(this->flag >= 0 && (size_t)this->flag < this->ctrls->size())
	{
		if(this->ctrls->at(this->flag)->GetType() == BUTTON)
		{
			this->result = this->flag;
			this->isCompleted = true;
			return this->flag;
		}
	}
	
	for(size_t i = 0;i < this->comboBoxes->size();++i)
	{
		if(this->comboBoxes->at(i)->GetShow())
		{
			int comboRes = this->comboBoxes->at(i)->doAction();
			if(comboRes == -1)
			{
				this->comboBoxes->at(i)->SetShow(false);
				this->isComboOpen = false;
			}
			return 0; 
		}
	}
	return 0;
}

vector<Ctrl*>* PopWin::getCtrls()
{
	return this->ctrls;
}
vector<ComoboBoxWin*>* PopWin::getComboBoxes()
{
	return this->comboBoxes;
}
void PopWin::winRun()
{
	this->isCompleted = false;
	this->result = -1;
	this->flag = -1;
	this->currentIndex = 0;
	this->isComboOpen = false;
	
	while (this->currentIndex < (int)this->ctrls->size()) {
        int type = this->ctrls->at(this->currentIndex)->GetType();
        if (type != LABEL && type != TABLE) {
            break;
        }
        this->currentIndex++;
    }

    if (this->currentIndex < (int)this->ctrls->size()) {
        Ctrl* focusCtrl = this->ctrls->at(currentIndex);
        Tool::gotoxy(focusCtrl->GetX() + 2, focusCtrl->GetY() + 1);
    }

    while (!this->isCompleted) {
        int key = Tool::getkey();
        switch (key) {
            case KEY_ESC:
                this->flag = -1;
                this->doAction();
                break;
            case KEY_ENTER:
                for (size_t i = 0; i < this->comboBoxes->size(); ++i) 
				{
                    if (this->comboBoxes->at(i)->GetShow()) 
					{
                        this->comboBoxes->at(i)->winRun();
                        this->comboBoxes->at(i)->doAction();
                        this->comboBoxes->at(i)->SetShow(false);
                        this->isComboOpen = false;
                        this->paintWindow();
                       
                        if (this->currentIndex < (int)this->ctrls->size()) 
						{
                            Ctrl* focusCtrl = this->ctrls->at(currentIndex);
                            Tool::gotoxy(focusCtrl->GetX() + 2, focusCtrl->GetY() + 1);
                        }
                        break;
                    }
                }
                
                if (!this->isComboOpen && this->currentIndex < (int)this->ctrls->size()) 
				{
					Ctrl* ctrl = this->ctrls->at(currentIndex);
				    if (ctrl->GetType() == BUTTON) 
					{
				        Button* btn = dynamic_cast<Button*>(ctrl);
				        if (btn && btn->getShowMode() == 1) 
						{
				            btn->setFocused(false);
				            btn->showCtrl();
				    	}
				    }
                    this->flag = this->currentIndex;
                    this->doAction();
                }
                break;
            case KEY_UP:
                if (this->ctrls->empty()) break;
                this->currentIndex = (this->currentIndex - 1 + this->ctrls->size()) % this->ctrls->size();
			    while (this->ctrls->at(this->currentIndex)->GetType() == LABEL || 
			           this->ctrls->at(this->currentIndex)->GetType() == TABLE)
			    {
			        this->currentIndex = (this->currentIndex - 1 + this->ctrls->size()) % this->ctrls->size();
			    }
			    Tool::gotoxy(this->ctrls->at(this->currentIndex)->GetX() + 2, 
			                this->ctrls->at(this->currentIndex)->GetY() + 1);
			    break;
            case KEY_DOWN:
                if (this->ctrls->empty()) break;
                this->currentIndex = (this->currentIndex + 1) % this->ctrls->size();
			    while (this->ctrls->at(this->currentIndex)->GetType() == LABEL || 
			           this->ctrls->at(this->currentIndex)->GetType() == TABLE)
			    {
			        this->currentIndex = (this->currentIndex + 1) % this->ctrls->size();
			    }
			    Tool::gotoxy(this->ctrls->at(this->currentIndex)->GetX() + 2, 
			                this->ctrls->at(this->currentIndex)->GetY() + 1);
			    break;
            default:
                if (this->currentIndex < (int)this->ctrls->size() && 
                    this->ctrls->at(this->currentIndex)->GetType() == EDIT) {
                    Edit* edit = dynamic_cast<Edit*>(this->ctrls->at(this->currentIndex));
                    if (edit) edit->inputControl(key);
                }
                break;
        }
    }
}
