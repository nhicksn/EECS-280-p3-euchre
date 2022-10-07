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

//Tests for get rank
//EFFECTS Returns the rank

TEST(get_rank_basic) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_NINE, c.get_rank());
}

//Tests for get suit
//EFFECTS Returns the suit.  Does not consider trump.

TEST(get_suit_basic) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());
}

//Tests for get suit (Trump)
//REQUIRES trump is a valid suit
//EFFECTS Returns the suit

TEST(get_suit_trump) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    std::string trump = "Hearts";

    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit(trump));
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

//Tests Suit Next
//EFFECTS returns the next suit, which is the suit of the same color

//Test Card to Stream
//EFFECTS Prints Card to stream, for example "Two of Spades"

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
