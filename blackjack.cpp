#include "blackjack.h"

BlackJack::BlackJack(string name, int numOfDecks,ServerChannel* channel) : CardGame(name, numOfDecks), _channel(channel), _turn(0), MESSAGE_HEADER("BLACKJACK GAME:"){
  players.push_back(new BlackJackDealer(0));
};

void BlackJack::start(){
  broadcast("Starting the game...");
  dealCards();
  play();
  anounceFinalResults();
};

