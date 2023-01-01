#pragma once
#include <iostream>
#include "PlayGame.h"
#include <ctime>
#include <string>
#include "DateTime.h"
#include <fstream>
#include <sstream>
using namespace std;

class StudentOperation{
    FileHandling file = FileHandling();
    Student* selstudent;
    bool exits = false;
    
    public: StudentOperation(Student selectedstudent){
        Studentmenu:
        selstudent = &selectedstudent;
        char choice;
        cout << "\n" << "Please select your operation" << endl;
        cout << "\n";
        cout << "1. View profile"<< endl;
        cout << "2. Update the profile" << endl;
        cout << "3. Play Game " << endl;
        cout << "4. View Game History" << endl;
        cout << "5. Search Game History" << endl;
        cout << "6. Remove Game History" << endl;
        cout << "7. Exit" << endl;
        cout << "User Enter: ";
        cin >> choice;
        cout << "\n" ;

        switch (choice){
            case '1':
                Vprofile();
                break;
            case '2':
                UpdatePro();
                break;
            case '3':
                Game();
                break;
            case '4':
                GameHis();
                break;
            case '5':
                SearchHis();
                break;
            case '6':
                RemoveHis();
                break;
            case '7':
                cout << "Exit successful";
                    exits = true;
                break;
            default:
            cout << "invalid value, Please try again"; 
                break;
            }
            if(exits != true){
                goto Studentmenu;
            }
        }

        void Vprofile(){ //find the latest year of semester
            StudentGrade latest = StudentGrade();
            for(StudentGrade sg :selstudent->Grades){
                if(sg.year>=latest.year){
                    if (sg.Semester>latest.Semester){
                        latest = sg;
                    }
                }
            }

            cout << "---------------------------------------------------------------" << endl;
            cout << "Name: " << selstudent->Name<< endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Gender: " << selstudent->Gender << endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Username: " << selstudent->Username << endl ;
            cout << "---------------------------------------------------------------" << endl;
            cout << "ID: " << selstudent->ID << endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Class: " << selstudent->clas <<endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Latest Semester: " << "year " << latest.year << " Sem " <<latest.Semester <<endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Latest Grade: " << latest.Grade <<endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << "Phone Number: " << selstudent->Ph << endl;
            cout << "---------------------------------------------------------------" << endl;
        }

        void UpdatePro(){
            updatepro:
            string inforselect;

            cout << "1. Password" << endl;
            cout << "2. Phone Number" << endl; 
            cout << "Enter the information that you want to update: " << endl;
            cin >> inforselect;
            int sel = stoi(inforselect);
            
            switch (sel){
            case 1 :{
                cout << "Enter a new Password: ";
                cin >> selstudent->Password;
                file.DeleteFileRow(file.loginStudent,selstudent->ID);
                file.SaveToFile(file.loginStudent,to_string(selstudent->ID)+','+selstudent->Username+','+selstudent->Password);
                cout << "Update successful";
                string cx;
                cout << "\n"; 
                cout << "Press c to continue," << endl;
                cout <<"Or press X to exit." << endl; 
                cin >> cx;
                if (cx == "c"){
                    goto updatepro;
                }
                break;
            }

            case 2 :{
                cout << "Enter a Phone Number: ";
                cin >> selstudent->Ph;
                file.DeleteFileRow(file.student,selstudent->ID);
                file.SaveToFile(file.student,selstudent->toString());
                cout << "Update successful";
                string cx;
                cout << "\n"; 
                cout << "Press c to continue," << endl;
                cout <<"Or press X to exit." << endl; 
                cin >> cx;
                if (cx == "c"){
                    goto updatepro;
                }
                break;
            }
            default:
                cout << "invalid value, Please try again" << endl; 
                break;
            }
        }

        void Game(){
            game:
            games(); //Insert Game history 
            StudentGameHistory gamehistory = StudentGameHistory();
            gamehistory.ID = file.NewId(file.gamehistory);
            gamehistory.StudentID = selstudent->ID;
            gamehistory.result = result;
            gamehistory.playDateTime.Parse(time(0));
            selstudent->History.push_back(gamehistory);
            file.SaveToFile(file.gamehistory,gamehistory.save_to_string());
        }

        void GameHis(){
            cout << "---------------------------------------------------------------" << endl;
            for(StudentGameHistory h : selstudent->History){
            cout << "Game ID: " << h.ID << endl;
            cout << "result: " << h.result << endl;
            cout << "time: " << h.playDateTime.ToString() << endl ;
            cout << "---------------------------------------------------------------" << endl;
            } 
        }

        void SearchHis(){
            His:
            string search;
            cout << "Search play date [dd/mm/yyy] : ";
            cin >> search;
            if(selstudent->History.size() == 0){
                cout << "No history in this day, Please try again" << endl;
                return;
            }
            int i = 1;
            cout << "---------------------------------------------------------------" << endl;
            for(StudentGameHistory h : selstudent->History){
                if(h.playDateTime.GetDate() == search) {
                    cout << i << ". " << h.result << "\t" << h.playDateTime.ToString() << endl;
                    cout << "---------------------------------------------------------------" << endl;
                    i++;
                }
            }
            string cx;
            cout << "\n"; 
            cout << "Press c to continue," << endl;
            cout <<"Or press X to exit." << endl; 
            cout <<"User Enter: ";
            cin >> cx;
                if (cx == "c"){
                    goto His;
                }
        }

        void RemoveHis(){
            for (StudentGameHistory h:selstudent->History){
                file.DeleteFileRow(file.gamehistory,h.ID);
            }
            cout << "Remove successful" << endl;
        }
};