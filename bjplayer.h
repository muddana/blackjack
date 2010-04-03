class BJPlayer: public Player{
public:
  BJPlayer(int id, string name);
  int id() const;
  bool isBust();
  bool isBlackjack();
  int score();     ;
private:
  int reAdjustScore(int score, int numAces);
  int _finalScore;
  int _id;
};

