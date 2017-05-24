#ifndef __FLOOR_H__
#define __FLOOR_H__

class Playable;
class Enemy;
class Potion;
class Gold;
class Controller;
class Stairs;
class Gold;
class Character;

#include <vector>
#include <string>

class Floor
{
    // the player (or potion decorator)
    Playable * player;

    // the stairs
    Stairs * stairs;

    // enemies, potions, and gold vectors
    std::vector<Enemy *> enemies;
    std::vector<Potion *> potions;
    std::vector<Gold *> gold;

    // the controller 
    Controller * controller;

    // the player type
    std::string playerType;

    // whether player beat level
    bool beatLevel;

    // whether a single game is still on 
    bool gameOn;

    // char representation of the board
    char tiles[25][79];

    // the player's spawning chamber
    int chamber;

    // can be thought of as the floor tile that the player is standing on (e.g. '.', '#')
    char temp;

    // getChar(x) returns the appropriate char for display if reading in from
    // a custom file (e.g. x = 0 returns P) or x if x isn't from '0' to '9'
    char getChar(char x);

    // isEnemyTile(other) returns true if other is an enemy char
    bool isEnemyTile(char other);

    // enemyNearPlayer() returns true if an enemy is near the player (one square away)
    bool enemyNearPlayer();

    // validCardinalMove(input) returns true if input is a valid cardinal direction
    bool validCardinalMove(std::string input);

    // getNewColumn(column, input) returns the new column if a player in the given
    // column moves in the cardinal direction input
    int getNewColumn(int column, std::string input);

    // getNewRow(row, input) returns the new row if a player in the given row
    // mves in the cardinal direction input
    int getNewRow(int row, std::string input);

    // validStepTile(r, c) returns true if char at (r, c) is a valid step tile
    // (e.g. G, \, ., etc.)
    bool validStepTile(int r, int c);

    // potionNearPlayer() returns true if there's a potion one square away from player
    bool potionNearPlayer();

    // rowInRange(row) returns true if row is in game board range
    bool rowInRange(int row);

    // columnInRange(column) returns true if column is in game board range
    bool columnInRange(int column);

    // removeGoldIfNecessary(row, column) removes gold at (row, column) if it exists
    void removeGoldIfNecessary(int row, int column);

    // enemyDropsGold(enemy) drops a gold at enemy's location 
    void enemyDropsGold(Enemy * enemy);

    // allMerchantsAttack() makes all merchants aggressive
    void allMerchantsAttack();

    // checkStairs(row, column) checks if stairs is at (row, column) and changes
    // beatLevel as necessary
    void checkStairs(int row, int column);

    // compare(enemy1, enemy2) returns -1, 0, 1 according to normal comparing 
    // conventions based on whether enemy1 is "before" enemy2, ie. if enemy1
    // is in a row higher up on the map or earlier column, and should move first
    int compare(Enemy * enemy1, Enemy * enemy2);

    // sortEnemies() sorts enemies by row first, then column (so the first enemy is
    // highest on map)
    void sortEnemies();
 
    // chooseLocation(character, playerChamber) randomly sets location of
    // character to a valid spot, and playerChamber is optional parameter
    // when setting the stairs
    void chooseLocation(Character &character, int playerChamber = -1);

public:
    // constructor
    Floor(Controller * controller, std::string playerType, std::string filename = "");

    // destructor
    ~Floor();

    // print() prints the controller's perspective of the board (used for debugging)
    void print();

    // getPlayer() returns the player (or potion decorator) 
    Playable * getPlayer();

    // getBeatLevel() returns beatLevel
    bool getBeatLevel();

    // playerMove() is called for the player to move a single turn
    void playerMove();

    // notifyCreated(character) notifies controller that character was created
    void notifyCreated(Character & character);

    // notifyPotionsSurrounding() notifies controller of potions surrounding player
    void notifyPotionsSurrounding();

    // notifyGold(gold) notifies controller that gold was obtained
    void notifyGold(Gold * gold);

    // notifyEnemyAttacked(enemy, amount) notifies controller that enemy
    // was attacked for amount damage
    void notifyEnemyAttacked(Enemy * enemy, int amount);

    // notifyAttackMissed() notifies controller that attack missed
    void notifyAttackMissed();

    // notifyPotion
    void notifyPotionUsed(int r, int c, std::string type);

    // notifyMoved(r1, c1, r2, c2, type) notifies controller that
    // character at (r1, c1) moved to (r2, c2) with optional type to indicate
    // that it was the player that moved
    void notifyMoved(int r1, int c1, int r2, int c2, std::string type = "");

    // notifyDead(character) notifies controller that character died
    void notifyDead(Character * character);

    // notifyPlayerDamaged(amount, type) notifies that player was
    // damaged by amount by an enemy of race type
    void notifyPlayerDamaged(int amount, std::string type);

    // notifyGoldDropped(enemy) notifies controller that gold was dropped
    // by enemy
    void notifyGoldDropped(Enemy * enemy);

    // enemiesMove() called for all enemies to make an action
    void enemiesMove();

    // getMapValue(row, column) returns the char at (row, column)
    int getMapValue(int row, int column);
};

#endif

