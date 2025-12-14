#include "AppointmentWin.h"

AppointmentWin::AppointmentWin()
:Window()
{
	
}

AppointmentWin::AppointmentWin(int win_startX, int win_startY, int win_width, int win_height)
: Window(win_startX, win_startY, win_width, win_height)
{
	// 初始化标签
    this->lab1 = new Label(LABEL, 45, 1, 0, 0, "欢迎使用门诊预约系统");
    this->lab2 = new Label(LABEL, 45, 3, 0, 0, "预约门诊");
    this->lab3 = new Label(LABEL, 30, 6, 0, 0, "选择医院：");
    this->lab4 = new Label(LABEL, 30, 9, 0, 0, "选择科室：");
    this->lab5 = new Label(LABEL, 30, 12, 0, 0, "选择医生：");
    this->lab6 = new Label(LABEL, 30, 15, 0, 0, "选择时间：");
    this->lab7 = new Label(LABEL, 30, 18, 0, 0, "描    述：");

    // 初始化输入框
    this->edit1 = new Edit(EDIT, 40, 6, 10, 3, "省立医院", 0, 0, 0); // 医院默认值，不可编辑
    this->edit2 = new Edit(EDIT, 40, 9, 10, 3, "", 0, 0, 4);         // 科室输入框
    this->edit3 = new Edit(EDIT, 40, 12, 10, 3, "", 0, 0, 4);        // 医生输入框
    this->edit4 = new Edit(EDIT, 40, 15, 10, 3, "", 0, 0, 4);        // 日期输入框
    this->edit5 = new Edit(EDIT, 64, 15, 10, 3, "", 0, 0, 4);        // 时间段输入框
    this->edit6 = new Edit(EDIT, 40, 18, 20, 4, "", 50, 0, 4);       // 描述输入框（支持中文）

    // 初始化下拉按钮
    this->btn1 = new Button(BUTTON, 58, 9, 4, 3, "↓");  // 科室下拉按钮
    this->btn2 = new Button(BUTTON, 58, 12, 4, 3, "↓"); // 医生下拉按钮
    this->btn3 = new Button(BUTTON, 58, 15, 4, 3, "↓"); // 日期下拉按钮
    this->btn4 = new Button(BUTTON, 82, 15, 4, 3, "↓"); // 时间段下拉按钮

    // 初始化功能按钮
    this->btn5 = new Button(BUTTON, 40, 23, 8, 3, "确认");
    this->btn6 = new Button(BUTTON, 55, 23, 8, 3, "取消");

    // 初始化下拉框
    this->comboDep = new ComoboBoxWin(40, 11, 15, 2);   // 科室下拉框
    this->comboDoc = new ComoboBoxWin(40, 14, 15, 2);   // 医生下拉框
    this->comboDay = new ComoboBoxWin(20, 10, 40, 20);   // 日期下拉框
    this->comboTime = new ComoboBoxWin(20, 35, 40, 20);  // 时间段下拉框
    
    this->addControl(this->lab1);//0
    this->addControl(this->lab2);//1
    this->addControl(this->lab3);//2
    this->addControl(this->lab4);//3
    this->addControl(this->lab5);//4
    this->addControl(this->lab6);//5
    this->addControl(this->lab7);//6
    this->addControl(this->edit1);//7
    this->addControl(this->edit2);//8
    this->addControl(this->btn1);//9
    this->addControl(this->edit3);//10
    this->addControl(this->btn2);//11
    this->addControl(this->edit4);//12
    this->addControl(this->btn3);//13
    this->addControl(this->edit5);//14
    this->addControl(this->btn4);//15
    this->addControl(this->edit6);//16
    this->addControl(this->btn5);//17
    this->addControl(this->btn6);//18
    
    this->loadDeptOptions();   // 加载科室选项到comboDep
    this->loadDayOptions();    // 加载日期选项到comboDay
    this->loadTimeOptions();
}

