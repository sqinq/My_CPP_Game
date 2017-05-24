#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <string>

#include "view.h"

class Playable;
class Enemy;
class Character;
class Gold;

class Display : public View
{
    // the char representation of the map
    char squares[25][79];

    // can be thought of as the char representing the floor tile
    // that the player is currently standing on
     char temp;

    // action string that is constantly appended when things happen
    std::string action;

    // holds the playerType throughout a single game
    std::string playerType;

    // getChar(x) returns the appropriate char for display if reading in from
    // a custom file (e.g. x = 0 returns P) or x if x isn't from '0' to '9'
    char getChar(char x);

    // getCardinal(row, column) returns the cardinal direction associated
    // with changing your coordinates relative by using row and column
    // for example, row=1 and column=1 will return south east
    // we require row and column to be between -1 and 1
    std::string getCardinal(int row, int column);

    // getSingleCardinal(cardinal) returns the cardinal direction 
    // associated with cardinal (for proper use, we require cardinal
    // to be between 1 and 8, and the numbers in ascending order are
    // associated with the cardinal directions left to right, top to bottom)
    std::string getSingleCardinal(int cardinal);

public:
    // constructor receives type, which is assigned to playerType
    Display(std::string type, std::string filename = "");

    // destructor
    ~Display();

    // print(player) prints the board and relevant game stats
    void print(Playable * player, int level);

    // change(r1, c1, r2, c2, type) moves entity from (r1, c1) to (r2, c2)
    // and uses type to update the action string if player
    void change(int r1, int c1, int r2, int c2, std::string type);

    // potionsSurrounding(directions, length) updates the action string to
    // reflect the potions surrounding the character, with cardinal locations
    // indicated with directions (see getSingleCardinal for more info) and 
    // the array has length of the argument, also cleans up memory of directions
    void potionsSurrounding(int * directions, int length);

    // potionUsed(r, c, type) updates that potion of variety type at
    // (r, c) used
    void potionUsed(int r, int c, std::string type);

    // gold(gold) updates that gold was obtained
    void gold(Gold * gold);

    // dead(character) updates that character died
    void dead(Character * character);

    // enemyAttacked(enemy, amount) updates that enemy was attacked for
    // amount damage
    void enemyAttacked(Enemy * enemy, int amount);

    // attackMissed() updates that player missed in attacking
    void attackMissed();

    // notifyWon(player) updates that player won
    void notifyWon(Playable * player);

    // notifyLoss(player) updates that player lost
    void notifyLoss(Playable * player);

    // notifyRestart() updates that player restarted
    void notifyRestart();

    // notifyQuit() updates that player quit
    void notifyQuit();

    // notifyCreated(character) notifies that character was created
    void notifyCreated(Character & character);

    // notifyStairs() updates that stairs were reached by player
    void notifyStairs();

    // notifyPlayerDamaged(amount, type) notifies that an enemy of
    // variety type damaged player by amount
    void notifyPlayerDamaged(int amount, std::string type);

    // notifyGoldDropped(enemy) updates that enemy has dropped gold
    void notifyGoldDropped(Enemy * enemy);
};

#endif

