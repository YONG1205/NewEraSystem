#include <iostream>
using namespace std;

int main(){
    string a, d, e;
    char c;

    a:
    cout << "Welcome to Treasure Island. \nYour mission is to find the treasure.\n";
    cout << "left or right? ";
    cin >> a;
    if (a != "left" && a != "Left" ){
        cout << "Fall into a hole. \nGame over.\n";
        d:
        cout << "Do you want to exit the game? (Y or N) ";
        cin >> c;
        if (c == 'Y' || c == 'y'){
            cout << "GoodBye!";
            return 0;
        }
        else
        goto a;
    }
    else
    cout << "swim or wait ";
    cin >> d;
    if (d != "wait" && d != "Wait"){
        cout << "Attacked by trout. \nGame over.\n";
        goto d;
    }
    else 
    cout << "Which door? (Red, Blue or Yellow) ";
    cin >> e;
    if(e == "Yellow" || e == "yellow"){
        cout << "You win!\n";
        goto d;
    }
    else
    if(e == "Red" || e == "red"){
        cout << "Burned by fire. \nGame over.\n";
        goto d;
    }
    else 
    if(e == "Blue" || e == "blue"){
        cout << "Eaten by beats. \nGame over.\n";
        goto d;
    }
    else
    cout <<"Game over.";
    goto d;
}