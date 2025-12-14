#include "AppointmentManager.h"

AppointmentManager* AppointmentManager::instance = NULL;

AppointmentManager::AppointmentManager()
{
	this->loadTimeSlots();
}

void AppointmentManager::loadTimeSlots() 
{
    ifstream file("./data/time/times.txt");
	if (!file.is_open())
	{
		cout << "无法打开时间段文件: ./data/time/times.txt" << endl;
		return;
	}

	string line;
	timeSlotMap.clear();
    timeIdToSlotMap.clear();
    
	while (getline(file, line))
	{
		istringstream iss(line);
		int id;
		string slot, num;
		if (iss >> id >> slot >> num)
		{
			this->timeSlotMap[slot].push_back(id);
			this->timeIdToSlotMap[id] = slot;
		}
	}
	file.close();
}

vector<int> AppointmentManager::getTimeIdsForSlot(string timeSlot)
{
    map<string, vector<int> >::iterator iter = this->timeSlotMap.find(timeSlot);
    if (iter == this->timeSlotMap.end())
    {
        return vector<int>(); // 返回空vector，避免野指针
    }
    return iter->second;
}

int AppointmentManager::getSlotAppointmentCount(string doctorId, int day, string timeSlot)
{
    vector<Appointment> apps = loadAppointments(doctorId);
    vector<int> timeIds = getTimeIdsForSlot(timeSlot);
    int count = 0;

    // 遍历预约记录
    for (vector<Appointment>::size_type i = 0; i < apps.size(); ++i)
    {
        Appointment app = apps[i];
        // 只统计指定日期+指定时间段ID的预约
        if (app.getDay() == day)
        {
            int appTime = app.getTime();
            // 遍历时间段ID列表（[1,2]）
            for (vector<int>::size_type j = 0; j < timeIds.size(); ++j)
            {
                if (appTime == timeIds[j])
                {
                    count++;
                    break; // 避免重复计数
                }
            }
        }
    }
    return count;
}

string AppointmentManager::getDoctorFilePath(string doctorId)
{
    return "./data/appointments/"+doctorId+".txt";
}

AppointmentManager* AppointmentManager::getInstance()
{
	if (!instance) 
	{
        instance = new AppointmentManager();
    }
    return instance;
}

bool AppointmentManager::isTimeSlotFull(string doctorId, int day, string slot) 
{
    int count = this->getSlotAppointmentCount(doctorId, day, slot);
    return count >= 2;
}

bool AppointmentManager::saveAppointment(Appointment app)
{
    //必填字段不能为空
    if (app.getDoctorId().empty() || app.getPatientId().empty() || app.getDay() <= 0 || app.getTime() <= 0)
    {
        return false;
    }

    // 根据timeId获取对应的时间段（如1→"9:00-10:00"）
    map<int, string>::iterator it = timeIdToSlotMap.find(app.getTime());
    if (it == timeIdToSlotMap.end())
    {
        cout << "无效的时间段ID：" << app.getTime() << endl;
        return false;
    }
    string slot = it->second;

    //判断该时间段是否已约满
    if (isTimeSlotFull(app.getDoctorId(), app.getDay(), slot))
    {
        cout << "时间段" << slot << "已约满（当前计数：2）" << endl;
        return false;
    }
    
    //检查患者当天是否已有预约
    if (checkPatientAppointmented(app.getPatientId(), app.getDay()))
    {
        cout << "患者 " << app.getPatientId() << " 当天已存在预约，无法重复预约" << endl;
        return false;
    }

    // 写入文件
    FILE* file = fopen(getDoctorFilePath(app.getDoctorId()).c_str(), "a");
    if (file == NULL) 
    {
        cout << "无法打开预约文件：" << getDoctorFilePath(app.getDoctorId()) << endl;
        return false;
    }

    //字段数匹配用户示例
    fprintf(file, "%d %d %s %s %s %s %d\n",
            app.getDay(),
            app.getTime(),
            app.getPatientId().c_str(),
            app.getDoctorId().c_str(),
            app.getDesc().c_str(),
			app.getVisitDesc().c_str(),
			app.getState());

    fclose(file);
    return true;
}

