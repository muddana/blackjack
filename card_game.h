class CardGame{
public:
  void virtual start() = 0;

  CardGame(string name);

  CardGame(string name, int numOfPacks);

  void initCardStack(int numOfPacks);

  void virtual addPlayer(Player* player);

  void virtual dealCards() = 0;
  
  string name() const;

  void virtual broadcast(string message);

protected:
  vector<Player*> players;
  stack<Card*> cards;
private:

  void sendMessageToPlayer(Player* player, string message){
    player->notify(message);
  };

  const string _name;
};
