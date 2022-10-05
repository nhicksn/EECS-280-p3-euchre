// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    this->rank = RANK_TWO;
    this->suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    this->rank = rank_in;
    this->suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return this->rank;
    assert(false);
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return this->suit;
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
            || trump == SUIT_HEARTS || trump == SUIT_SPADES);
    if(this->suit == Suit_next(trump) && this->rank == RANK_JACK) {
        return trump;
    }
    else return this->suit;
    assert(false);
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
    if(this->rank == RANK_JACK || this->rank == RANK_QUEEN || 
    this->rank == RANK_KING || this->rank == RANK_ACE) {
        return true;
    }
    else return false;
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if(this->suit == trump && this->rank == RANK_JACK) {
        return true;
    }
    else return false;
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    std::string sameColor = Suit_next(trump);
    if(this->suit == sameColor && this->rank == RANK_JACK) {
        return true;
    }
    else return false;
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if(this->suit == trump) {
        return true;
    }
    else if(this->is_left_bower(trump)) {
        return true;
    }
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int indexLHS = 0;
    int indexRHS = 0;
    for(int i = 0; i < 13; i++) {
        if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            indexLHS = i;
        }
        else if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            indexRHS = i;
        }
    }
    if(indexLHS < indexRHS) return true;
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    if (lhs < rhs || lhs.get_rank() == rhs.get_rank()) {
        return true;
    }
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    if(!(lhs < rhs) && lhs.get_rank() != rhs.get_rank()) {
        return true;
    }
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    if(!(lhs < rhs)) {
        return true;
    }
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    if(lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else return false;
    assert(false);
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    if(!(lhs == rhs)) {
        return true;
    }
    else return false;
    assert(false);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    assert(suit == "Clubs" || suit == "Diamonds"
            || suit == "Hearts" || suit == "Spades");
    std::string sameColor;
    if(suit == "Diamonds") {
        sameColor = "Hearts";
    }
    else if(suit == "Hearts") {
        sameColor = "Diamonds";
    }
    else if(suit == "Spades") {
        sameColor = "Clubs";
    }
    else if(suit == "Clubs") {
        sameColor = "Spades";
    }
    return sameColor;
    assert(false);
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    assert(trump == "Clubs" || trump == "Diamonds"
            || trump == "Hearts" || trump == "Spades");
    if(!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if(a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if(a.is_trump(trump) && b.is_trump(trump)) {
        if(a.is_right_bower(trump)) return false;
        else if(b.is_right_bower(trump)) return true;
        else if(a.is_left_bower(trump) && !b.is_right_bower(trump)) return false;
        else if(b.is_left_bower(trump) && !a.is_right_bower(trump)) return true;
        if(a > b) return false;
        else if (b > a) return true;
    }
    else if(!a.is_trump(trump) && !b.is_trump(trump)) {
        if (a > b) return false;
        else if (b > a) return true;
    }
    if(a == b){
        return false;
    }
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    assert(trump == "Clubs" || trump == "Diamonds"
            || trump == "Hearts" || trump == "Spades");
    std::string ledSuit = led_card.get_suit();
    std::string ledRank = led_card.get_rank();
    std::string aSuit = a.get_suit();
    std::string bSuit = b.get_suit();
    std::string aRank = a.get_rank();
    std::string bRank = b.get_suit();
    if(a == b) return false;
    if(aSuit != ledSuit && bSuit == ledSuit && aSuit != trump) return true;
    assert(false);
}