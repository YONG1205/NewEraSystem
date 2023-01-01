#include <iostream>
using namespace std;

int main(){
    string Grade[12] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "D+", "D", "E", "F"};
    string Marks[12] = {"85%-100%", "80%-84%" ,"75%-79%", "70%-74%", "65%-69%", "60%-64%",
    "55%-59%", "50%-54%", "45%-49%", "40%-44%", " 30-39%", "  0-29%"};
    string GradePoints[12] = {"4.00", " 4.00", " 3.67", " 3.33", " 3.00", " 2.67", " 2.33", " 2.00", " 1.67", " 1.33", " 1.00", " 0.00"};
    string Remarks[12] = {"         Outstanding", "          Excellent", "           Good", "               ", 
    "        Satisfactory", "                    ", "           Pass", "               ",
    "Sufficient for the award of credit", "                                  ", "           Fail", "               "};
    int a;
    
    cout << "Grade\t  Marks\t  Grade points\t           Remarks\t\n";
    for(a=0; a<12; a++)
    cout <<" " << Grade[a] << "\t" << Marks[a] << "     " << GradePoints[a] << "\t" << Remarks[a] << "\n";
}
