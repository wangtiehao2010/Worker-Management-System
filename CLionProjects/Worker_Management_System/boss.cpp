//
// Created by david on 02.11.20.
//

#include "boss.h"

Boss::Boss(int ID, string name, int DeptID)
{
    this->m_ID = ID;
    this->m_Name = name;
    this->m_DeptID = DeptID;
}

void Boss::showInfo()
{
    cout << "Staff code: " << this->m_ID;
    cout << "\tStaff name: " << this->m_Name;
    cout << "\tJob: " << this->getDeptName();
    cout << "\tResponsibility: Take charge of the company" << endl;
}

string Boss::getDeptName()
{
    return string("Boss");
}