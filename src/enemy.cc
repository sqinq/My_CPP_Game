#include "enemy.h"
#include "character.h"
#include "playable.h"
#include "player.h"
#include "floor.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

// see enemy.h for documentation
Enemy::Enemy(int hp, int attack, int defence) : Character(hp, attack, defence)
{
    setOverallType("enemy");
}


// see enemy.h for documentation
void Enemy::setAttack(bool other)
{

}

// see enemy.h for documentation
void Enemy::attack(Playable & player)
{
    player.takeDamage(this);
}

// see enemy.h for documentation
string Enemy::getType()
{
    return type;
}

// see enemy.h for documentation
void Enemy::setType(std::string type){
    this->type = type;
}

// see enemy.h for documentation
void Enemy::takeDamage(Playable & player, string type)
{
    string playerType = type;
    string enemyType = getType();

    // hit is always true unless halfling, which makes it half chance false
    bool hit = true;

    if (enemyType == "halfling")
    {
        int random = rand() % 2;

        hit = (random == 1);
    }

    // if hit is true then attack
    if (hit)
    {
        // change is the damage calculation
        int change = ceil(((double) 100/(100+getDef())) * player.getAtk());

        // notify floor that attack occurred
        notifyFloorAttacked(this, change);

        changeHp(-change);

        // if player is vampire then could gain or lose health
        if (playerType == "v")
        {
            if (enemyType == "dwarf")
            {
                player.changeHp(-5);
            }
            else
            {
                player.changeHp(5);
            }
        }
    }
    else
    {
        // if attack missed then notify floor of that
        notifyFloorAttackMissed();
    }
}

// see enemy.h for documentation
void Enemy::notifyFloorAttacked(Enemy * enemy, int amount)
{
    getGame()->notifyEnemyAttacked(enemy, amount);
}

// see enemy.h for documentation
void Enemy::notifyFloorAttackMissed()
{
    getGame()->notifyAttackMissed();
}

// see enemy.h for documentation
bool Enemy::rowInRange(int row)
{
    if (0 <= row || row < 25) return true;

    return false;
}

// see enemy.h for documentation
bool Enemy::columnInRange(int column)
{
    if (0 <= column || column < 79) return true;

    return false;
}

// see enemy.h for documentation
Enemy * Enemy::getEnemy(Floor * game, string type)
{
     int random;
     if (type == "")
        random = rand() % 18 + 1;
     else if (type == "H")
        random = 1;
     else if (type == "W")
        random = 5;
     else if (type == "L")
        random = 8;
     else if (type == "E")
        random = 13;
     else if (type == "O")
        random = 15;
     else if (type == "M")
        random = 20;
      else 
         return getDragon(game);

    // returns an enemy pointer of random type
    if (1 <= random && random <= 4)
    {
        return new Human(game);
    }
    else if (5 <= random && random <= 7)
    {
        return new Dwarf(game);
    }
    else if (8 <= random && random <= 12)
    {
        return new Halfling(game);
    }
    else if (random == 13 || random == 14)
    {
        return new Elf(game);
    }
    else if (random == 15 || random == 16)
    {
        return new Orc(game);
    }
    else
    {
        return new Merchant(game);
    }
}

// see enemy.h for documentation
Enemy * Enemy::getDragon(Floor * game)
{
    return new Dragon(game);
}

// see enemy.h for documentation
bool Enemy::tryToAttack()
{
    bool foundPlayer = false;

    int row = getRow();
    int column = getCol();

    // iterate through the squares around the enemy
    for (int i = -1; i <= 1; i++)
    {
        for (int q = -1; q <= 1; q++)
        {
            // first we check if the new square in question is in game board
            if (columnInRange(column + i) && rowInRange(row + q))
            {
                // if the new square is the player
                if (getGame()->getMapValue(row + q, column + i) == '@')
                {
                    // record the player position and break out of loop
                    foundPlayer = true;
                    break;
                }
            }
        }

        if (foundPlayer) break;
    }

    // if player was found then enemy has right to attack it
    if (foundPlayer)
    {
        attack(*(getGame()->getPlayer()));
    }

    // return whether or not player was found
    return foundPlayer;
}

// see enemy.h for documentation
void Enemy::move()
{
    int row = getRow();
    int column = getCol();

    int length = 0;

    // cardinal represents the direction represented by the square currently 
    // analyzing as you iterate through the for loops
    int cardinal = 1;

    // possible is filled with numbers from 1 to 8, indicating the cardinal directions
    // (left to right, top to bottom)
    int possible[8] = {0};

    // iterate through the surrounding squares
    for (int i = -1; i <= 1; i++)
    {
        for (int q = -1; q <= 1; q++)
        {
            // if new square in game board range
            if (columnInRange(column + q) && rowInRange(row + i))
            {
                // if new square is valid step tile
                if (getGame()->getMapValue(row + i, column + q) == '.')
                {
                    // add the appropriate cardinal number (e.g. E = 5) to possible 
                    possible[length] = cardinal;
                    length++;
                }
            }

            // we only increment cardinal if not the center square
            if (!(i == 0 && q == 0)) cardinal++;
        }
    }

    // if a valid direction to move exists
    if (length > 0)
    {
        // choose a random valid direction
        int random = rand() % length;

        cardinal = possible[random];

        int newRow, newColumn;

        // get the new square determined by the current location and the
        // cardinal direction
        if (1 <= cardinal && cardinal <= 3)
        {
            newRow = row - 1;
        }
        else if (4 <= cardinal && cardinal <= 5)
        {
            newRow = row;
        }
        else
        {
            newRow = row + 1;
        }


        if (cardinal == 1 || cardinal == 4 || cardinal == 6)
        {
            newColumn = column - 1;
        }
        else if (cardinal == 2 || cardinal == 7)
        {
            newColumn = column;
        }
        else
        {
            newColumn = column + 1;
        }

        // move enemy to that new location
        Character::move(newRow, newColumn);
    }
}

