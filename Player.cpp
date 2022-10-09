// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Card.h"

using namespace std;

class SimplePlayer: public Player {
private:
  std::string name;
  vector<Card> hand;

public:
  SimplePlayer(const std::string &nameInput) {
    this->name = nameInput;
  }

  //EFFECTS returns player's name
  const std::string &get_name() const override {
    return this->name;
  }
  
  //EFFECTS returns player's hand
  const std::vector<Card> &get_hand() { //no override bc not base class
    return this->hand;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    assert(this->hand.size() < MAX_HAND_SIZE);
    this->hand.push_back(c);
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
    std::string upTrump = upcard.get_suit();
    std::vector<Card> hand = this->hand;

    if(round == 1) {
      for(int i = 0; i < hand.size(); i++) {
        if((hand[i].get_suit(upTrump) == upTrump) && (hand[i].get_rank() == Card::RANK_JACK || 
        hand[i].get_rank() == Card::RANK_QUEEN || hand[i].get_rank() == Card::RANK_KING ||
        hand[i].get_rank() == Card::RANK_ACE)) {
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
      for(int i = 0; i < hand.size(); i++) {
        if((hand[i].get_suit(sameColor) == sameColor) && (hand[i].get_rank() == Card::RANK_JACK || 
        hand[i].get_rank() == Card::RANK_QUEEN || hand[i].get_rank() == Card::RANK_KING ||
        hand[i].get_rank() == Card::RANK_ACE)) {
          trumpCounter++;
        }
      }
      if((trumpCounter >= 1) || (is_dealer == true)) {
        order_up_suit = sameColor;
        return true;
      }
    }
    return false;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    assert(this->hand.size() > 0);
    std::vector<Card> hand = this->hand;
    std::string trump = upcard.get_suit();
    Card lowestCard = hand[0];
    int lowestIndex = 0;
    bool allTrump = false;
    int trumpCounter = 0;
    for(int i = 0; i < hand.size(); i++) {
      if(hand[i].get_suit(trump) == trump) {
        trumpCounter++;
      }
    }
    if(trumpCounter == hand.size()) allTrump = true;
    if(!allTrump) {
      for(int i = 0; i < hand.size(); i++) {
        if(Card_less(hand[i], lowestCard, trump) && hand[i].get_suit(trump) != trump) {
          lowestCard = hand[i];
          lowestIndex = i;
        }
      }
    }
    else if(allTrump) {
      for(int i = 0; i < hand.size(); i++) {
        if(Card_less(hand[i], lowestCard, trump)) {
          lowestCard = hand[i];
          lowestIndex = i;
        }
      }
    }
    if(Card_less(upcard, lowestCard, trump)) return;
    else if(Card_less(lowestCard, upcard, trump)) this->hand[lowestIndex] = upcard;
  }

 //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override {
    assert(this->hand.size() > 0);
    assert(trump == "Clubs" || trump == "Diamonds"
            || trump == "Hearts" || trump == "Spades");

    std::vector<Card> hand = this->hand;
    Card highestCard = hand[0];
    int highestIndex = 0;
    bool allTrump = false;
    int trumpCounter = 0;
    for(int i = 0; i < hand.size(); i++) {
      if(hand[i].get_suit(trump) == trump) {
        trumpCounter++;
      }
    }
    if(trumpCounter == hand.size()) allTrump = true;
    if(!allTrump) {
      for(int i = 0; i < hand.size(); i++) {
        if(hand[i].get_suit(trump) != trump) {
          highestCard = hand[i];
          break;
        }
      }
    }
    if(allTrump) {
      for(int i = 0; i < hand.size(); i++) {
        if(Card_less(highestCard, hand[i], trump)) {
          highestCard = hand[i];
          highestIndex = i;
        }
      }
    }
    else if(!allTrump) {
      for(int i = 0; i < hand.size(); i++) {
        if(Card_less(highestCard, hand[i], trump) && hand[i].get_suit(trump) != trump) {
          highestCard = hand[i];
          highestIndex = i;
        }
      }
    }
    this->hand.erase(this->hand.begin() + highestIndex);
    return highestCard;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
Card play_card(const Card &led_card, const std::string &trump) override {
  //checks if player has at least one card
  assert(this->hand.size() > 0);
  //checks if trump is valid input
  assert(trump == "Clubs" || trump == "Diamonds"
               || trump == "Hearts" || trump == "Spades");

  bool canFollow = false;
  std::vector<Card> hand = this->hand;
  std::string ledSuit = led_card.get_suit(trump);
  int index = 0;
  for(int i = 0; i < hand.size(); i++) {
    if(hand[i].get_suit(trump) == ledSuit) {
      canFollow = true;
    }
  }
  Card highestCard = hand[0];
  Card lowestCard = hand[0];
  if(canFollow) {
    for(int i = 0; i < hand.size(); i++) {
      if(hand[i] > highestCard && hand[i].get_suit(trump) == ledSuit) {
        highestCard = hand[i];
        index = i;
      }
    }
    this->hand.erase(this->hand.begin() + index);
    return highestCard;
  }
  else if(!canFollow) {
    for(int i = 0; i < hand.size(); i++) {
      if(hand[i] < lowestCard) {
        lowestCard = hand[i];
        index = i;
      }
    }
    this->hand.erase(this->hand.begin() + index);
    return lowestCard;
  }
  Card c;
  return c;
}


};

class HumanPlayer: public Player {
private:
  std::string name;
  std::vector<Card> hand;
  void print_hand() const {
    for(size_t i=0; i < this->hand.size(); ++i) {
      std::cout << "Human player " << this->name << "'s hand: "
           << "[" << i << "] " << this->hand[i] << "\n";
    }
  }
public:

  HumanPlayer(const std::string &nameInput) {
    this->name = nameInput;
  }

  //EFFECTS returns player's name
  const std::string & get_name() const override {
    return this->name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    assert(this->hand.size() < MAX_HAND_SIZE);
    this->hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, std::string &order_up_suit) const override {
    std::vector<Card> hand = this->hand;
    std::string playerChoice;
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Human player " << name << ", please enter a suit, or pass\n";
    std::cin >> playerChoice;
    if(playerChoice == "Spades") {
      order_up_suit = "Spades";
      return true;
    }
    else if(playerChoice == "Hearts") {
      order_up_suit = "Hearts";
      return true;
    }
    else if(playerChoice == "Clubs") {
      order_up_suit = "Clubs";
      return true;
    }
    else if(playerChoice == "Diamonds") {
      order_up_suit = "Diamonds";
      return true;
    }
    else if(playerChoice == "Pass") {
      return false;
    }
    return false;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    std::string discard;
    std::vector<Card> hand = this->hand;
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Discard upcard: [-1]\n";
    std::cout << "Human player " << this->name << ", please select a card to discard:\n";
    std::cin >> discard;
    int discardInt = std::stoi(discard);
    if(discardInt == -1) {
      return;
    }
    for(int i = 0; i < hand.size(); i++) {
      if(discardInt == i) {
        this->hand[i] = upcard;
      }
    }
  }
  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override {
    std::string play;
    int playInt;
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Human player " << name << ", please select a card:\n";
    std::cin >> play;
    playInt = stoi(play);
    Card playCard;
    for(int i = 0; i < this->hand.size(); i++) {
      if(playInt == i) {
        playCard = this->hand[i];
        this->hand.erase(this->hand.begin() + i);
        return playCard;
      }
    }
    return this->hand[0];
  }
  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) override {
    std::string play;
    int playInt;
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Human player " << name << ", please select a card:\n";
    std::cin >> play;
    playInt = stoi(play);
    Card playCard;
    for(int i = 0; i < this->hand.size(); i++) {
      if(playInt == i) {
        playCard = this->hand[i];
        this->hand.erase(this->hand.begin() + i);
        return playCard;
      }
    }
    return this->hand[0];
  }
  
};

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
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

