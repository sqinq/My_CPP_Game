  #ifndef __PLAYER_H__
  #define __PLAYER_H__
  #include "playable.h"
  #include <string>
  
  class Playable;

  class Player:public Playable{
    
    public:
      
      static Player* instance; //a pointr to the only instance of player
      
      //constructor, sets the health point, attack, and defence
      Player(int hp, int atk, int def);
      
      //getInstance(type): takes a type, allocs and returns a pointer to a player of that type
      //String -> Player*
    static Player* getInstance(std::string type);//factory method, generate a player
    
    //move(r, c): takes r and c and moves the player to r, c
    //Int Int -> Void
    void move(int r, int c);
    
    ~Player();//destructor
  };
  
  #endif

