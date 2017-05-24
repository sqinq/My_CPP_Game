#ifndef __ORC_H__
#define __ORC_H__

#include "moveableenemy.h"

class Floor;

class Orc : public MoveableEnemy
{
public:
	// constructor
    Orc(Floor * game);
    
    // action() is called for a single turn
    void action();
};

#endif
