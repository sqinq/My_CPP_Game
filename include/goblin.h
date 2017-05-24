  #ifndef __GOBLIN_H__
  #define __GOBLIN_H__
  #include <string>
  #include "player.h"
  
  class Goblin: public Player {
  public:
    
    //constructor
    Goblin();
    
    //takDemage(Character*): takes a pointer to a enemy and calculates the damage it gives to the Character. Specifies the 
    //case when the enemy is an orc
    //Character* -> Void
    void takeDamage(Character *enemy);
};


#endif

