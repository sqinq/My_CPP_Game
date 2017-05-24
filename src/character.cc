#include "character.h"
#include "floor.h"
#include <string>
#include <cmath>
using namespace std;

//see .h for documentation
  Character::Character(int hp, int atk, int def):
    hp(hp),
    atk(atk),
    def(def),
    gold(0),
    game(){}
    
//see .h for documentation    
  int Character::getHp() {return hp;}
//see .h for documentation
  int Character::getDef() {return def;}
//see .h for documentation
  int Character::getAtk() {return atk;}
//see .h for documentation
  int Character::getGold() {return gold;}
//see .h for documentation
  int Character::getRow() {return r;}
//see .h for documentation
  int Character::getCol() {return c;}
//see .h for documentation
  std::string Character::getOverallType() { return overallType;}
//see .h for documentation
  Floor* Character::getGame() {return game;}
  
//see .h for documentation
  void Character::changeGold(int i) {gold += i;}
//see .h for documentation
  void Character::changeHp(int i) {
    int tempHp = getHp();
    //if after change hp, hp is below 0
    if (tempHp+i <= 0){
      setHp(0);
      game->notifyDead(this);
    } else {
      setHp(tempHp + i);
    }
  }

//see .h for documentation
  void Character::setGame(Floor* g) {game = g;}
//see .h for documentation
  void Character::setCood(int r, int c) {
    this->r = r;
    this->c = c;
  }
//see .h for documentation
  void Character::setHp(int i) {hp = i;}
//see .h for documentation
  void Character::setOverallType(std::string overallType) {
    this->overallType = overallType;
  }
//see .h for documentation
  void Character::takeDamage(Character* enemy) {
    int amount = ceil(((double) 100/(100+getDef()))*enemy->getAtk()); //calculating the amount of damage
    changeHp(-amount);
    game->notifyPlayerDamaged(amount, enemy->getType());//notify the gameboard
  }

//see .h for documentation
  void Character::move(int r, int c){
    game->notifyMoved(getRow(), getCol(), r, c, overallType);
    setCood(r, c);
  }
  