AppointmentWin::~AppointmentWin()
{
    delete this->lab1;
    delete this->lab2;
    delete this->lab3;
    delete this->lab4;
    delete this->lab5;
    delete this->lab6;
    delete this->lab7;
    delete this->edit1;
    delete this->edit2;
    delete this->btn1;
    delete this->edit3;
    delete this->btn2;
    delete this->edit4;
    delete this->btn3;
    delete this->edit5;
    delete this->btn4;
    delete this->edit6;
    delete this->btn5;
    delete this->btn6;
    delete this->comboDep;
    delete this->comboDoc;
    delete this->comboDay;
    delete this->comboTime;
}

void AppointmentWin::loadDeptOptions()
{
    DepartmentManager* deptMgr = DepartmentManager::GetInstance();
    vector<Department*> Departments = deptMgr->getAllDepartments();
    vector<Department*>::iterator deptIter;
    int yPos = 11;

    for (deptIter = Departments.begin(); deptIter != Departments.end(); ++deptIter)
    {
        Department* dept = *deptIter; // 解引用迭代器获取元素
        string deptName = dept->GetDepName();
        char* deptNameChar = new char[deptName.length() + 1];
        strcpy(deptNameChar, deptName.c_str());
        this->comboDep->addOption(40, yPos, 15, 3, deptNameChar);
        yPos += 3;
        delete[] deptNameChar;
    }
}

void AppointmentWin::loadDayOptions()
{
    Workdate workDate;
    vector<string> Days = workDate.GetSevenDays();
    int colCount = 3;          // 每行显示3个
    int optionWidth = 11;      // 每个选项宽度（避免重叠）
    int optionHeight = 3;      // 每个选项高度
    int startX = 25;            // 下拉框内起始X（相对ComboBoxWin的坐标）
    int startY = 10;            // 下拉框内起始Y（相对ComboBoxWin的坐标）

    for (size_t i = 0; i < Days.size(); ++i)
    {
        // 计算当前选项的行列
        int col = i % colCount;      // 列索引（0/1/2）
        int row = i / colCount;      // 行索引
        
        // 计算绝对坐标（基于ComboBoxWin的位置 + 行列偏移）
        int xPos = startX + col * optionWidth*2;
        int yPos = startY + row * optionHeight;

        string day = Days[i];
        char* dayChar = new char[day.length() + 1];
        strcpy(dayChar, day.c_str());
        this->comboDay->addOption(xPos, yPos, optionWidth - 1, optionHeight, dayChar);
        delete[] dayChar;
    }
}

void AppointmentWin::loadTimeOptions()
{
    ifstream file("./data/time/times.txt");
    if (!file.is_open())
    {
        cerr << "无法打开时间段文件: ./data/time/times.txt" << endl;
        return;
    }

	string line;
    
    vector<string> addTimes; 
    this->timeMap.clear();
    
    int colCount = 3;
    int optionWidth = 12;
    int optionHeight = 3;
    int startX = 20;
    int startY = 15;
    size_t index = 0;

    while (getline(file, line))
    {
        istringstream iss(line);
        string id, time, num;
        if (iss >> id >> time >> num)
        {
            // 检查当前时间段是否已添加过
            bool isDuplicate = false;
            for (size_t j = 0; j < addTimes.size(); ++j)
            {
                if (addTimes[j] == time)
                {
                    isDuplicate = true;
                    break; // 重复则跳过当前行
                }
            }

            //不重复时，才添加到下拉框
            if (!isDuplicate)
            {
                // 记录到已添加列表，防止后续重复
                addTimes.push_back(time);
                this->timeMap[time] = atoi(id.c_str());

                // 原有坐标计算逻辑（一行3个）
                int col = index % colCount;
                int row = index / colCount;
                int xPos = startX + col * optionWidth*2;
                int yPos = startY + row * optionHeight;

                // 添加到下拉框
                char* timeChar = new char[time.length() + 1];
                strcpy(timeChar, time.c_str());
                this->comboTime->addOption(xPos, yPos, optionWidth - 1, optionHeight, timeChar);
                delete[] timeChar;
                index++; // 不重复时，索引递增
            }
        }
    }
    file.close();
}

