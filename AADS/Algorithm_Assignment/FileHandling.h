#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Student.h"
using namespace std;

class FileHandling{
    public:
    const string loginStudent = "LoginStudent.csv";
    const string student = "student.csv";
    const string studentgrade = "studentGrade.csv";
    const string gamehistory = "studentGameHistory.csv";
    
    vector<vector<string>> ReadFromFile(string fileName){
        fstream fin;
        fin.open(fileName, ios::in);
        vector<vector<string>> rows;
        string line;//read data from file
        while (getline(fin,line)){
            vector<string> row;
            string word;
            stringstream s(line);
            while (getline(s, word, ',')) {
                row.push_back(word);
            }
            rows.push_back(row);
        }
        fin.close();
        return rows;
    }

    void SaveToFile(string fileName,string dataRow){
        fstream fout;
        fout.open(fileName, ios::out | ios::app); //write data to file
        fout << dataRow << "\n";
        fout.close();
    }

    void UpdateFile(string fileName, vector<string> dataRows){
        fstream fout; //create new file , if file exited, delete the content in the file
        fout.open(fileName,ios::trunc|ios::out);
        for(string data : dataRows){
            fout << data << "\n";
        } // close the file path after datas are inserted
        fout.close();
    } 

	void UpdateToFile(string fileName,vector<string> rowData){ //Update Operation //update range data
		fstream fout; //use trunc which will clear previous data after open the file
		fout.open(fileName, ios::trunc | ios::out); //write to file
		for (string r : rowData) {
			fout << r << "\n";
		}
		fout.close();
	}

	void DeleteFileRow(string fileName, int id) {  //Delete Operation
		vector<vector<string>> rows = ReadFromFile(fileName);
		for (int i = 0; i < rows.size();i++) { //fins the match id and delete it from vector
			if (stoi(rows[i][0]) == id) {
				rows.erase(rows.begin()+i);
			}
		}

		vector<string> rowData; //expect the specific row has been deleted and convert multi-demensional vector to single vector
		for (vector<string> r : rows) {
			string line = "";
			for (int i = 0; i < r.size();i++) {
				line += r[i];
				line += (i==r.size()-1) ? "" : ",";
			}
			rowData.push_back(line);
		}
		UpdateToFile(fileName, rowData); //Update to file
	}

    int NewId(string file){ //find the last id and incretmented it to get a new id 
        int maxId = 0;
        for(vector<string> row:ReadFromFile(file)){
            if(stoi(row[0])>maxId){
                maxId = stoi(row[0]);
            }
        }
        return maxId+1;
    }

    vector<Student> GetAllStudents(){     // Read all student from csv file and including their grades and game history
        vector<vector<string>> rows = ReadFromFile(student);
        vector<Student> output;
        for(vector<string> r:rows){
            Student s = Student(); //instansiate
            s.ID = stoi(r[0]);
            s.Name = r[1];
            s.Gender = r[2];
            s.Username = r[3];
            s.clas = r[4];
            s.Ph = stoi(r[5]);
            s.Password = GetPassword_byUsername(s.Username);
            s.Grades = GetGrade_byStudent(s.ID); //get student grades
            s.History = GetHistory_byStudent(s.ID);
            output.push_back(s);
        }
        return output;
    }

    string GetPassword_byUsername(string userName){
        vector<vector<string>> login = ReadFromFile(loginStudent);
        string output;
            for(vector<string> r:login){
                if(r[1] == userName){
                   output = r[2];
                }
            }
        return output;
    }

    vector<StudentGrade> GetGrade_byStudent(int id){
        vector<vector<string>> rows = ReadFromFile(studentgrade);
        vector<StudentGrade> output;
        for(vector<string> r:rows){
            if(stoi(r[1]) == id){
                StudentGrade g = StudentGrade();
                g.ID = stoi(r[0]);
                g.StudentId = stoi(r[1]);
                g.year = stoi(r[2]);
                g.Semester = stoi(r[3]);
                g.Grade = stod(r[4]);
                output.push_back(g);
            }
        }
        return output;
    }

    vector<StudentGameHistory> GetHistory_byStudent(int studentid){
        vector<vector<string>> row = ReadFromFile(gamehistory);
        vector<StudentGameHistory> output;
        for(vector<string> r:row){
            if(stoi(r[1]) == studentid){
                StudentGameHistory h = StudentGameHistory();
                h.ID = stoi(r[0]);
                h.StudentID = stoi(r[1]);
                h.result = r[2];
                h.playDateTime = DateTime(r[3]);
                output.push_back(h);
            }
        }
        return output;
    }
};