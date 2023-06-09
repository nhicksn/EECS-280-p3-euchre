// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <cassert>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_default_card_ctor) {
    Card c;
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TWO);
}

//Tests for get rank
//EFFECTS Returns the rank

TEST(get_rank_basic) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_NINE, c.get_rank());
}

TEST(get_rank_incorrect) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_NOT_EQUAL(Card::RANK_TWO, c.get_rank());
}

//Tests for get suit
//EFFECTS Returns the suit.  Does not consider trump.

TEST(get_suit_basic) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());
}

TEST(get_suit_incorrect) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_NOT_EQUAL(Card::SUIT_CLUBS, c.get_suit());
}

//Tests for get suit (Trump)
//REQUIRES trump is a valid suit
//EFFECTS Returns the suit

TEST(get_suit_trump) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    std::string trump = "Hearts";

    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit(trump));
}

TEST(get_suit_trump_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    std::string trump = "Spades";

    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit(trump));
}

//Tests for Face or Ace
//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)

TEST(face_or_ace_king) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);

    assert(c.is_face_or_ace());

}

TEST(face_or_ace_ace) {
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    assert(c.is_face_or_ace());

}

TEST(face_or_ace_not_either) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    assert(!c.is_face_or_ace());

}

//Tests for is Right Bower
//EFFECTS Returns true if card is the Jack of the trump suit

TEST(is_right_bower_basic) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    std::string trump = "Diamonds";
    assert(c.is_right_bower(trump));

}

TEST(is_right_bower_wrong_suit) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);

    std::string trump = "Diamonds";
    assert(!c.is_right_bower(trump));

}

TEST(is_right_bower_wrong_rank) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);

    std::string trump = "Diamonds";
    assert(!c.is_right_bower(trump));

}

//Tests for is Left Bower
//EFFECTS Returns true if card is the Jack of the next suit

TEST(is_left_bower_basic_red) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);

    std::string trump = "Diamonds";
    assert(c.is_left_bower(trump));

}

TEST(is_left_bower_basic_black) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

    std::string trump = "Spades";
    assert(c.is_left_bower(trump));

}

TEST(is_left_bower_same_suit) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

    std::string trump = "Clubs";
    assert(!c.is_left_bower(trump));

}

TEST(is_left_bower_diff_rank) {
    Card c(Card::RANK_KING, Card::SUIT_CLUBS);

    std::string trump = "Spades";
    assert(!c.is_left_bower(trump));

}

//Tests Card is Trump
//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.

TEST(card_is_trump_basic) {
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);

    std::string trump = "Hearts";
    assert(c.is_trump(trump));

}

TEST(card_is_trump_not_face) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    std::string trump = "Diamonds";
    assert(c.is_trump(trump));

}

TEST(card_is_trump_not_trump) {
    Card c(Card::RANK_NINE, Card::SUIT_CLUBS);

    std::string trump = "Spades";
    assert(!c.is_trump(trump));

}

TEST(card_is_trump_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);

    std::string trump = "Hearts";
    assert(c.is_trump(trump));

}

// Tests overload operators
//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.

TEST(card1_less_than_card2) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_HEARTS);

    assert(c1 < c2);
}

TEST(card1_less_than_or_equal_to_card2) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_SPADES);

    assert(c1 <= c2);
}

TEST(card2_greater_than_card1) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_HEARTS);

    assert(c2 > c1);
}

TEST(card1_greater_than_or_equal_to_card2) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_SPADES);

    assert(c1 >= c2);
}

TEST(card1_equal_to_card2) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_SPADES);

    assert(c1 == c2);
}

TEST(card2_not_equal_to_card1) {
    Card c1(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c2(Card::RANK_TWO, Card::SUIT_HEARTS);

    assert(c2 != c1);
}

//Tests Suit Next
//EFFECTS returns the next suit, which is the suit of the same color

TEST(suit_next_basic_red){
    std::string suit = "Diamonds";
    std::string nextSuit = "Hearts";

    ASSERT_EQUAL(suit, Suit_next(nextSuit));

}

TEST(suit_next_basic_black){
    std::string suit = "Spades";
    std::string nextSuit = "Clubs";

    ASSERT_EQUAL(suit, Suit_next(nextSuit));

}

TEST(suit_next_not_equal){
    std::string suit = "Spades";
    std::string nextSuit = "Hearts";

    ASSERT_NOT_EQUAL(suit, Suit_next(nextSuit));
    
}

//Test Card to Stream
//EFFECTS Prints Card to stream, for example "Two of Spades"

TEST(card_to_stream_basic) {
  Card c(Card::RANK_TWO, Card::SUIT_SPADES);
  ostringstream s; 

  s << c;
  ostringstream test;
  test << "Two of Spades";
  ASSERT_EQUAL(s.str(), test.str());
}

TEST(card_to_stream_face) {
  Card c(Card::RANK_KING, Card::SUIT_HEARTS);
  ostringstream s; 

  s << c;
  ostringstream test;
  test << "King of Hearts";
  ASSERT_EQUAL(s.str(), test.str());
}

//Tests Card Less
//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.

TEST(card_less_basic) {
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_NINE, Card::SUIT_HEARTS);
    
    std::string trump = "Hearts";

    assert(Card_less(a, b, trump));

}

TEST(card_less_both_are_trump) {
    Card a(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    std::string trump = "Diamonds";

    assert(Card_less(a, b, trump));

}

TEST(card_less_none_are_trump) {
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_NINE, Card::SUIT_HEARTS);
    
    std::string trump = "Clubs";

    assert(!Card_less(a, b, trump));

}

//Tests Card Less suit led
//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.

TEST(card_less_led_suit_basic) {
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card led(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    std::string trump = "Clubs";

    assert(Card_less(a, b, led, trump));

}

TEST(card_less_led_suit_is_trump) {
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card led(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    
    std::string trump = "Hearts";

    assert(Card_less(a, b, led, trump));

}

TEST(card_less_led_suit_all_diff_suits) {
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card led(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    
    std::string trump = "Spades";

    assert(!Card_less(a, b, led, trump));

}

TEST_MAIN()
