// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

int main(int argc, char *argv[]) {

    //argv 1: pack.in
    string pack_filename = (argv[1]);

    //argv 2: points to win game -- can be between 1 and 100 inclusive
    int pointsToWin = atoi(argv[2]);

    if(pointsToWin < 1 || pointsToWin > 100){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    }

    //argv 3: shuffle toggle, use "noshuffle" to turn off shuffling
    string shuffleToggle = (argv[3]);

    if(shuffleToggle != "shuffle" || shuffleToggle != "noshuffle"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    }

    //players may only be human or simple
    //argv 4-5: name and type of player 0
    string playerZeroName = (argv[4]);
    string playerZeroType = (argv[5]);

    //argv 6-7: name and type of player 1
    string playerOneName = (argv[6]);
    string playerOneType = (argv[7]);

    //argv 8-9: name and type of player 2
    string playerTwoName = (argv[8]);
    string playerTwoType = (argv[9]);

    //argv 10-11: name and type of player 3
    string playerThreeName = (argv[10]);
    string playerThreeType = (argv[11]);

    if(playerZeroName != "Simple" || playerZeroName != "Human" 
    || playerOneName != "Simple" || playerOneName != "Human" 
    || playerTwoName != "Simple" || playerTwoName != "Human"
    || playerThreeName != "Simple" || playerThreeName != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    }

    //read in input file
    ifstream fin;
    fin.open(pack_filename);

    //check for error
    if(!fin.is_open()){
         cout << "Error opening " << pack_filename << endl;
    return 1;
}


}

