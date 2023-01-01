#include <iostream>
#include "DateTime.h"
#include "Admin.h"
#include "StudentOperation.h"
using namespace std;

int id;
string username,password;
string loginmember;
Student selectedstudent;

bool validateAdmin(){
    if(username == "admin"&& password == "admin"){
        cout << "\n" << "Admin Login Successful." << endl;
        return true;
    }
    
    return false;
}

bool validateStudent(){
    vector<vector<string>> rows;
    FileHandling file = FileHandling();
    rows = file.ReadFromFile(file.loginStudent);
    for(vector<string> row:rows){
        if(username == row[1]&&password==row[2]){
            cout << "\n" << "Login successful" << endl;
            for(Student s:file.GetAllStudents()){
                if(s.Username == username){
                    selectedstudent = s;
                }
            }

            return true;
        }
    }

    return false;
}
    
int main (){
login:
    char select;
    bool loginsucessful = false;
    cout << "Please Select: " << endl;
    cout << "1. Admin" << endl;
    cout << "2. Student" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> select ;
    switch (select){
    case '1':
    cout << "\nUsername: ";
    cin >> username ;
    cout << "Password: ";
    cin >> password ;
    if (validateAdmin()){
        Admin admin = Admin();
    }

    break;
        case '2':
        cout << "\nUsername: ";
        cin >> username ;
        cout << "Password: ";
        cin >> password ;       
        if(validateStudent()){
            StudentOperation student = StudentOperation(selectedstudent);
        }

        break;
        case '3':
        cout << "\nExit successful";
        exit(0);
        default:
        cout << "\nInvalid input"<< endl;
        break;
    }

    if(loginsucessful == false){
        cout << "\nLogin unsuccessful" << endl;
        goto login;
    }

    return 0;
}