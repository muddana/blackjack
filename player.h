class Player{
public:
  Player(string name);
  void notify(const string message);
  int money() const;
  string name() const;    
  string prettyPrintCards();
  void addCard(Card* card);
protected:
  vector<Card *> cards;
private:
  stack<string> messages;// a record of all messages, including the broadcast ones, not using right now but or needs a scheme to empty it regularly! 
  const string _name;
  int _money;
};
