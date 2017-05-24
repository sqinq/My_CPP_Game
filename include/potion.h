  #ifndef __POTION_H__
  #define __POTION_H__
  #include "playable.h"
  #include <string>
  
  class Floor;
  class Potion:public Playable {
    protected:
      Playable* p;
      
    public:
      
      //constructor, sets the type to potion and hp, atk, def
      Potion();
      
      //destructor, deletes p
      ~Potion();
      
      //getHp(): returns the hp of p
      //Void -> Int
      int getHp() {return p->getHp();}
      
      //setHp(): sets the hp of p
      //Int -> Void
      void setHp(int i) {p->setHp(i);}
      
      //getAtk(): returns the atk of p
      //Void -> Int
      int getAtk() {return p->getAtk();}
      
      //getDef(): returns the def of p
      //Void -> Int
      int getDef() {return p->getDef();}
      
      //getGold(): returns the gold of p
      //Void -> Int
      int getGold(){return p->getGold();};
      
      //changeGold(): changes the gold of p to i
      //Int -> Void
      void changeGold(int i){p->changeGold(i);};

      // changeHp(i) changes the hp of p to hp + i
      void changeHp(int i) { p->changeHp(i); }
      
      //takePotion(Playable*): makes the playable item p takes the potion
      //Playable* -> Void
      void takePotion(Playable* p);
      
      //getPotion(Floor*, int type): randomly returns a pointer to one kind of the potions
      //Floor* Int-> Potion* 
      static Potion* getPotion(Floor* g, int type = -1);

      //takeDamage(Character*): takes a pointer to an enemy and calculates the damage it gives to p
      //Character* -> Void
      void takeDamage(Character* enemy) {p->takeDamage(enemy);}
  };
  
  
  #endif

