// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <cassert>
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
TEST(test_simple_player_make_trump_basic) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Joe makes trump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = joe->make_trump(
    nine_spades,    // Upcard
    true,           // Joe is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete joe;
}

TEST(test_simple_player_make_trump_basic_not_dealer) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Joe makes trump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = joe->make_trump(
    nine_spades,    // Upcard
    false,           // Joe is not the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete joe;
}


//Test add and discard


//Test lead card


//Test play card

TEST_MAIN()
