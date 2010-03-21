
class Player{
public:
  Player(string name) : _name(name){
  };
  void notify(string message){
    messages.push(message);
  };
  int money() const{
    return _money;
  };
  string name() const{
    return _name;
  };
    
  string prettyPrintCards(){
    string info = "\n##########################\n";
    vector<Card *>::iterator it;
    for(it = cards.begin(); cards.end() != it; it++){
      info.append((*it)->prettyPrint());
      info.append("\n");
    };
    info.append("##########################\n");
    return info;
  };
  void addCard(Card* card){
    cards.push_back(card);
  };
protected:
  vector<Card *> cards;
private:
  stack<string> messages;// a record of all messages, including the broadcast ones, not using right now but or needs a scheme to empty it regularly! 
  const string _name;
  int _money;
};
