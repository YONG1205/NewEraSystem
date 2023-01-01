#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "FileHandling.h"
using namespace std;

class Admin{
    FileHandling file = FileHandling();
    bool exit = false;
    public: Admin(){
        Adminmenu:
        char select;
        cout << "\n" << "Please select your operation:" << endl;
        cout << "\n";
        cout << "1. Add New Student"<< endl;
        cout << "2. Add Information and Grade for Student " << endl;
        cout << "3. Update Student Information" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. View Student profile" << endl;
        cout << "6. View and search Student's Game History" << endl;
        cout << "7. Exit" << endl;
        cout << "User Enter: ";
        cin >> select;
        cout << "\n" ;

        switch (select){
        case '1':
            AddStudent();
            break;
        case '2':
            GradeStudent();
            break;
        case '3':
            UpdateInfor();
            break;
        case '4':
            DeleteInfor();
            break;
        case '5':
            StudentList();
            break;
        case '6':
            GameHistory();
            break;
        case '7':
        cout << "Exit successful";
            exit = true;
            break;
        default:
        cout << "invalid value, Please try again"; 
            break;
        }
        if(exit != true){
            goto Adminmenu;
        }
    }
    
    void AddStudent(){
        AddStudent:
        string stusername;
        cout << "\n" << "Student Name: ";
        cin >> stusername;
        Student newstudent = Student();
        newstudent.Name = stusername;
        vector<vector<string>> rows = file.ReadFromFile(file.student);
        newstudent.ID = file.NewId(file.student);
        newstudent.Username = stusername+to_string(newstudent.ID);
        file.SaveToFile(file.student, newstudent.toString());
        file.SaveToFile(file.loginStudent,to_string(newstudent.ID)+','+newstudent.Username+','+"123abc");
        cout << "Insert successful" << endl;
        string cx;
        cout << "\n"; 
        cout << "Enter c to continue add new student," << endl;
        cout <<"Or any alphabet other then c to back to operation menu." << endl; 
        cin >> cx;
        if (cx == "c"){
            goto AddStudent;
        } 
    }

    void GradeStudent(){
        gradestudent:
        string select; 
        int years,sem,stuid;
        double grade;

        cout << "Please select a student to update his/her Grade point average" << endl;
        vector<Student> students = file.GetAllStudents();
        Student selectedstudent;
        for(int i=0;i<students.size();i++){
            cout << i+1 << ". " << students[i].Name << endl;
        }
        cout << "Enter your choice: ";
        cin >> select;
        cout << "\n" ;
        selectedstudent = students[stoi(select)-1];
        cout << "Year: ";
        cin >> years;
        cout << "Semester : ";
        cin >> sem;
        cout << "Avarage Grade: ";
        cin >> grade; 
        StudentGrade newgrade = StudentGrade();
        newgrade.ID = file.NewId(file.studentgrade);
        newgrade.StudentId = selectedstudent.ID;
        newgrade.year = years;
        newgrade.Semester = sem;
        newgrade.Grade = grade; 
        file.SaveToFile(file.studentgrade, newgrade.toString());
        cout << "\nInsert successful";
        string cx;
        cout << "\n"; 
        cout << "Press c to continue add grade for student," << endl;
        cout <<"or any alphabet other then c to back to operation menu." << endl; 
        cin >> cx;
        if (cx == "c"){
            goto gradestudent;
        } 
    }
    
