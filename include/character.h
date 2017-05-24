#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
  
class Floor;
class Character {
  int hp, atk, def; //health point, attack, and defence
  int r, c; //location
  int gold; 
  Floor* game; //a pointer to the gameboard
  std::string overallType; //the overall type of the character (player, potion, gold, or stairs)
  
  public:
    
    //constructor, sets the health point, attack, and defence
    Character(int hp, int atk, int def);
    
    //getHp(): returns the value of hp
    //Void -> Int
    virtual int getHp();
    
    //getDef(): returns the value of def
    //Void -> Int
    virtual int getDef();
    
    //getAtk(): returns the value of atk
    //Void -> Int
    virtual int getAtk();
    
    //getGold(): returns the value of gold
    //Void -> Int
    virtual int getGold();
    
    //getRow(): returns the value of r
    //Void -> Int
    int getRow();
    
    //getCol(): returns the value of c
    //Void -> Int
    int getCol();
    
    //getGame(): returns the pointer to the gameboard
    //Void -> Floor*
    Floor* getGame();
    
    //getOverallType(): returns the overallType of this character
    //Void -> String
  std::string getOverallType();
  
  //getType: returns the type of the character
  //Void ->string
  virtual std::string getType() =0;
  
  //setGame: sets the pinter to gameboard to g
  //Floor* -> Void
  //effect: changes the value of Character::game
  void setGame(Floor* g);
  
  //setCood: sets this->r and this->c to r and c
  //Int, Int -> Void
  //effect: changes the value of Character::r and Character::c to r and c
  void setCood(int r, int c);
  
  //changeHp(): changes the value of hp to i
  //Int ->Void
  virtual void changeHp(int i);
  
  //changeGold(): changes the value of gold to i
  //Int -> Void
  virtual void changeGold(int i);
  
  //setOverallType: sets the field overallType to overallType
  //String -> Void
  //effect: changes the value of Character::overallType
  void setOverallType(std::string overallType);
  
  //setHp: sets the field hp to hp
  //Int -> Void
  //effect: changes the value of Character::hp
  virtual void setHp(int hp);
  
  //move(int, int): takes r and c and moves the character to this location
  //Int Int -> Void
  void move(int r, int c);
  
  //takDemage(Character*): takes a pointer to a enemy and calculates the damage it gives to the Character
  //Character* -> Void
  virtual void takeDamage(Character* enemy);
  
  //getHoard(): returns the value of hoard
  //Void -> String
  virtual std::string getHoard(){return "";} ;
};

#endif

