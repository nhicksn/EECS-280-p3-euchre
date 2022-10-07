// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <cassert>
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

public:
  SimplePlayer() {
    this->name = "";
  }
  const std::string get_name() {
    return this->name;
  }
};

class HumanPlayer: public Player {

};