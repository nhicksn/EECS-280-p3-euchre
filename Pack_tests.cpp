// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <cassert>

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

TEST(deal_one_last){
    Pack pack;
    Card currentCard;

    for(int i = 0; i < 24; ++i){
        currentCard = pack.deal_one();
    }

    ASSERT_EQUAL(Card::RANK_ACE, currentCard.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, currentCard.get_suit());

}

//Tests for shuffle
// EFFECTS: Shuffles the Pack and resets the next index. This
//performs an in shuffle seven times.

TEST(test_shuffle_basic){
    Pack pack;
    Card currentCard;

    pack.shuffle();

    for(int i = 0; i < 2; ++i){
        currentCard = pack.deal_one();
    }

    cout << currentCard.get_rank() << " " << currentCard.get_suit();
    ASSERT_EQUAL(Card::RANK_JACK, currentCard.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, currentCard.get_suit());

}

TEST(test_shuffle_last_card){
    Pack pack;
    Card currentCard;

    pack.shuffle();

    for(int i = 0; i < 24; ++i){
        currentCard = pack.deal_one();
    }

    cout << currentCard.get_rank() << " " << currentCard.get_suit();
    ASSERT_EQUAL(Card::RANK_TEN, currentCard.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, currentCard.get_suit());

}

TEST(test_shuffle_first_ten){
    //brute force approach but it works ig

    Pack pack;
    Card currentCard;

    pack.shuffle();

    Card first = pack.deal_one();
    Card second = pack.deal_one();
    Card third = pack.deal_one();
    Card fourth = pack.deal_one();
    Card fifth = pack.deal_one();
    Card sixth = pack.deal_one();
    Card seventh = pack.deal_one();
    Card eigth = pack.deal_one();
    Card ninth = pack.deal_one();
    Card tenth = pack.deal_one();

    cout << first.get_rank() << first.get_suit();
    //1
    ASSERT_EQUAL(Card::RANK_KING, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, first.get_suit());
    //2
    ASSERT_EQUAL(Card::RANK_JACK, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, second.get_suit());
    //3
    ASSERT_EQUAL(Card::RANK_NINE, third.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, third.get_suit());
    //4
    ASSERT_EQUAL(Card::RANK_ACE, fourth.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, fourth.get_suit());
    //5
    ASSERT_EQUAL(Card::RANK_QUEEN, fifth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, fifth.get_suit());
    //6
    ASSERT_EQUAL(Card::RANK_TEN, sixth.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, sixth.get_suit());
    //7
    ASSERT_EQUAL(Card::RANK_NINE, seventh.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, seventh.get_suit());
    //8
    ASSERT_EQUAL(Card::RANK_KING, eigth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, eigth.get_suit());
    //9
    ASSERT_EQUAL(Card::RANK_JACK, ninth.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, ninth.get_suit());
    //10
    ASSERT_EQUAL(Card::RANK_TEN, tenth.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, tenth.get_suit());

}

TEST(test_shuffle_twice){
    //brute force approach but it works ig

    Pack pack;
    Card currentCard;

    pack.shuffle();
    pack.shuffle();

    for(int i = 0; i < 14; ++i){
        currentCard = pack.deal_one();
    }

    Card first = pack.deal_one();
    Card second = pack.deal_one();
    Card third = pack.deal_one();
    Card fourth = pack.deal_one();
    Card fifth = pack.deal_one();
    Card sixth = pack.deal_one();
    Card seventh = pack.deal_one();
    Card eigth = pack.deal_one();
    Card ninth = pack.deal_one();
    Card tenth = pack.deal_one();

    cout << first.get_rank() << first.get_suit();
    //1
    ASSERT_EQUAL(Card::RANK_QUEEN, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, first.get_suit());
    //2
    ASSERT_EQUAL(Card::RANK_ACE, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, second.get_suit());
    //3
    ASSERT_EQUAL(Card::RANK_NINE, third.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, third.get_suit());
    //4
    ASSERT_EQUAL(Card::RANK_TEN, fourth.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, fourth.get_suit());
    //5
    ASSERT_EQUAL(Card::RANK_QUEEN, fifth.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, fifth.get_suit());
    //6
    ASSERT_EQUAL(Card::RANK_KING, sixth.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, sixth.get_suit());
    //7
    ASSERT_EQUAL(Card::RANK_NINE, seventh.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, seventh.get_suit());
    //8
    ASSERT_EQUAL(Card::RANK_TEN, eigth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, eigth.get_suit());
    //9
    ASSERT_EQUAL(Card::RANK_QUEEN, ninth.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, ninth.get_suit());
    //10
    ASSERT_EQUAL(Card::RANK_KING, tenth.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, tenth.get_suit());

}

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

TEST(is_pack_empty_not_empty){
    Pack pack;
    Card currentCard;

    for(int i = 0; i < 10; ++i){
        currentCard = pack.deal_one();
    }
    assert(!pack.empty());
}


TEST_MAIN()
