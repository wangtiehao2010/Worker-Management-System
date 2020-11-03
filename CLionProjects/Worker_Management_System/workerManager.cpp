//
// Created by david on 02.11.20.
//
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "worker.h"

//构造函数
workerManager::workerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //1、文件不存在的情况
    if (!ifs.is_open())
    {
        //cout << "File does not exist" << endl;

        this->m_EmpNum = 0;  //初始化人数
        this->m_FileIsEmpty = true;  //初始化文件为空标志
        this->m_EmpArray = NULL;  //初始化数组
        ifs.close();  //关闭文件
        return;
    }

    //2、文件存在，并且没有记录
    char c;
    ifs >> c;
    if (ifs.eof())
    {
        //cout << "File is empty！" << endl;
        this->m_EmpNum = 0;  //初始化人数
        this->m_FileIsEmpty = true;  //初始化文件为空标志
        this->m_EmpArray = NULL;  //初始化数组
        ifs.close();  //关闭文件
        return;
    }

    //3、文件存在，并且记录了数据
    int num = this->get_EmpNum();

    this->m_EmpNum = num; //更新成员属性
    //开辟空间
    this->m_EmpArray = new Worker * [this->m_EmpNum];
    //将文件中的数据存到数组中
    this->init_Emp();
    //初始化文件为空标志
    this->m_FileIsEmpty = false;
}

//析构函数
workerManager::~workerManager()
{
    if(this->m_EmpArray != NULL)
    {
        delete m_EmpArray;
        m_EmpArray = NULL;
    }
}

//显示菜单
void workerManager::Show_Menu()
{
    cout << "************************************************" << endl;
    cout << "**  welcome to the Staff Management system  ****" << endl;
    cout << "**************  0. Exit the system  ************" << endl;
    cout << "**************  1. Add new employee  ***********" << endl;
    cout << "**************  2. show employee  **************" << endl;
    cout << "**************  3. delete employee  ************" << endl;
    cout << "**************  4. edit employee  **************" << endl;
    cout << "**************  5. find employee  **************" << endl;
    cout << "**************  6. Sort by staff code  *********" << endl;
    cout << "**************  7. clean all data  *************" << endl;
    cout << "************************************************" << endl;
    cout << endl;
}

//退出函数
void workerManager::exitSystem()
{
    cout << "See you next time" << endl;
    exit(0);
}

//增加职工
void workerManager::Add_Emp()
{
    cout << "Please enter the number of additional employees: " << endl;

    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker ** newSpace = new Worker*[newSize];

        //将原空间下的内容存储到新的空间下
        if (this->m_EmpArray != NULL)
        {
           for (int i = 0; i < this->m_EmpNum; i++)
           {
               newSpace[i] = this->m_EmpArray[i];
           }
        }

        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "Please enter the staff code of the No." << i+1 << " new staff: " << endl;
            cin >> id;

            //判断新输入的id是否已经存在，如存在，报错
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_ID == id)
                {
                    cout << "the staff code is existed, please enter again:" << endl;
                    cin >> id;
                    i = -1; //输入新的id号后重新遍历已经存在的职工编号进行对比,
                            //i = -1是因为要使i在for循环中从0开始，因为执行完这句语句后会执行 i++ 语句（-1+1 = 0）， 从而实现 i=0
                }
            }

            cout << "Please enter the name of the No." << i+1 << " new staff: " << endl;
            cin >> name;


            cout << "Please enter the job code of the No." << i+1 << " new staff: " << endl;
            cout << "1. general staff" << endl;
            cout << "2. manager" << endl;
            cout << "3. boss" << endl;
            cin >> dSelect;
            Worker * worker = NULL;

            switch (dSelect)
            {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3:
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
            }

            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有的空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新职工的个数
        this->m_EmpNum = newSize;

        //更新职工不为空标志
        this->m_FileIsEmpty = false;

        //提示添加成功
        cout << addNum << " Staff(s)" << "are successfully added" <<endl;

        //保存到文件
        this->save();
    }
    else
    {
        cout << "Input Error" << endl;
    }

    //按任意键，清屏回到上级目录
}

//保存文件
void workerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for( int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptID << endl;
    }

    ofs.close();
}

//统计人数
int workerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dID;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dID)
    {
        //记录人数
        num++;
    }
    ifs.close();

    return num;
}

//初始化员工
void workerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dID;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dID)
    {
        Worker * worker = NULL;
        //根据不同部门Id创建不同的对象
        if (dID == 1)//普通职工
        {
            worker = new Employee(id,name,dID);
        }
        else if (dID == 2)//经理
        {
            worker = new Manager(id,name,dID);
        }
        else//老板
        {
            worker = new Boss(id,name,dID);
        }
        //存放在数组中
        this->m_EmpArray[index] = worker;
        index ++;
    }
    //关闭文件
    ifs.close();
}