void AppointmentWin::updateDoctorOptions(std::string deptName)
{
    this->comboDoc->clearOptions();

    DepartmentManager* deptMgr = DepartmentManager::GetInstance();
    vector<Department*> allDepartments = deptMgr->getAllDepartments();
    int yPos = 14;

    for (vector<Department*>::iterator deptIter = allDepartments.begin();
         deptIter != allDepartments.end(); ++deptIter)
    {
        Department* dept = *deptIter;
        if (dept->GetDepName() == deptName)
        {
            map<std::string, Doctor*>* doctors = dept->GetDepDoctors();
            map<string, Doctor*>::iterator pairIter;
            // 遍历map
            for (pairIter = doctors->begin(); pairIter != doctors->end(); ++pairIter)
            {
                Doctor* doc = pairIter->second;
                string docName = doc->GetName();
                char* docNameChar = new char[docName.length() + 1];
                strcpy(docNameChar, docName.c_str());
                this->comboDoc->addOption(40, yPos, 15, 3, docNameChar);
                yPos += 3;
                delete[] docNameChar;
            }
            break;
        }
    }
}

void AppointmentWin::paintWindow()
{
    Window::paintWindow();

    BaseUser* user = Window::GetCurrentUser();
    if (user != NULL)
    {
        Tool::gotoxy(30, 5);
        cout << "欢迎您：" << user->GetName();
    }

    time_t now = time(0);
    tm* localTime = localtime(&now);
    char date[20];
    sprintf(date, "日期：%d-%02d-%02d",
            1900 + localTime->tm_year,
            1 + localTime->tm_mon,
            localTime->tm_mday);
    Tool::gotoxy(60, 5);
    cout << date;
}

string AppointmentWin::getSelectedDoctorId() 
{
    string docName = comboDoc->GetOptionContext();
    if (docName.empty()) return "";
    
    DepartmentManager* deptMgr = DepartmentManager::GetInstance();
    vector<Department*> allDepartments = deptMgr->getAllDepartments();
    
    for (size_t i = 0; i < allDepartments.size(); ++i)
    {
        Department* dept = allDepartments[i];
        map<string, Doctor*>* doctors = dept->GetDepDoctors();
        map<string, Doctor*>::iterator iter;
        
        for (iter = doctors->begin(); iter != doctors->end(); ++iter)
        {
            Doctor* doc = iter->second;
            if (doc->GetName() == docName)
            {
                return doc->GetAccount(); // 返回医生账号作为ID
            }
        }
    }
    return "";
}

int AppointmentWin::getSelectedDay()
{
    string dayStr = comboDay->GetOptionContext();
    Workdate workDate;
    vector<string> days = workDate.GetSevenDays();
    
    for (size_t i = 0; i < days.size(); i++) {
        if (days[i] == dayStr) {
            return i + 1; // 对应1-7天
        }
    }
    return -1;
}

int AppointmentWin::getAvailableTimeId(string doctorId, int day, string timeSlot)
{
    AppointmentManager* appMgr = AppointmentManager::getInstance();
    vector<int> timeIds = appMgr->getTimeIdsForSlot(timeSlot);
    
    // 时间段无对应ID
    if (timeIds.empty())
    {
        cout << "无效的时间段：" << timeSlot << endl;
        return -1;
    }
    
    // 统计当前预约数
    int total = appMgr->getSlotAppointmentCount(doctorId, day, timeSlot);
    
    // 严格判断约满（total>=2则返回-1）
    if (total >= 2)
    {
        return -1;
    }
    
    //避免vector越界（total必须小于timeIds.size()）
    if (total >= (int)timeIds.size())
    {
        return -1;
    }
    
    //第1次约→timeIds[0]，第2次约→timeIds[1]
    return timeIds[total];
}

int AppointmentWin::getSelectedTime()
{
    string selectedTime = comboTime->GetOptionContext();
    // 从映射表中获取对应的时间编号
    map<string, int>::iterator iter = timeMap.find(selectedTime);
    if (iter != timeMap.end())
    {
        return iter->second;
    }
    return 0;  // 未选中返回0
}