    void UpdateInfor(){
        updateinfor:
        string select; 
        string inforselect;
        cout << "Please select a student to update his/her information," << endl;
        vector<Student> students=file.GetAllStudents();
        Student* selectedstudent;
        for(int i=0;i<students.size();i++){
            cout << i+1 << ". " << students[i].Name << endl;
        }
        cout << "Enter your choice: ";
        cin >> select;
        cout << "\n" ;
        selectedstudent = &students[stoi(select)-1];
        menu:
        cout << "1. Name" << endl;
        cout << "2. Password" << endl;
        cout << "3. Grade" << endl; 
        cout << "4. Phone Number" << endl; 
        cout << "5. Gender" << endl;
        cout << "6. Class" << endl;
        cout << "7. Change student" << endl; 
        cout << "Enter the information that you want to update: ";
        cin >> inforselect;
        int sel = stoi(inforselect);
        switch (sel)
        {
        case 1 :{
            cout << "\nEnter a new name: ";
            cin >> selectedstudent->Name;
            vector<string> drs; // convert all student to string 
            for(Student s:students){
                drs.push_back(s.toString());
            }
            file.UpdateFile(file.student,drs);
            cout << "\nUpdate successful";
            string cx;
            cout << "\n"; 
            cout << "\nPress c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl; 
            cin >> cx;
            if (cx == "c"){
                goto menu;
            }
            break;
        }

        case 2 :{
            cout << "Enter a new Password: ";
            cin >> selectedstudent->Password;
            vector<string> drs;
            for(Student s:students){
                drs.push_back(to_string(s.ID)+','+s.Username+','+s.Password);
            }
            file.UpdateFile(file.loginStudent,drs);
            cout << "Update successful";
            string cx;
            cout << "\n"; 
            cout << "Press c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl;
            cin >> cx;
            if (cx == "c"){
                goto menu;
            }
            break;
        }

        case 3 :{
            StudentGrade latest = StudentGrade();  //find the latest year of semester
            if (selectedstudent->Grades.size() == 0){
                cout << "This student has no yet have any grade.";
                break;
            }
            for(StudentGrade sg :selectedstudent->Grades){
                if(sg.year>=latest.year){
                    if (sg.Semester>latest.Semester){
                        latest = sg;
                    }
                }
            }
            cout << "Update latest year of semester " << to_string(latest.year) << " semester " << to_string(latest.Semester) << endl;
            cout << "Enter a new Grade: ";  
            cin >> latest.Grade;            
            file.DeleteFileRow(file.studentgrade, latest.ID);
            file.SaveToFile(file.studentgrade,latest.toString());
            cout << "Update successful";
            string cx;
            cout << "\n"; 
            cout << "Press c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl; 
            cin >> cx;
            if (cx == "c"){ 
                goto menu;
            }
            break;
        }

        case 4 :{
            cout << "Enter a Phone Number: ";
            cin >> selectedstudent->Ph;
            vector<string> drs;
            for(Student s:students){
                drs.push_back(s.toString());
            }
            file.UpdateFile(file.student,drs);
            cout << "Update successful";
            string cx;
            cout << "\n"; 
            cout << "Press c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl;
            cin >> cx;
            if (cx == "c"){
                goto menu;
            }
            break;
        }

        case 5 :{
            cout << "Enter a Gender: ";
            cin >> selectedstudent->Gender;
            vector<string> drs;
            for(Student s:students){
                drs.push_back(s.toString());
            }
            file.UpdateFile(file.student,drs);
            cout << "Update successful";
            string cx;
            cout << "\n"; 
            cout << "Press c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl;
            cin >> cx;
            if (cx == "c"){
                goto menu;
            }
            break;
        }

        case 6 :{
            cout << "Enter a Class: ";
            cin >> selectedstudent->clas;
             vector<string> drs;
            for(Student s:students){
                drs.push_back(s.toString());
            }
            file.UpdateFile(file.student,drs);
            cout << "Update successful";
            string cx;
            cout << "\n"; 
            cout << "Press c to continue update information for student," << endl;
            cout <<"Or any alphabet other then c to back to operation menu." << endl;
            cin >> cx;
            if (cx == "c"){
                goto menu;
            }
            break;
        }

        case 7 :{
            goto updateinfor;
            break;
        }

        default:
        cout << "\ninvalid value, Please enter number between 1-7!\n" << endl; 
        goto menu;
            break;
        }
    }

