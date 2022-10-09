// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;


//Test get name
TEST(test_player_get_name_simple) {
    Player * noah = Player_factory("Noah", "Simple");
    ASSERT_EQUAL("Noah", noah->get_name());

    delete noah; 
}

TEST(test_player_get_name_human) {
    Player * noah = Player_factory("Noah", "Human");
    ASSERT_EQUAL("Noah", noah->get_name());

    delete noah; 
}

//Test get card
//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand

//Test make trump
//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
TEST(test_player_make_trump_basic) {
    Player * noah = Player_factory("Noah", "Simple");
    Card upcard(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    bool is_dealer = false;
    int round = 1;
    std::string order_up_suit = "Hearts";
    
    //simple player wants to make trump hearts, return true
    assert(noah->make_trump(upcard, is_dealer, round, order_up_suit));

    delete noah; 
}


//Test add and discard


//Test lead card


//Test play card

TEST_MAIN()
