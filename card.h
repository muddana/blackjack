class Card{
public:
  Card(int type,int suit);
  enum CardType{
    ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX =6, SEVEN = 7, EIGHT = 8, NINE = 9 , TEN = 10, JACK = 10, QUEEN = 12, KING = 13
  };
  enum CardSuit{
    HEARTS = 1, SPADES = 2, DIAMONDS = 3, CLUBS = 4
  };
  int type() const;
  int suit() const;
  string prettyPrint() const;
  string getSuit() const;

  string getType() const;

private:
  const int _type;
  const int _suit;
};
