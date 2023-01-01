#include <iostream>
using namespace std;

class StudentGrade{
    public:
    int ID, StudentId, Semester, year;
    double Grade;
    string toString(){
        return to_string(ID) + ','+to_string(StudentId)+','+to_string(year)+','+to_string(Semester)+','
        +to_string(Grade);
    }
};