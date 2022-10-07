// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

//Tests for deal one
// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
TEST(deal_one_basic){
    Pack pack;
    Card currentCard;

    for(int i = 0; i < 10; ++i){
        currentCard = pack.deal_one();
    }

    ASSERT_EQUAL(Card::RANK_QUEEN, currentCard.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, currentCard.get_suit());

}

//Tests for shuffle
// EFFECTS: Shuffles the Pack and resets the next index. This
//performs an in shuffle seven times.

//Tests for is pack empty
// EFFECTS: returns true if there are no more cards left in the pack
    
TEST(is_pack_empty_basic){
    Pack pack;
    Card currentCard;

    for(int i = 0; i < 24; ++i){
        currentCard = pack.deal_one();
    }
    
    assert(pack.empty());

}

TEST_MAIN()
