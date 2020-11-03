//
// Created by david on 02.11.20.
//

#include "manager.h"

Manager::Manager(int ID, string name, int DeptID)
{
    this->m_ID = ID;
    this->m_Name = name;
    this->m_DeptID = DeptID;
}

void Manager::showInfo()
{
    cout << "Staff code: " << this->m_ID;
    cout << "\tStaff name: " << this->m_Name;
    cout << "\tJob: " << this->getDeptName();
    cout << "\tResponsibility: Complete the tasks assigned by the boss and send tasks to general staff" << endl;
}

string Manager::getDeptName()
{
    return string("Manager");
}
