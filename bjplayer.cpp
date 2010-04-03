#include "bjplayer.h"
#include "bjdealer.h"


BJPlayer::BJPlayer(int id, string name): _id(id), Player(name){
};
int BJPlayer::id() const{
  return _id;
};
bool BJPlayer::isBust(){
  return (score() > 21);
};

bool BJPlayer::isBlackjack(){
  return (21 == score());
};

int BJPlayer::score(){
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

//privates
int BJPlayer::reAdjustScore(int score, int numAces){
  while(score > 21 && numAces >0 ){
    score -= 10;
    numAces--;
  }
  return score;
};
