#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"

class Playable;
class Floor;

class Enemy : public Character
{
protected:
    // type represents the enemy's specific type (e.g. human)
    std::string type;

public:
    // constructor
    Enemy(int hp, int attack, int defence);

    // action() is called for an enemy's single turn, but must be overridden
    virtual void action() = 0;

    // attack(player) attacks the player and lowers player's health
    void attack(Playable & player);

    // setType() sets type
    void setType(std::string type);

    // getType() returns type
    std::string getType();

    // takeDamage(player) causes enemy to take damage from the player
    void takeDamage(Playable & player, std::string type);

    // notifyFloorAttacked(enemy, amount) notifies floor that enemy was attacked
    // for amount damage
    void notifyFloorAttacked(Enemy * enemy, int amount);

    // notifyFloorAttackMissed() notifies floor that player's attack missed
    // (e.g. halfling)
    void notifyFloorAttackMissed();

    // rowInRange(row) returns true if row is valid with the game board
    bool rowInRange(int row);

    // columnInRange(column) returns true if column is valid with the game board
    bool columnInRange(int column);

    // getEnemy(game, type) returns an enemy pointer, randomly generated type
    static Enemy * getEnemy(Floor * game, std::string type = "");

    // getDragon(game) returns a dragon pointer
    static Enemy * getDragon(Floor * game);

    // tryToAttack() returns true if enemy successfully attacked player in a turn
    bool tryToAttack();

    // move() is called to move the enemy (if attacking fails)
    void move();

    // setAttack(other) is only used for merchant to indicate whether merchants should
    // attack player (but must appear here since merchants referred to using enemy pointers)
    virtual void setAttack(bool other);
};

#endif