vector<Appointment> AppointmentManager::loadAppointments(string doctorId)
{
    vector<Appointment> apps;
    string filePath = getDoctorFilePath(doctorId);
    FILE* file = fopen(filePath.c_str(), "r");
    if (file == NULL) 
    {
        // 首次预约，直接返回空列表
        return apps;
    }

    int day, time, state;
    // 定义足够大的缓冲区，避免字符串截断
    char patientId[64] = {0};
    char docId[64] = {0};
    char desc[256] = {0};
    char vdesc[256] = {0};

    while (fscanf(file, "%d %d %63s %63s %255s %255s %d[^\n]",  // %[^\n]匹配带空格的描述
                 &day, &time, patientId, docId, desc,vdesc,&state) == 7) 
    {
        Appointment app(day, time, docId, patientId, desc);
        apps.push_back(app);

        // 清空缓冲区，避免残留数据
        memset(patientId, 0, sizeof(patientId));
        memset(docId, 0, sizeof(docId));
        memset(desc, 0, sizeof(desc));
    }

    fclose(file);
    return apps;
}

bool AppointmentManager::checkPatientAppointmented(string patientId, int day)
{
    // 获取所有科室
    DepartmentManager* deptMgr = DepartmentManager::GetInstance();
    vector<Department*> allDepartments = deptMgr->getAllDepartments();
	vector<Department*>::iterator deptIter;
    // 遍历所有科室
    for (deptIter = allDepartments.begin(); deptIter != allDepartments.end(); ++deptIter)
    {
        Department* dept = *deptIter;
        // 获取科室下所有医生
        map<string, Doctor*>* doctors = dept->GetDepDoctors();
        map<string, Doctor*>::iterator docIter;
        for (docIter = doctors->begin(); docIter != doctors->end(); ++docIter)
        {
            // 加载该医生的所有预约
            string doctorId = docIter->first;
            vector<Appointment> apps = loadAppointments(doctorId);
            
            // 检查是否有相同患者当天的预约
            for (vector<Appointment>::size_type i = 0; i < apps.size(); ++i)
            {
                Appointment app = apps[i];
                if (app.getPatientId() == patientId && app.getDay() == day)
                {
                    return true;  // 找到重复预约
                }
            }
        }
    }
    return false;  // 无重复预约
}

vector<Appointment*> AppointmentManager::getallAppointments()
{
	vector<Appointment*> allApps;
    string dirPath = "./data/appointments/";
    char searchPath[MAX_PATH];
    sprintf(searchPath, "%s*.txt", dirPath.c_str());

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "无法打开目录: " << dirPath << endl;
        return allApps;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;  // 跳过目录

        string fileName = findData.cFileName;
        string doctorId = fileName.substr(0, fileName.find_last_of("."));

        vector<Appointment> apps = loadAppointments(doctorId);
        // 修正3：用传统迭代器循环替代范围for（兼容C++98）
        for (vector<Appointment>::const_iterator it = apps.begin(); it != apps.end(); ++it)
        {
            // 利用拷贝构造函数创建新对象（需先添加拷贝构造函数）
            allApps.push_back(new Appointment(*it));
        }
    } while (FindNextFileA(hFind, &findData) != 0);  // 使用ANSI版本FindNextFileA

    FindClose(hFind);
    return allApps;
}

void AppointmentManager::saveAppointments(const string& doctorId, const vector<Appointment*>& apps)
{
    string filePath = "./data/appointments/" + doctorId + ".txt";
    ofstream outFile(filePath.c_str(), ios::trunc); // 覆盖写入
    if (!outFile.is_open())
    {
        cerr << "无法打开预约文件：" << filePath << endl;
        return;
    }
    
    for (size_t i = 0; i < apps.size(); ++i)
    {
        Appointment* app = apps[i];
        if (app == NULL) continue;
        outFile << app->getDay() << " " 
                << app->getTime() << " " 
                << app->getPatientId().c_str() << " " 
                << app->getDoctorId().c_str() << " " 
                << app->getDesc().c_str() << " " 
                << app->getVisitDesc().c_str() << " " 
                << app->getState() << endl;
    }
    outFile.close();
}
