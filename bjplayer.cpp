class BJPlayer: public Player{
public:
  BJPlayer(int id, string name): _id(id), Player(name){
  };
  int id() const{
    return _id;
  };
  bool isBust(){
    if(score() > 21)
      return true;
    else
      return false;
  };
  int score(){
    vector<Card *>::iterator it;
    int score = 0;
    int numAces = 0;
    for(it = cards.begin(); cards.end() != it; it++){
      if(1 == (*it)->type()){
	numAces++;
	score += 11;
      }
      else if((*it)->type() > 10){
	score += 10;
      }
      else{
	score += (*it)->type();
      };
    };
    if(score > 21 && numAces >0)
      score = reAdjustScore(score, numAces);
    return score;
  };
private:
  int reAdjustScore(int score, int numAces){
    while(score > 21 && numAces >0 ){
      score -= 10;
      numAces--;
    }
    return score;
  };
  int _finalScore;
  int _id;
};

//Need to add behaviour to this class for automating the dealer
class BlackJackDealer : public BJPlayer{
public:
  BlackJackDealer(int id) : BJPlayer(id, "DEALER") {

  };
};
