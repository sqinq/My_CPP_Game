#ifndef __PLAYABLE_H__
#define __PLAYABLE_H__
#include "character.h"
#include <string>

class Playable: public Character {
    std::string type;//the specific type of the character
     bool drow;
    public:
     //constructor
    Playable(int hp, int atk, int def);
     //destructor
    virtual ~Playable();

    //setType: sets the field type to type
    //String -> Void
    //effect: changes the value of type
    void setType(std::string type);

    //getType: returns the type of the character
    //Void ->string
    std::string getType();
 
    //setDrow: sets the field drow to drow
    //Bool -> Void
    void setDrow(bool drow);

    //getDrow: returns the field drow to drow
    //Void -> Bool
    bool getDrow() {return drow;}
};

#endif

