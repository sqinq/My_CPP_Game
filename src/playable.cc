#include "playable.h"

//see .h for documentation
Playable::Playable(int a, int b, int c):Character(a, b, c){
    drow = 0;
}

//see .h for documentation
Playable::~Playable() {}

//see .h for documentation
std::string Playable::getType() {return type;}

//see .h for documentation
void Playable::setType(std::string type){
    this->type = type;
}
//see .h for documentation
void Playable::setDrow(bool drow){
    this->drow = drow;
}


