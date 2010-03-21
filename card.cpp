class Card{
public:
  enum CardType{
    ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX =6, SEVEN = 7, EIGHT = 8, NINE = 9 , TEN = 10, JACK = 10, QUEEN = 12, KING = 13
  };
  enum CardSuit{
    HEARTS = 1, SPADES = 2, DIAMONDS = 3, CLUBS = 4
  };
  Card(int type,int suit) : _suit(suit), _type(type){
    
  };
  int type() const{
    return _type;
  };
  int suit() const{
    return _suit;
  };
  string prettyPrint() const{
    return "suit: " + getSuit() + ", type: " + getType();
  };
  string getSuit() const{
    switch(_suit){
    case 1:
      return "Hearts";
    case 2:
      return "Spades";
    case 3:
      return "Diamond";
    case 4:
      return "Clubs";
    default:
      cout << "Unknown suit type : " << _suit << endl;
      throw "Unkown suit type";
    }
  };
  string getType() const{
    switch(_type){
    case 1:
      return "A";
    case 2:
      return "2";
    case 3:
      return "3";
    case 4:
      return "4";
    case 5:
      return "5";
    case 6:
      return "6";
    case 7:
      return "7";
    case 8:
      return "8";
    case 9:
      return "9";
    case 10:
      return "10";
    case 11:
      return "JACK";
    case 12:
      return "QUEEN";
    case 13:
      return "KING";
    default:
      cout << "Unknown card type : " << _type << endl;
      throw "Unkown suit type";
    }
  };
private:
  const int _type;
  const int _suit;
};
