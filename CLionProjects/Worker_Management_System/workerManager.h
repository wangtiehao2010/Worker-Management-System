//
// Created by david on 02.11.20.
//
#pragma once

#include <iostream>
using namespace std;
#include "worker.h"
#include <fstream>
#define FILENAME "empFile.txt"

class workerManager
{
public:

    //构造函数
    workerManager();

    //显示菜单
    void Show_Menu();

    //析构函数
    ~workerManager();

    //退出函数
    void exitSystem();

    //记录文件中的人数个数
    int m_EmpNum;

    //员工数组的指针
    Worker ** m_EmpArray;

    //增加职工
    void Add_Emp();

    //保存文件
    void save();

    //标志文件是否为空
    bool m_FileIsEmpty;

    //统计人数
    int get_EmpNum();

    //初始化员工
    void init_Emp();

    //显示职工
    void show_Emp();

    //删除员工
    void del_Emp();

    //按照职工编号判断该职工是否存在，若存在返回职工在数组中的位置，否则返回-1
    int isExist(int id);

    //修改职工
    void mod_Emp();

    //查找职工
    void find_Emp();

    //排序员工
    void sort_Emp();

    //清空文件
    void clean_File();

};

