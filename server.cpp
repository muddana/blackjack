#include "server.h"
//generic server class to hold objects of type CardGame

void GameServer::addGame(string name, int numDecks){
  games.push_back(new BlackJack(name, numDecks, new ServerChannel()));
};

void GameServer::join(int typeOfGame, string name){
  clientCount++;
  if(typeOfGame < games.size())
    games.at(typeOfGame)->addPlayer(getPlayer(typeOfGame, name));
  else
      ;
};

void GameServer::startGame(int typeOfGame){
  if(typeOfGame < games.size())
    games.at(typeOfGame)->start();
  else
      ;
};

GameServer::GameServer() : clientCount(0){
};

