#pragma once
#include <iostream>
#include <string>
using namespace std;

class StudentGameHistory{
    public:
    int ID, StudentID;
    string result;
    DateTime playDateTime;
    string save_to_string(){
        return to_string(ID) + ','+to_string(StudentID)+','+result+','+playDateTime.ToString();
    }
};