//显示职工
void workerManager::show_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File does not exist or it is empty!" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            //利用多态调用接口
            this->m_EmpArray[i]->showInfo();
        }
    }

}


//按照职工编号判断该职工是否存在，若存在返回职工在数组中的位置，否则返回-1
int workerManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_ID == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void workerManager::del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "File does not exist or it is empty!" << endl;
    }
    else
    {
        //按照职工编号删除职工
        cout << "Please enter the staff code you want to delete: " << endl;
        int id = 0;
        cin >> id;

        int index = this->isExist(id);
        if (index != -1)//说明职工存在，并且要删除数组中index位置的员工
        {
            //数据前移
            for (int i = index; i < this->m_EmpNum-1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--; //更新数组中的记录人数
            //数据同步更新到文件中
            this->save();

            cout << "It is deleted successfully！" << endl;
        }
        else
        {
            cout << "Can not find this staff" << endl;
        }
    }

}

//修改职工
void workerManager::mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "File does not exist or it is empty!" << endl;
    }
    else
    {
        cout << "Please enter the staff code you want to edit: " << endl;
        int id;
        cin >> id;

        int ret = this->isExist(id);
        if(ret != -1)
        {
            //查找到该编号的职工

            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "Staff with staff code: " << id << "is found，please enter a new staff code: " << endl;
            cin >> newId;
            cout << "Please enter a new name: "<<endl;
            cin >> newName;
            cout << "Please enter the job code" << endl;
            cout << "1. general staff" << endl;
            cout << "2. manager" << endl;
            cout << "3. boss" << endl;
            cin >> dSelect;

            Worker * worker = NULL;

            switch (dSelect)
            {
                case 1:
                    worker = new Employee(newId, newName, 1);
                    break;
                case 2:
                    worker = new Manager(newId, newName, 2);
                    break;
                case 3:
                    worker = new Boss(newId, newName, 3);
                    break;
                default:
                    break;
            }
            //更新数组，将新的数据覆盖到原来对应位置的数据上
            this->m_EmpArray[ret] = worker;
            cout << "It is edited successfully!" << endl;

            //保存到文件中
            this->save();

        }
        else
        {
            cout << "Can not find this staff" << endl;
        }
    }

}

//查找职工
void workerManager::find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "File does not exist or it is empty!" << endl;
    }
    else
    {
        cout << "Please choose a way to find a staff " << endl;
        cout << "1、according to the staff code" << endl;
        cout << "2、according to the name" << endl;

        int select = 0;
        cin >> select;

        if (select == 1)
        {
            int id;
            cout << "Please enter the staff code you want to find: " << endl;
            cin >> id;

            int ret = isExist(id);
            if (ret != -1)
            {
                cout << "Successfully! here are the information: " << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "Can not find this staff" << endl;
            }
        }
        else if (select == 2)
        {
            string name;
            cout << "please enter name you want to find: " << endl;
            cin >> name;

            bool flag = false; // 查找到的标志
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (m_EmpArray[i]->m_Name == name)
                {
                    cout << "Successfully! The information of staff with staff code: "
                         << m_EmpArray[i]->m_ID
                         << " is shown below"<< endl;

                    flag = true;

                    this->m_EmpArray[i]->showInfo();
                }
            }
            if(flag == false)
            {
                cout << "Can not find this staff" << endl;
            }
        }
        else
        {
            cout << "Input error" << endl;
        }
    }

}

//排序员工
void workerManager::sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "File does not exist or it is empty!" << endl;
    }
    else
    {
        cout << "Please choose a way to sort" << endl;
        cout << "1. Ascending according to the staff code" << endl;
        cout << "2. Descending according to the staff code" << endl;

        int select = 0;
        cin >> select;

        for (int i = 0; i < m_EmpNum; i++)
        {
            int minOrMax = i;
            for (int j = i+1; j < m_EmpNum; j++)
            {
                if(select == 1) //升序
                {
                    if(m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID)
                    {
                        minOrMax = j;
                    }
                }
                else //降序
                {
                    if(m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID)
                    {
                        minOrMax = j;
                    }
                }
            }
            if (i != minOrMax)
            {
                Worker * temp = m_EmpArray[i];
                m_EmpArray[i] = m_EmpArray[minOrMax];
                m_EmpArray[minOrMax] = temp;
            }
        }

        cout << "Sorting Successfully" << endl;
        this->save();
        this->show_Emp();
    }

}

//清空文件
void workerManager::clean_File()
{
    cout << "clean all data？" << endl;
    cout << "1、Yes" << endl;
    cout << "2、No" <<endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        //打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            //删除堆区的每个职工对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                    this->m_EmpArray[i] = NULL;
                }
            }

            //删除堆区数组指针
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;
        }
        cout << "All data has been cleaned！" << endl;
    }

}