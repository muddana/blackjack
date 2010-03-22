#include "player.h"

Player::Player(string name) : _name(name){
};
void Player::notify(string message){
  messages.push(message);
};
int Player::money() const{
  return _money;
};
string Player::name() const{
  return _name;
};

string Player::prettyPrintCards(){
  string info = "\n##########################\n";
  vector<Card *>::iterator it;
  for(it = cards.begin(); cards.end() != it; it++){
    info.append((*it)->prettyPrint());
    info.append("\n");
  };
  info.append("##########################\n");
  return info;
};

void Player::addCard(Card* card){
  cards.push_back(card);
};