    void DeleteInfor(){
        string select; 
        string inforselect;
        cout << "Select a student to remove from the list" << endl;
        vector<Student> students=file.GetAllStudents();
        Student* selectedstudent;
        for(int i=0;i<students.size();i++){
            cout << i+1 << ". " << students[i].Name << endl;
        }
        cout << "Enter your choice: ";
        cin >> select;
        cout << "\n" ;
        selectedstudent = &students[stoi(select)-1];
        file.DeleteFileRow(file.loginStudent,selectedstudent->ID);
        for(StudentGrade g:selectedstudent->Grades){
            file.DeleteFileRow(file.studentgrade,g.ID);
        }
        file.DeleteFileRow(file.student,selectedstudent->ID);
        cout << "Remove successful" << endl;
        
    }

    void StudentList(){
        studentlist:
        string select; 
        string inforselect;
        cout << "Choose a student to view their profile " << endl;
        vector<Student> students=file.GetAllStudents();
        Student* selectedstudent;
        cout << "---------------------------------------------------------------" << endl;
        for(int i=0;i<students.size();i++){
            cout << i+1 << ". " << students[i].Name << " ID:" << students[i].ID <<endl;
        }
        cout << "Enter your choice: ";
        cin >> select;
        cout << "---------------------------------------------------------------" << endl;
        cout << "\n" ;
        selectedstudent = &students[stoi(select)-1]; //find the latest year of semester
        StudentGrade latest = StudentGrade();
        for(StudentGrade sg :selectedstudent->Grades){
            if(sg.year>=latest.year){
                if (sg.Semester>latest.Semester){
                    latest = sg;
                }
            }
        }
        cout << "---------------------------------------------------------------" << endl;
        cout << "Name: " << selectedstudent->Name << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Gender: " << selectedstudent->Gender << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Username: " << selectedstudent->Username << endl ;
        cout << "---------------------------------------------------------------" << endl;
        cout << "ID: " << selectedstudent->ID << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Phone Number: " << selectedstudent->Ph << endl; 
        cout << "---------------------------------------------------------------" << endl;
        cout << "Class: " << selectedstudent->clas <<endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Latest Semester: " << latest.Semester <<endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "Latest Grade: " << latest.Grade <<endl;
        cout << "---------------------------------------------------------------" << endl;
        string cx;
        cout << "\n"; 
        cout << "Enter c to continue view student profile," << endl;
        cout <<"Or press any key other than c to exit." << endl; 
        cin >> cx;
        if (cx == "c"){
            goto studentlist;
        } 
    }

    void GameHistory(){
        gamehis:
        string select; 
        string inforselect;
        cout << "Choose a student to view their Game History " << endl;
        vector<Student> students=file.GetAllStudents();
        Student* selectedstudent;
        cout << "---------------------------------------------------------------" << endl;
        for(int i=0;i<students.size();i++){
            cout << i+1 << ". " << students[i].Name << " ID:" << students[i].ID <<endl;
        }
        cout << "\nEnter your choice: ";
        cin >> select;
        selectedstudent = &students[stoi(select)-1];
        cout << "\n---------------------------------------------------------------" << endl;
        int i = 1;
        for(StudentGameHistory h : selectedstudent->History){
            cout << i << ". " << h.result << "\t" << h.playDateTime.ToString() << endl;
            cout << "---------------------------------------------------------------" << endl;
            i++;     
        }
        string searchs;
        cout << "\nSearch play date [dd/mm/yyy] : ";
        cin >> searchs;
        int p = 1;
        cout << "---------------------------------------------------------------" << endl;
        int j = 1;
        for(StudentGameHistory h : selectedstudent->History){
            if(h.playDateTime.GetDate() == searchs) {
                cout << j << ". " << h.result << "\t" << h.playDateTime.ToString() << endl;
                cout << "---------------------------------------------------------------" << endl;
                j++;
            }
        } 
        string cx;
        cout << "\n"; 
        cout << "Press c to continue view student's game history," << endl;
        cout <<"Or press any key to exit." << endl; 
        cout <<"User Enter: "; 
        cin >> cx;
        if (cx == "c"){
            goto gamehis;
        }
    }
};