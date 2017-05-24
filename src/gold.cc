#include "gold.h"
#include "floor.h"

#include <cstdlib>
#include <string>

using namespace std;

// see gold.h for documentation
Gold::Gold(int i, string hoard, Floor * game) : Playable(0, 0, 0)
{
    value = i;
    this->hoard = hoard;
    setGame(game);
    setType("gold");
    setOverallType("gold");
}

// see gold.h for documentation
int Gold::getValue()
{
    return value;
}

// see gold.h for documentation
string Gold::getHoard()
{
    return hoard;
}

// see gold.h for documentation
Gold * Gold::getGold(Floor * game, int type)
{
     int random;
     if (type == -1)
        random = rand() % 8 + 1;
     else if (type == 6)
         random = 1;
     else if (type == 7)
         random = 6;
      else if (type == 8)
          return getMerchantGold(game);
     else if (type == 9)
         random = 9;

    if (1 <= random && random <= 5)
    {
        return new Gold(2, "normal hoard", game);
    }
    else if (6 <= random && random <= 7)
    {
        return new Gold(1, "small hoard", game);
    }
    else
    {
        return new Gold(6, "dragon hoard", game);
    }
}

// see gold.h for documentation
Gold * Gold::getOrdinaryDrop(Floor * game)
{
    srand(time(NULL));

    int random = rand() % 2 + 1;

    if (1 == random)
    {
        return new Gold(2, "normal hoard", game);
    }
    else
    {
        return new Gold(1, "small hoard", game);
    }
}

// see gold.h for documentation
Gold * Gold::getHumanGold(Floor * game)
{
    return new Gold(4, "two normal hoards", game);
}

// see gold.h for documentation
Gold * Gold::getMerchantGold(Floor * game)
{
    return new Gold(4, "merchant hoard", game);
}

