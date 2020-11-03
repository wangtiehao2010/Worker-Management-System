//
// Created by david on 02.11.20.
//

#include "employee.h"

Employee::Employee(int ID, string name, int DeptID)
{
    this->m_ID = ID;
    this->m_Name = name;
    this->m_DeptID = DeptID;
}

void Employee::showInfo()
{
      cout << "Staff code: " << this->m_ID;
      cout << "\tStaff name: " << this->m_Name;
      cout << "\tJob: " << this->getDeptName();
      cout << "\tResponsibility: Complete the tasks assigned by the boss " << endl;
}

string Employee::getDeptName()
{
    return string("General staff");
}