

#include "merchant.h"
#include "floor.h"

using namespace std;

// see merchant.h for documentation
Merchant::Merchant(Floor * game) : Enemy(30, 70, 5)
{
    setGame(game);
    attack = false;
    setType("merchant");
}

// see merchant.h for documentation
void Merchant::action()
{
    bool performed = false;

    // only attack if the boolean is set so
    if (attack)
    {
        performed = tryToAttack();
    }

    if (! performed) move();
}

// see merchant.h for documentation
void Merchant::setAttack(bool other)
{
    attack = other;
}