int AppointmentWin::doAction()
{
    if (this->flag == 9) // 科室下拉按钮
    {
        this->comboDep->SetShow(!this->comboDep->GetShow());
        if (this->comboDep->GetShow())
        {
            this->comboDep->paintWindow();
            this->comboDep->winRun();
            int res = this->comboDep->doAction();
            if (res != -1)
            {
                string dept = this->comboDep->GetOptionContext();
                ((Edit*)edit2)->SetContext(dept);
                this->updateDoctorOptions(dept);
            }
            this->comboDep->SetShow(false);
        }
        return 14;
    }

    if (this->flag == 11) // 医生下拉按钮
    {
        this->comboDoc->SetShow(!this->comboDoc->GetShow());
        if (this->comboDoc->GetShow())
        {
            this->comboDoc->paintWindow();
            this->comboDoc->winRun();
            int res = this->comboDoc->doAction();
            if (res != -1)
            {
                string doc = this->comboDoc->GetOptionContext();
                ((Edit*)edit3)->SetContext(doc);
            }
            this->comboDoc->SetShow(false);
        }
        return 14;
    }

    if (this->flag == 13) // 日期下拉按钮
    {
        this->comboDay->SetShow(!this->comboDay->GetShow());
        if (this->comboDay->GetShow())
        {
            this->comboDay->paintWindow();
            this->comboDay->winRun();
            int res = this->comboDay->doAction();
            if (res != -1)
            {
                string day = this->comboDay->GetOptionContext();
                ((Edit*)edit4)->SetContext(day);
            }
            this->comboDay->SetShow(false);
        }
        return 14;
    }

    if (this->flag == 15) // 时间段下拉按钮
    {
        this->comboTime->SetShow(!this->comboTime->GetShow());
        if (this->comboTime->GetShow())
        {
            this->comboTime->paintWindow();
            this->comboTime->winRun();
            int res = this->comboTime->doAction();
            if (res != -1)
            {
                string time = this->comboTime->GetOptionContext();
                ((Edit*)edit5)->SetContext(time);
            }
            this->comboTime->SetShow(false);
        }
        return 14;
    }

    if (this->flag == 17) 
    { 
        string doctorId = getSelectedDoctorId();
        int day = getSelectedDay();
        string timeSlot = comboTime->GetOptionContext();
        // 获取当前用户
        BaseUser* user = GetCurrentUser();
        
        // 避免空值导致的逻辑异常
        if (doctorId.empty() || day <= 0 || timeSlot.empty() || user == NULL || user->GetAccount().empty())
        {
            Tool::gotoxy(40, 25);
            cout << "请完善预约信息（医生/日期/时间段不能为空）" << endl;
            Sleep(1500);
            return 14;
        }
        
        // 获取可用的时间段ID
        int timeId = getAvailableTimeId(doctorId, day, timeSlot);
        if (timeId == -1)
        {
            Tool::gotoxy(40, 25);
            cout << "当前时段已经约满" << endl;
            Sleep(1500);
            return 14;
        }
        
        // 构建预约对象
        Appointment app;
        app.setDay(day);
        app.setTime(timeId);
        app.setDoctorId(doctorId);
        app.setPatientId(user->GetAccount());
        app.setDesc(edit6->GetContext()); // 预约描述
        
        // 保存预约
        if (AppointmentManager::getInstance()->saveAppointment(app))
        {
            Tool::gotoxy(40, 25);
            cout << "预约成功！时间段ID：" << timeId << endl;
            Sleep(1500);
			clearEdits();
            return 13;
        }
        else
        {
            Tool::gotoxy(40, 25);
            cout << "预约失败（可能时段已约满/文件写入错误）" << endl;
            Sleep(1500);
			return 14;
        }
        return 14;
    }

    if (this->flag == 18) // 取消按钮
    {
        this->clearEdits();
        return 13;
    }

    if (this->flag == -1) // ESC键
    {
        return 13;
    }

    return 14;
}

void AppointmentWin::clearEdits()
{
    ((Edit*)edit2)->SetContext("");
    ((Edit*)edit3)->SetContext("");
    ((Edit*)edit4)->SetContext("");
    ((Edit*)edit5)->SetContext("");
    ((Edit*)edit6)->SetContext("");
}
