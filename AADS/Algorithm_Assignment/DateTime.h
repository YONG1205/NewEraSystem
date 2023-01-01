#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

struct DateTime {
    int Year, Month, Day, Hour, Min, Sec;
    DateTime(){}
    DateTime(string line){
        Parse(line);
    }

    DateTime(time_t dt){
        Parse(dt);
    }

    string ToString() {
        string date, time;
        date = to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
        time = (Hour < 10) ? '0' + to_string(Hour) : to_string(Hour);
        time += ':';
        time += (Min < 10) ? '0' + to_string(Min) : to_string(Min);
        time += ':';
        time += (Sec < 10) ? '0' + to_string(Sec) : to_string(Sec);
        return date + ' ' + time;
    }

    string GetDate(){
        return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
    }

    void Parse(string line) {
        string word, element;
        vector<string> date;
        vector<string> time;
        stringstream ssLine(line);
        while (getline(ssLine, word, ' ')){
            stringstream ssWord(word);
            if (word.rfind('/') != string::npos){
                while (getline(ssWord, element, '/')){
                    date.push_back(element);
                }
            }

            else if (word.rfind(':') != string::npos) {
                while (getline(ssWord, element, ':')) {
                    time.push_back(element);
                }
            }
        }

        Day = stoi(date[0]);
        Month = stoi(date[1]);
        Year = stoi(date[2]);
        Hour = stoi(time[0]);
        Min = stoi(time[1]);
        Sec = stoi(time[2]);
    }

    void Parse(time_t dt) {
        tm* dateTime = localtime(&dt);
        Day = dateTime->tm_mday;
        Month = 1 + dateTime->tm_mon;
        Year = 1900 + dateTime->tm_year;
        Hour =  dateTime->tm_hour;
        Min =  dateTime->tm_min;
        Sec =  dateTime->tm_sec;
    }
};