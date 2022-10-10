// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>

using namespace std;

//Test ctor
TEST(test_simple_ctor) {
  Player * bob = Player_factory("Bob", "Simple");
  ASSERT_EQUAL("Bob", bob->get_name());
  delete bob;
}

TEST(test_human_ctor) {
  Player * bob = Player_factory("Bob", "Human");
  ASSERT_EQUAL("Bob", bob->get_name());
  delete bob;
}

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

//Test add card
//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
TEST(test_add_card) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  Card c = bob->play_card(Card(Card()), Card::SUIT_SPADES);
  ASSERT_EQUAL(c, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_add_card_twice) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));

  Card c = bob->play_card(Card(Card()), Card::SUIT_SPADES);
  Card c2 = bob->play_card(Card(Card()), Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(c, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  ASSERT_EQUAL(c2, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}

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

TEST(test_simple_make_trump_false) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Joe makes trump
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = "Spades";
  bool orderup = joe->make_trump(
    nine_diamonds,    // Upcard
    true,           // Joe is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(!orderup);
  ASSERT_EQUAL(trump, "Spades");

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

TEST(test_simple_player_make_trump_round_2_not_dealer) {
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
    2,              // Second Round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(!orderup);

  delete joe;
}

TEST(test_simple_player_make_trump_round_2_dealer) {
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
    true,           // Joe is the dealer
    2,              // Second Round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete joe;
}

TEST(test_simple_player_make_trump_round_2_not_dealer_has_opposite) {
  // Joe's hand
  Player * joe = Player_factory("Joe", "Simple");
  joe->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  joe->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS)); //has opposite

  // Joe makes trump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = joe->make_trump(
    nine_spades,    // Upcard
    false,           // Joe is not the dealer
    2,              // Second Round
    trump           // Suit ordered up (if any)
  );

  // Verify Joe's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, "Clubs");

  delete joe;
}

//Test add and discard
TEST(add_and_discard_discard) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_and_discard(Card(Card::RANK_KING, Card::SUIT_SPADES));
  Card c = bob->play_card(Card(Card()), Card::SUIT_SPADES);
  ASSERT_EQUAL(c, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(add_and_discard_discard_all_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_and_discard(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  Card c1 = bob->play_card(Card(Card(Card::RANK_TWO, Card::SUIT_CLUBS)), Card::SUIT_CLUBS);
  Card c2 = bob->play_card(Card(Card(Card::RANK_TWO, Card::SUIT_CLUBS)), Card::SUIT_CLUBS);
  Card c3 = bob->play_card(Card(Card(Card::RANK_TWO, Card::SUIT_CLUBS)), Card::SUIT_CLUBS);
  Card c4 = bob->play_card(Card(Card(Card::RANK_TWO, Card::SUIT_CLUBS)), Card::SUIT_CLUBS);
  Card c5 = bob->play_card(Card(Card(Card::RANK_TWO, Card::SUIT_CLUBS)), Card::SUIT_CLUBS);
  ASSERT_EQUAL(c1, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  ASSERT_EQUAL(c2, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  ASSERT_EQUAL(c3, Card(Card::RANK_KING, Card::SUIT_CLUBS));
  ASSERT_EQUAL(c4, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  ASSERT_EQUAL(c5, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  delete bob;
}

TEST(add_and_discard_same) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_and_discard(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  Card c = bob->play_card(Card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)), Card::SUIT_SPADES);
  ASSERT_EQUAL(c, Card(Card::RANK_ACE, Card::SUIT_SPADES));
  delete bob;
}

TEST(add_and_discard_add) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_and_discard(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  Card c = bob->play_card(Card(Card()), Card::SUIT_SPADES);
  ASSERT_EQUAL(c, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  delete bob;
}

//Test lead card
TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_all_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_one_trump_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_one_not_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, ace_hearts); //check led card

  delete bob;
}

//Test play card
TEST(test_simple_player_play_card_basic) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_has_one_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card_has_one_led_suit) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_has_two_led_suit) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_has_one_led_and_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Clubs"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_has_all_led_suit_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Diamonds"      // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_has_all_led_suit) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_play_all_cards) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played1 = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 
  Card card_played2 = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 
  Card card_played3 = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 
  Card card_played4 = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 
  Card card_played5 = bob->play_card(
    nine_spades,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 
  ASSERT_EQUAL(card_played1, Card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS)))
  ASSERT_EQUAL(card_played2, Card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)))
  ASSERT_EQUAL(card_played3, Card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS)))
  ASSERT_EQUAL(card_played4, Card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS)))
  ASSERT_EQUAL(card_played5, Card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS)))
  delete bob;
}

//Test cout operator
TEST(test_simple_cout) {
  Player * bob = Player_factory("Bob", "Simple");
  ostringstream s; 

  s << bob->get_name();
  ostringstream test;
  test << "Bob";
  ASSERT_EQUAL(s.str(), test.str());
  delete bob;
}

TEST(test_human_cout) {
  Player * bob = Player_factory("Bob", "Human");
  ostringstream s;

  s << bob->get_name();
  ostringstream test;
  test << "Bob";
  ASSERT_EQUAL(s.str(), test.str());
  delete bob;
}

TEST_MAIN()
