  #include "goblin.h"
  #include <string>
  #include "floor.h"
  #include <cmath>
  
//see .h for documentation
  Goblin::Goblin():Player(110, 15, 20){
  setType("Goblin");
}

//see .h for documentation
  void Goblin::takeDamage(Character* enemy) {
    int amount;
    //if it is a orc, take 50% more damage
    if (enemy->getType() == "orc") {
      amount = ceil(((double) 100/(100+getDef()))*enemy->getAtk()*1.5);
      changeHp(-amount);
    } else {      //otherwise it's the same 
      amount = ceil(((double) 100/(100+getDef()))*enemy->getAtk());
      changeHp(-amount);
    }
    getGame()->notifyPlayerDamaged(amount, enemy->getType()); //notify the gameboard
  }
  

