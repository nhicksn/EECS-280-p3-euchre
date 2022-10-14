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

class Game {
private:
    vector<Player *> players;
    Pack deck;
    int winPoints;
    Card upcard;
    int orderUpIndex;
    // team one is players 0 and 2
    int team1TotalScore;
    // team two is players 1 and 3
    int team2TotalScore;
    int handNum = 0;


    void deal(int dealerIndex) {
        cout << "Hand " << handNum << endl;
        cout << *players[dealerIndex] << " deals" << endl;
        int first = (dealerIndex + 1) % 4;
        for(int i = first; i < first + 4; i++) {
            if(i == first || i == first + 2) {
                for(int j = 0; j < 3; j++) {
                    Card c = this->deck.deal_one();
                    players[i % 4]->add_card(c);
                }
            }
            else {
                for(int j = 0; j < 2; j++) {
                    Card c = this->deck.deal_one();
                    players[i % 4]->add_card(c);
                }
            }
        }
        for(int i = first; i < first + 4; i++) {
            if(i == first || i == first + 2) {
                for(int j = 0; j < 2; j++) {
                    Card c = this->deck.deal_one();
                    players[i % 4]->add_card(c);
                }
            }
            else {
                for(int j = 0; j < 3; j++) {
                    Card c = this->deck.deal_one();
                    players[i % 4]->add_card(c);
                }
            }
        }
        this->upcard = this->deck.deal_one();
        cout << upcard << " turned up" << endl;
        handNum++;
    }

    void make_trump(int indexDealer, string orderUpSuit) {
        bool done = false;
        int first = (indexDealer + 1) % 4;
        for(int i = 1; i < 3; i++) {
            for(int j = first; j < first + 4; j++) {
                int z = j % 4;
                if(z == indexDealer) {
                    done = players[z]->make_trump(this->upcard, true, i, orderUpSuit);
                }
                else {
                    done = players[z]->make_trump(this->upcard, false, i, orderUpSuit);
                }
                if(done == true) {
                    players[indexDealer]->add_and_discard(this->upcard);
                    orderUpIndex = z;
                    return;
                }
            }            
        }
        return;
    }
    void play_hand(int indexDealer) {
        int lead = (indexDealer + 1) % 4;
        int team1Score = 0;
        int team1Wins = 0;
        int team2Score = 0;
        int team2Wins = 0;
        string trump = upcard.get_suit();
        for(int i = 0; i < 5; i++) {
            Card leadCard = players[lead]->lead_card(trump);
            Card card1 = players[(lead + 1) % 4]->play_card(leadCard, trump);
            Card card2 = players[(lead + 2) % 4]->play_card(leadCard, trump);
            Card card3 = players[(lead + 3) % 4]->play_card(leadCard, trump);
            Card highestCard = leadCard;
            if(Card_less(highestCard, card1, trump)) {
                highestCard = card1;
                lead = (lead + 1) % 4;
            }
            if(Card_less(highestCard, card2, trump)) {
                highestCard = card2;
                lead = (lead + 2) % 4;
            }
            if(Card_less(highestCard, card3, trump)) {
                highestCard = card3;
                lead = (lead + 3) % 4;
            }
            if(lead == 0 || lead == 2) {
                team1Wins++;
            }
            else if(lead == 1 || lead == 3) {
                team2Wins++;
            }
        }
        if(team1Wins >= 3) {
            if(team1Wins == 5) {
                team1Score += 2;
            }
            else {
                if(orderUpIndex == 1 || orderUpIndex == 3) {
                    team1Score += 2;
                }
                else {
                    team1Score += 1;
                }
            }
        }
        if(team2Wins >= 3) {
            if(team2Wins == 5) {
                team2Score += 2;
            }
            else {
                if(orderUpIndex == 0 || orderUpIndex == 2) {
                    team2Score += 2;
                }
                else {
                    team2Score += 1;
                }
            }
        }
        team1TotalScore += team1Score;
        team2TotalScore += team2Score;
    }

public:
    Game(vector<Player *> playersIn, Pack deckIn, int winPointsIn) {
        this->players = playersIn;
        this->deck = deckIn;
        this->winPoints = winPointsIn;
        this->team1TotalScore = 0;
        this->team2TotalScore = 0;
    }

    void play(string shuffleToggle, ifstream &pack) {
        // first we need to shuffle or reset the deck
        if(shuffleToggle == "shuffle") {
            this->deck.shuffle();
        }
        else {
            Pack deck(pack);
        }
        bool playBool = true;
        int dealerIndex = 0;
        string orderUpSuit;
        while(playBool == true) {
            deal(dealerIndex);
            make_trump(dealerIndex, orderUpSuit);
            play_hand(dealerIndex);
            if(this->team1TotalScore >= this->winPoints) {
                playBool = false;
                cout << *players[0] << " and " << *players[2] << " win!" << endl;
            }
            else if(this->team2TotalScore >= this->winPoints) {
                playBool = false;
                cout << *players[1] << " and " << *players[3] << " win!" << endl;
            }
            dealerIndex++;
        }
    }
};

int main(int argc, char *argv[]) {

    // argv 1: pack.in
    string pack_filename = (argv[1]);

    // argv 2: points to win game -- can be between 1 and 100 inclusive
    int pointsToWin = atoi(argv[3]);

    if (pointsToWin < 1 || pointsToWin > 100) {
        cout << "1 Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    }

    // argv 3: shuffle toggle, use "noshuffle" to turn off shuffling
    string shuffleToggle = (argv[2]);

    if (shuffleToggle != "shuffle" && shuffleToggle != "noshuffle") {
        cout << "2 Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    }

    // players may only be human or simple
    // argv 4-5: name and type of player 0
    string playerZeroName = (argv[4]);
    string playerZeroType = (argv[5]);

    // argv 6-7: name and type of player 1
    string playerOneName = (argv[6]);
    string playerOneType = (argv[7]);

    // argv 8-9: name and type of player 2
    string playerTwoName = (argv[8]);
    string playerTwoType = (argv[9]);

    // argv 10-11: name and type of player 3
    string playerThreeName = (argv[10]);
    string playerThreeType = (argv[11]);

    if ((playerZeroType != "Simple" && playerZeroType != "Human") || (playerOneType != 
        "Simple" && playerOneType != "Human") || (playerTwoType != "Simple" && 
        playerTwoType != "Human") || (playerThreeType != "Simple" && 
        playerThreeType != "Human")) {
        cout << "3 Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    }
    Player* playerZero = Player_factory(playerZeroName, playerZeroType);
    Player* playerOne = Player_factory(playerOneName, playerOneType);
    Player* playerTwo = Player_factory(playerTwoName, playerTwoType);
    Player* playerThree = Player_factory(playerThreeName, playerThreeType);
    vector<Player*> players= {playerZero, playerOne, playerTwo, playerThree};

    // read in input file
    ifstream fin;
    fin.open(pack_filename);

    // check for error
    if (!fin.is_open()) {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }
    Pack deck(fin);
    Game game(players, deck, pointsToWin);
    game.play(shuffleToggle, fin);
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }  
}

