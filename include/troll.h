  #ifndef __TROLL_H__
  #define __TROLL_H__
  #include <string>
  #include "player.h"
  
  class Troll: public Player {
  public:
    //constructor
    Troll();
    
    //changeHp(): changes the value of hp to i(maximum 120)
    //Int ->Void
    void changeHp(int amount);
};


#endif

