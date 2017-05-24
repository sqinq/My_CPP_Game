  #include "player.h"
  #include "troll.h"
  #include "default.h"
  #include "vampire.h"
  #include "goblin.h"
  #include "drow.h"
  #include <string>
  #include <iostream>
  using namespace std;

  Player * Player::instance = NULL;
  
//see .h for documentation
  Player::Player(int hp, int atk, int def):Playable(hp, atk, def){
    this->setOverallType("player");
  }
  
//see .h for documentation
  Player::~Player() { instance = NULL;}
  
//see .h for documentation
  Player* Player::getInstance(string type) {
    if (instance) return instance;
    if (type =="s") 
      instance = new Default;
    else if (type =="t")
      instance = new Troll;
    else if (type == "v")
      instance = new Vampire;
    else if (type == "g")
      instance = new Goblin;
    else
      instance = new Drow;
    return instance;       
  }//factory method, generate a player
  
  
  

