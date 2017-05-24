  #include "potion.h"
  #include "restorehealth.h" 
  #include "poisonhealth.h"
  #include "boostdefence.h"
  #include "boostattack.h"
  #include "woundattack.h"
  #include "wounddefence.h"
  #include "floor.h"
  #include <cstdlib>
  #include <string>

//see .h for documentation
  Potion::Potion():Playable(0, 0, 0),p(0) {
  setOverallType("potion");
}

//see .h for documentation
  Potion::~Potion(){
    if (p && p->getOverallType() != "player")
      delete p;
  }
  
//see .h for documentation
  void Potion::takePotion(Playable *p){
     setDrow(p->getDrow());
    std::string tempType = getType();
    this->p = p;
    
    //directly changes the hp of the player 
    if (tempType == "RH" && getDrow())
      p->changeHp(15);
    else if (tempType == "PH" && getDrow())
      p->changeHp(-15);

    if (tempType == "RH" && !getDrow())
      p->changeHp(10);
    else if (tempType == "PH" && !getDrow())
      p->changeHp(-10);
    
    getGame()->notifyPotionUsed(getRow(), getCol(), tempType); 
  }
  
  
//see .h for documentation
  Potion* Potion::getPotion(Floor* g, int type) {
    int temp;
     if (type == -1)
         temp = rand() % 6; //generates a random number between 0 to 6
     else 
         temp = type;

    Potion* pt = NULL;
    if (temp==0)
      pt =  new RestoreHealth;
    else if (temp==1)
      pt = new BoostAttack;
    else if (temp==2)
      pt = new BoostDefence;
    else if (temp==3)
      pt = new PoisonHealth;
    else if (temp==4)
      pt = new WoundAttack;
    else 
      pt = new WoundDefence;
    pt->setGame(g);
    return pt;
  }
  

