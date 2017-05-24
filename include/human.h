#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "moveableenemy.h"

class Floor;

class Human : public MoveableEnemy
{
public:
	// constructor
    Human(Floor * game);
};

#endif
