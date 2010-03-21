class BJPlayer: public Player{
public:
  BJPlayer(int id, string name);
  int id() const;
  bool isBust();
  int score();
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

