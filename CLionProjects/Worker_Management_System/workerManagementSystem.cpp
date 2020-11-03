//
// Created by david on 02.11.20.
//

#include <iostream>
using namespace std;
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


int main()
{
//    test();
    workerManager wm;
    int choice = 0;
    while (true)
    {
        //展示菜单
        wm.Show_Menu();
        cout << "Please enter your choice: " << endl;
        cin >> choice;

        switch (choice)
        {
            case 0: //退出系统
                wm.exitSystem();
                break;
            case 1: //添加职工
                wm.Add_Emp();
                break;
            case 2: //显示职工
                wm.show_Emp();
                break;
            case 3: //删除职工
                wm.del_Emp();
                break;
            case 4: //修改职工
                wm.mod_Emp();
                break;
            case 5: //查找职工
                wm.find_Emp();
                break;
            case 6: //排序职工
                wm.sort_Emp();
                break;
            case 7: //清空文件
                wm.clean_File();
                break;
            default:
                system("clear");
                break;
        }
    }

    return 0;
}