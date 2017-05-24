#ifndef __ELF_H__
#define __ELF_H__

#include "moveableenemy.h"

class Floor;

class Elf : public MoveableEnemy
{
public:
	// constructor
    Elf(Floor * game);

    // action() is called for object to move one turn
    void action();
};

#endif
