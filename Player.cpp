// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include "Player.h"

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
  SimplePlayer(std::string &nameInput) {
    this->name = nameInput;
  }

  //EFFECTS returns player's name
  const std::string &get_name() const override {
    return this->name;
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
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
    assert(round == 1 || round == 2);
    int trumpCounter = 0;
    std::string upTrump = upcard.get_suit(order_up_suit);
    if(round == 1) {
      for(int i = 0; i < MAX_HAND_SIZE; i++) {
        
      }
    }
  }
};

class HumanPlayer: public Player {

};