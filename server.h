//generic server class to hold objects of type CardGame
class GameServer{
public:
  void addGame(string name, int numDecks);

  void join(int typeOfGame, string name);

  void startGame(int typeOfGame);

  GameServer();    

private:
  map<int,string> idToIP; //id to ip mapping to communicate with the user not used for now
  int clientCount;
  vector<CardGame *> games;
  //each game at particular index is of the following type, bad design need to be modified
  Player* getPlayer(int typeOfGame, string name){
    switch(typeOfGame){
    case 0:
      return new BJPlayer(clientCount, name);
    default:
      throw "unknown game type";
    };
  }
};
