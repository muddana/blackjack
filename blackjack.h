class BlackJack : public CardGame{
private:
  enum Action{
    INVALID, HIT, STAND
  };
    
  int extractAction(string text){
    istringstream strStr(text);
    int i = -1;
    if(strStr >> i){
      if(BlackJack::HIT == i || BlackJack::STAND == i)
	return i;
      else
	return BlackJack::INVALID;
    }
    else
      return BlackJack::INVALID;
      
  };

  //requesting action from channel, channel right now is cout, cin but could be replaced with a networking implementation in ServerChannel class without disturbing BlackJack class
  int requestAction(int id, string name){
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

  //game play for blackjack
  void play(){
    // deal the first player
    setTurn(1);
    while(players.size() != turn()){
      playWithCurrPlayer();
      incTurn();
    };
    //the dealer plays at the end
    setTurn(0);
    playWithCurrPlayer();
  };

  
  void playWithCurrPlayer(){
    BJPlayer* objPlayer = (BJPlayer *)players.at(turn());
    int action = -1;
    do{
      broadcast(objPlayer->name() + " your Cards are: "+ objPlayer->prettyPrintCards() +" your score is: " + iToS(objPlayer->score()));
      action = requestAction(objPlayer->id(), objPlayer->name());
      if(BlackJack::HIT == action){
	broadcast(objPlayer->name() + " goes for another card");
	  dealCard();
	  if(objPlayer->isBust()){
	    broadcast(objPlayer->name() + " score is: " + iToS(objPlayer->score()));
	    broadcast(objPlayer->name() + " is Bust, loses anyways!");
	    break;
	  }
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
  
  string  handleDealerBustResult(BJPlayer* objPlayer){
    string message = "";
    if(!objPlayer->isBust())
      message = objPlayer->name() + " wins against " + players.at(0)->name() +"  with score " + iToS(objPlayer->score());
    else
      message = objPlayer->name() + " doesn't win against " + players.at(0)->name() +" coz both are bust!. ";
    return message;
  }

  void anounceFinalResults(){
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

  void dealCard(int times = 1){
    for(int i=0;times != i; i++){
      players.at(turn())->addCard(cards.top());
      cards.pop();
    };
  };

  //rules for dealing the cards
  void dealCards(){
    broadcast("Dealing the cards...");
    vector<Player*>::iterator it;
    for(it = players.begin(); players.end() != it; it++){
      dealCard(2);
      incTurn();
    };
  };

  void incTurn(){
    _turn++;
  };

  void setTurn(int turn){
    _turn = turn;
  };
  int turn() const{
    return _turn;
  };
    
  void broadcast(string message){
    vector<Player*>::iterator it;
    for(it = players.begin(); players.end() != it; it++){
      (*it)->notify(message);
    };
    writeToChannel(MESSAGE_HEADER + message);
  };

  void writeToChannel(string message){
    _channel->write(message);
  };
  
  string readFromChannel(){
    string temp = "";
    temp = _channel->read();
    return temp;
  };

  int _turn;
  const string MESSAGE_HEADER;
  ServerChannel* _channel;
 public:
  BlackJack(string name, int numOfDecks,ServerChannel* channel);
  
  void start();
  
  ~BlackJack(){
    delete _channel;
  };

};

