#ifndef __STAIRS_H__
#define __STAIRS_H__

#include "playable.h"

class Floor;

class Stairs : public Playable
{
public:
	// constructor
	Stairs(Floor * game);
	
	// getStairs(game) returns a stairs pointer
	static Stairs * getStairs(Floor * game);

	// getType() returns "stairs"
	std::string getType();
};

#endif
