#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "enemy.h"

class Floor;

class Merchant : public Enemy
{
	bool attack;

public:
	// constructor
    Merchant(Floor * game);

    // setAttack(other) sets attack boolean to other
    void setAttack(bool other);

    // action() is called for a single turn
    void action();
};

#endif
