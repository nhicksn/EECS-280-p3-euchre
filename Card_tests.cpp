// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

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

//Tests for Face or Ace
//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)

//Tests for is Right Bower
//EFFECTS Returns true if card is the Jack of the trump suit

//Tests for is Left Bower
//EFFECTS Returns true if card is the Jack of the next suit

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


//Tests Card Less suit led
//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.

TEST_MAIN()
