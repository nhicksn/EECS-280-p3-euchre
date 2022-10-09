// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include "Player.h"
#include "Card.h"

Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  else if(strategy == "Human") {
    return new HumanPlayer(name);
  }
  // TODO: implement SimplePlayer and HumanPlayer
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}
std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer: public Player {
private:
  std::string name;
  std::array<Card, MAX_HAND_SIZE> hand;

public:
  SimplePlayer(const std::string &nameInput) {
    this->name = nameInput;
  }

  //EFFECTS returns player's name
  const std::string &get_name() const override {
    return this->name;
  }
  
  //EFFECTS returns player's hand
  const std::array<Card, MAX_HAND_SIZE> &get_hand() { //no override bc not base class
    return this->hand;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    for(int i = 0; i < MAX_HAND_SIZE; i++) {
      // Checks if the space is empty, then changes that spot to the new card
      // Breaks once a spot is found
      if(hand[i].get_rank() == "null") {
        hand[i] = c;
        break;
      }
    }
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump (const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
    assert(round == 1 || round == 2);
    int trumpCounter = 0;
    std::string upTrump = upcard.get_suit(order_up_suit);
    std::array<Card, MAX_HAND_SIZE> hand = this->hand;

    //NEEDS TO BE FIXED, confused on how this works
    //if round 1 and order suit and suit of upcard are equal then suit of upcard is trump
    if(round == 1) {
      for(int i = 0; i < MAX_HAND_SIZE; i++) {
        if(hand[i].get_suit(upTrump) == upTrump && hand[i].get_rank() == Card::RANK_JACK || 
        hand[i].get_rank() == Card::RANK_QUEEN || hand[i].get_rank() == Card::RANK_KING ||
        hand[i].get_rank() == Card::RANK_ACE) {
          trumpCounter++;
        }
      }
      if(trumpCounter >= 2) {
        order_up_suit = upTrump;
        return true;
      }
    }
    //if round 2, order up suit becomes trump
    if(round == 2) {
      trumpCounter = 0;
      std::string sameColor = Suit_next(upTrump);
      for(int i = 0; i < MAX_HAND_SIZE; i++) {
        if(hand[i].get_suit(sameColor) == sameColor && hand[i].get_rank() == Card::RANK_JACK || 
        hand[i].get_rank() == Card::RANK_QUEEN || hand[i].get_rank() == Card::RANK_KING ||
        hand[i].get_rank() == Card::RANK_ACE) {
          trumpCounter++;
        }
      }
      if(trumpCounter >= 1 | is_dealer == true) {
        order_up_suit = sameColor;
        return true;
      }
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    //checks if player has at least one card
    for(int i = 0; i < MAX_HAND_SIZE; ++i){
      if(hand[i].get_rank() != "null"); {
        break;
      }
      if(i == (MAX_HAND_SIZE-1) && hand[i].get_rank() == "null"){
        assert(false);
      }
    }
    std::array<Card, MAX_HAND_SIZE> hand = this->hand;
    std::string trump = upcard.get_suit();
    Card lowestCard = hand[0];
    int lowestIndex = 0;
    for(int i = 0; i < MAX_HAND_SIZE; i++) {
      if(hand[i] < lowestCard && hand[i].get_rank() != "null") {
        lowestCard = hand[i];
        lowestIndex = i;
      }
    }
    if(upcard < lowestCard) return;
    else if(upcard > lowestCard) hand[lowestIndex] = upcard;
  }

 //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override{
    for(int i = 0; i < MAX_HAND_SIZE; ++i){
      if(hand[i].get_rank() != "null"); {
        break;
      }
      if(i == (MAX_HAND_SIZE-1) && hand[i].get_rank() == "null"){
        assert(false);
      }
    }
    assert(trump == "Clubs" || trump == "Diamonds"
            || trump == "Hearts" || trump == "Spades");

    std::array<Card, MAX_HAND_SIZE> hand = this->hand;
    Card highestCard = hand[0];
    bool allTrump;
    int trumpCounter = 0;
    for(int i = 0; i < MAX_HAND_SIZE; i++) {
      if(hand[i].get_suit(trump) == trump) {
        trumpCounter++;
      }
    }
    if(trumpCounter == 5) allTrump = true;
    if(allTrump) {
      for(int i = 0; i < MAX_HAND_SIZE; i++) {
        if(hand[i] > highestCard && hand[i].get_rank() != "null") {
          highestCard = hand[i];
        }
      }
    }
    else if(!allTrump) {
      for(int i = 0; i < MAX_HAND_SIZE; i++) {
        if(hand[i] > highestCard && hand[i].get_rank() != "null" && hand[i].get_suit(trump) != trump) {
          highestCard = hand[i];
        }
      }
    }
    return highestCard;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
Card play_card(const Card &led_card, const std::string &trump) override{
  
  //checks if player has at least one card
  for(int i = 0; i < MAX_HAND_SIZE; ++i){
    if(hand[i].get_rank() != "null"); {
    break;
    }
    if(i == (MAX_HAND_SIZE-1) && hand[i].get_rank() == "null"){
      assert(false);
    }
  }
  //checks if trump is valid input
  assert(trump == "Clubs" || trump == "Diamonds"
               || trump == "Hearts" || trump == "Spades");
  bool canFollow   = false;
  std::array<Card, MAX_HAND_SIZE> hand = this->hand;
  std::string ledSuit = led_card.get_suit(trump);
  for(int i = 0; i < MAX_HAND_SIZE; i++) {
    if(hand[i].get_suit(trump) == ledSuit) {
      canFollow = true;
    }
  }
  Card highestCard = hand[0];
  Card lowestCard = hand[0];
  if(canFollow) {
    for(int i = 0; i < MAX_HAND_SIZE; i++) {
      if(hand[i] > highestCard && hand[i].get_suit(trump) == ledSuit) {
        highestCard = hand[i];
      }
    }
    return highestCard;
  }
  else if(!canFollow) {
    for(int i = 0; i < MAX_HAND_SIZE; i++) {
      if(hand[i] < lowestCard) {
        lowestCard = hand[i];
      }
    }
    return lowestCard;
  }
}


};

class HumanPlayer: public Player {

};