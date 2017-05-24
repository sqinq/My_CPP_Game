#include "troll.h"
  #include "floor.h"
  #include <cmath>
  
//see .h for documentation
  Troll::Troll():Player(120, 25, 15) {
  setType("Troll");
}

//see .h for documentation
  void Troll::changeHp(int amount) {
    int tempHp = getHp() + amount;
    if (tempHp > 120) {
      setHp(120); 
    }else if (tempHp<=0) {
      setHp(0);
      getGame()->notifyDead(this);
    }else{
      setHp(tempHp);
    }
  }

