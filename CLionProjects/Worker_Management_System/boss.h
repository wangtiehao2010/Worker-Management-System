//
// Created by david on 02.11.20.
//

#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

//老板类
class Boss: public Worker
{
public:

    //构造函数
    Boss(int ID, string name, int DeptID);

    //显示个人信息
    virtual void showInfo();

    //获取职工岗位名称
    virtual string getDeptName();
};
