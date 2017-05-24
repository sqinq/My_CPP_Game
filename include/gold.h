#ifndef __GOLD_H__
#define __GOLD_H__

#include <string>

#include "playable.h"

class Floor;

class Gold : public Playable
{
	// the type of hoard (e.g. dragon hoard, normal hoard)
	std::string hoard;

	// the value of the hoard (e.g. dragon hoard is 6)
    int value;

public:
	// constructor
    Gold(int i, std::string hoard, Floor * game);

    // getValue() returns value
    int getValue();

    // getHoard() returns hoard
    std::string getHoard();

    // getGold(game, type) returns a randomly generated type of gold
    // for initial spawning
    static Gold * getGold(Floor * game, int type = -1);

    // getOrdinaryDrop(game) returns a randomly generated small
    // or normal hoard
    static Gold * getOrdinaryDrop(Floor * game);

    // getMerchantGold(game) returns a gold representing merchant hoard
    static Gold * getMerchantGold(Floor * game);

    // getHumanGold(game) returns a gold representing two normal hoards
    static Gold * getHumanGold(Floor * game);
};

#endif

