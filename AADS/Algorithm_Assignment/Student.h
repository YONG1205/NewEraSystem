#pragma once
#include <iostream>
#include "StudentGrade.h"
#include "StudentGameHistory.h"
#include <vector>
#include <string>
using namespace std;

class Student{
    public:
    int ID, Ph;
    string clas, Gender, Name, Username, Password;
    vector<StudentGameHistory> History;
    vector<StudentGrade> Grades;
    string toString(){
        return to_string(ID) + ',' +Name+ ',' +Gender+ ',' +Username+ ',' +clas+ ','+to_string(Ph);
    }
};