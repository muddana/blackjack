//generic library for a card games
class CardGame{
public:
  void virtual start() = 0;

  CardGame(string name): _name(name){
  };

  CardGame(string name, int numOfPacks): _name(name){
    initCardStack(numOfPacks);
  };

  void initCardStack(int numOfPacks){
    srand (time(NULL));
    vector<Card *> tempcards;
    for(int times=0; numOfPacks != times; times++){
      for(int suit=Card::HEARTS; Card::CLUBS >= suit; suit++){
	for(int type=Card::ACE; Card::KING >= type; type++){
	  tempcards.push_back(new Card(type, suit));
	};
      };
    };
    random_shuffle(tempcards.begin(), tempcards.end());
    vector<Card *>::iterator it;
    for(it = tempcards.begin(); tempcards.end() != it; it++){
      cards.push((*it));
    };
  };

  void virtual addPlayer(Player* player){
    players.push_back(player);
    broadcast(player->name() + " joined the game");
  };

  void virtual dealCards() = 0;

  string name() const{
    return _name;
  };

  void virtual broadcast(string message){
    vector<Player*>::iterator it;
    for(it = players.begin(); players.end() != it; it++){
      (*it)->notify(message);
    };
  };

protected:
  vector<Player*> players;
  stack<Card*> cards;
private:

  void sendMessageToPlayer(Player* player, string message){
    player->notify(message);
  };

  const string _name;
};
