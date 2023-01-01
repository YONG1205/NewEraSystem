#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

string input, result; 

string tolowercase(string loo){
    string i;
    for(int j=0;j<loo.size();j++){
    i += tolower(loo[j]);
    }

    return i;
} 

int games(){
    cout << "Welcome to Treasure Island!\n";
    cout << "Your mission is to find the treasure.\n";
    cout << "\nYou hit a fork in the road.";
    cout << "\nLeft or Right?";
    cout << "\nMake a choice : ";
    cin >> input;
    string i = tolowercase(input);
    if (i == "left"){
        goto sec;}
    else {
        cout << "Fall into a hole. Game Over.";
        result = "lose";
        return 0;
    }

    sec:
    cout << "\nYou are face a river";
    cout << "\nSwim over the river or wait for help";
    cout << "\nSwim or wait";
    cout << "\nMake a choice : ";
    cin >> input ;
    string s = tolowercase(input);
    if (s == "wait"){ 
        cout << "\nThe explorer rescued you and showed you 3 doors";
    }

    else{
        cout << "You get attacked by an angry trout. Game Over.";
        result = "lose";
        return 0;
    }

    cout << "\nWhich is a Red door, a Blue door and a Yellow door";
    cout << "\nRed or Blue or Yellow";
    cout << "\nMake a choice : ";
    cin >> input;
    string y = tolowercase(input);
    if (y == "yellow"){ 
        cout << "You win";
        result = "win";
        return 0;
    }

    else if (y == "red"){
        cout << "You burned by fire. Game Over.";
        result = "lose";
        return 0; 
    }

    else if (y == "blue"){
        cout << "You eaten by beats. Game Over.";
        result = "lose";
        return 0;
    }

    else {
        cout << "Game Over";
        result = "lose";
        return 0;
    } 
    return 0;
}