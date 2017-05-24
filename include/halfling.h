#ifndef __HALFLING_H__
#define __HALFLING_H__

#include "moveableenemy.h"

class Floor;

class Halfling : public MoveableEnemy
{
public:
	// constructor
    Halfling(Floor * game);
};

#endif
