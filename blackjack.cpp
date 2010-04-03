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


int BlackJack::extractAction(string text){
  istringstream strStr(text);
  int i = -1;
  if(strStr >> i && (BlackJack::HIT == i || BlackJack::STAND == i)){
    return i;
  };
  return BlackJack::INVALID;  
};

//requesting action from channel, channel right now is cout, cin but could be replaced with a networking implementation in ServerChannel class without disturbing BlackJack class
int BlackJack::requestAction(int id, string name){
  int act = BlackJack::INVALID;
  string response = "";
  do{
    writeToChannel(name + ": Press 1 to hit or Press 2 to stand");
    response = readFromChannel();
    act = extractAction(response);
  }
  while(BlackJack::INVALID == act);    
  return act;
};

//game play for blackjack,deal the first player, the dealer plays at the end
void BlackJack::play(){ 
  setTurn(1);
  while(players.size() != turn()){
    playWithCurrPlayer();
    incTurn();
  };
  setTurn(0);
  playWithCurrPlayer();
};

//FIXME big fat method very 
void BlackJack::playWithCurrPlayer(){
  BJPlayer* objPlayer = (BJPlayer *)players.at(turn());
  int action = -1;
  do{
    broadcast(objPlayer->name() + " your Cards are: "+ objPlayer->prettyPrintCards() +" your score is: " + iToS(objPlayer->score()));
    action = requestAction(objPlayer->id(), objPlayer->name());
    if(BlackJack::HIT == action){
      broadcast(objPlayer->name() + " goes for another card");
      dealCard();
      if(objPlayer->isBust()){
	broadcast(objPlayer->name() + " your Cards are: "+ objPlayer->prettyPrintCards() +" your score is: " + iToS(objPlayer->score()));
	broadcast(objPlayer->name() + " is Bust");
	break;
      };
      if(objPlayer->isBlackjack()){
	broadcast(objPlayer->name() + " your Cards are: "+ objPlayer->prettyPrintCards() +" your score is: " + iToS(objPlayer->score()));
	broadcast(objPlayer->name() + " got a BLACKJACK!");
	break;
      };
      
    }
    else if(BlackJack::STAND == action){
      broadcast(objPlayer->name() + " stands , score is " + iToS(objPlayer->score()));
      break;
    }
    else{
      cout << "error in program: action is : " <<  action << endl;
      throw "error in program";
    };
  }
  while(true);
};

//FIXME along with other messages, need a place to contruct my messages in this class, like a central formatter
string BlackJack::handleDealerBustResult(BJPlayer* objPlayer){
  string message = "";
  if(!objPlayer->isBust())
    message = objPlayer->name() + " wins against " + players.at(0)->name() +"  with score " + iToS(objPlayer->score());
  else
    message = objPlayer->name() + " doesn't win against " + players.at(0)->name() +" coz both are bust!. ";
  return message;
}

//FIXME big fat method
void BlackJack::anounceFinalResults(){
  broadcast("Anouncing Final results");
  vector<Player*>::iterator it;
  BJPlayer* objPlayer = (BJPlayer *)players.at(0);
  bool isDealerBust = objPlayer->isBust();
  int dealerScore =  objPlayer->score();
  string message = "";
  message = objPlayer->name() + " score is " + iToS(dealerScore);
  broadcast(message);
  for(it = (players.begin()+1); players.end() != it; it++){
    objPlayer = (BJPlayer *)(*it);
    if(isDealerBust){
      message = handleDealerBustResult(objPlayer);
    }
    else{
      string outcome = "";
      if(objPlayer->isBust()){
	outcome = "loses";
      }
      else{
	if(objPlayer->score() > dealerScore)
	  outcome = "wins";
	else if(objPlayer->score() < dealerScore)
	  outcome = "loses";
	else
	  outcome = "squares";	  
      };
      message = objPlayer->name() + " " +outcome + " against " + players.at(0)->name();
    };
    broadcast(message);
  };
};

void BlackJack::dealCard(int times){
  for(int i=0;times != i; i++){
    players.at(turn())->addCard(cards.top());
    cards.pop();
  };
};

//rules for dealing the cards
void BlackJack::dealCards(){
  broadcast("Dealing the cards...");
  vector<Player*>::iterator it;
  for(it = players.begin(); players.end() != it; it++){
    dealCard(2);
    incTurn();
  };
};

void BlackJack::incTurn(){
  _turn++;
};

void BlackJack::setTurn(const int turn){
  _turn = turn;
};

int BlackJack::turn() const{
  return _turn;
};

void BlackJack::broadcast(const string message){
  vector<Player*>::iterator it;
  for(it = players.begin(); players.end() != it; it++){
    (*it)->notify(message);
  };
  writeToChannel(MESSAGE_HEADER + message);
};

void BlackJack::writeToChannel(const string message){
  _channel->write(message);
};

string BlackJack::readFromChannel(){
  string temp = "";
  temp = _channel->read();
  return temp;
};
