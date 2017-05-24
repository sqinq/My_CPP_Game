#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>

class Playable;
class Gold;
class Enemy;
class Character;

class View
{
public:
    // constructor
    View();

    // destructor
    virtual ~View();

    // print(player) prints the board and relevant game stats
    virtual void print(Playable * player, int level) = 0;

    // change(r1, c1, r2, c2, type) moves character at (r1, c1) to (r2, c2)
    // with optional type to indicate that character is player 
    virtual void change(int r1, int c1, int r2, int c2, std::string type = "") = 0;

    // potionsSurrounding(directions, length) updates the action string to
    // reflect the potions surrounding the character, with cardinal locations
    // indicated with directions (see getSingleCardinal for more info) and 
    // the array has length of the argument, also cleans up memory of directions
    virtual void potionsSurrounding(int * directions, int length) = 0;

    // potionUsed(r, c, type) updates that potion of variety type at
    // (r, c) used
    virtual void potionUsed(int r, int c, std::string type) = 0;

    // gold(gold) updates that gold was obtained
    virtual void gold(Gold * gold) = 0;

    // dead(character) updates that character died
    virtual void dead(Character * character) = 0;

    // enemyAttacked(enemy, amount) updates that enemy was attacked
    // for amount damage
    virtual void enemyAttacked(Enemy * enemy, int amount) = 0;

    // attackMissed() updates that player's attack missed
    virtual void attackMissed() = 0;

    // notifyWon(player) updates that player won
    virtual void notifyWon(Playable * player) = 0;

    // notifyLoss(player) updates that player lost
    virtual void notifyLoss(Playable * player) = 0;

    // notifyResetart() updates that player restarted
    virtual void notifyRestart() = 0;

    // notifyQuit() updates that player quit
    virtual void notifyQuit() = 0;

    // notifyCreated(character) updates that character was created
    virtual void notifyCreated(Character & character) = 0;

    // notifyPlayerDamaged(amount, type) updates that enemy of race type
    // damaged player for amount damage
    virtual void notifyPlayerDamaged(int amount, std::string type) = 0;

    // notifyStairs() updates that stairs were reached
    virtual void notifyStairs() = 0;

    // notifyGoldDropped(enemy) updates that enemy dropped gold
    virtual void notifyGoldDropped(Enemy * enemy) = 0;
};

#endif



