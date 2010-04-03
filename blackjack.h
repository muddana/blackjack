class BlackJack : public CardGame{
private:
  enum Action{
    INVALID, HIT, STAND
  };
    
  int extractAction(string text);

  //requesting action from channel, channel right now is cout, cin but could be replaced with a networking implementation in ServerChannel class without disturbing BlackJack class
  int requestAction(int id, string name);

  //game play for blackjack
  void play();
  
  void playWithCurrPlayer();
  
  string handleDealerBustResult(BJPlayer* objPlayer);

  void anounceFinalResults();

  void dealCard(int times = 1);

  //rules for dealing the cards
  void dealCards();

  void incTurn();

  void setTurn(const int turn);

  int turn() const;
    
  void broadcast(const string message);

  void writeToChannel(string message);
  
  string readFromChannel();

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

