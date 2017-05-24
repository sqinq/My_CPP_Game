#ifndef __DWARF_H__
#define __DWARF_H__

#include "moveableenemy.h"

class Floor;

class Dwarf : public MoveableEnemy
{
public:
	// constructor
    Dwarf(Floor * game);
};

#endif
