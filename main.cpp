#include "helper.h"

#include "card.cpp"

#include "player.cpp"
#include "card_game.cpp"

#include "server_channel.cpp"

#include "bjplayer.cpp"
#include "blackjack.cpp"

#include "server.cpp"



//try declaring a namespace for ur game class
int main(){
  
  GameServer bj;
  bj.addGame("ultimate blackjack", 2);
  bj.join(0, "stranger");
  bj.join(0, "diana");
  bj.startGame(0);
  //bj.begin();
  // Game poker = new Game("texas holdem"); this is illegal coz of the pure virtual keyword
  return 0; //what does this signify ?
};



