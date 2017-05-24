#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class View;
class Floor;
class Playable;
class Character;
class Enemy;
class Gold;

#include <string>

class Controller
{
    // the display
    View * view;

    // the game
    Floor * game;

    // the current level number
    int level;

    // whethe user wants to continue playing
    bool play;

    // whether user wants to restart
    bool restart;

    // checkQuit() returns true if user wants to quit
    bool checkQuit();

    // checkRestart() returns true if user wants to restart
    bool checkRestart();

    // checkWin() returns true if user won the game
    bool checkWin();

    // checkLoss() returns true if user lost the game
    bool checkLoss();

    // checkBeatLevel() returns true if user beat the level 
    bool checkBeatLevel();

public:
    // constructor
    Controller();

    // destructor
    ~Controller();

    // setRestart(other) sets restart to other
    void setRestart(bool other);

    // setPlay(other) sets play to other
    void setPlay(bool other);

    // getPlayerType(input) returns the appropriate string player type
    // based on input
    std::string getPlayerType(std::string input);

    // playGame() is the full lifecycle of the game 
    void playGame(std::string filename = "");

    // notifyDisplay(r1, c1, r2, c2, type) notifies the display that the entity
    // at (r1, c1) moved to (r2, c2) and type helps identify the character
    void notifyDisplay(int r1, int c1, int r2, int c2, std::string type);

    // notifyDisplayDead(character) notifies display that character died
    void notifyDisplayDead(Character * character);

    // notifyDisplayPotionsSurrounding(directions, length) notifies display
    // of potions surrounding player using directions array with length given
    // as argument
    void notifyDisplayPotionsSurrounding(int * directions, int length);

    // notifyDisplayGold(gold) notifies display that gold has been dropped
    void notifyDisplayGold(Gold * gold);

    // notifyDisplayPotionUsed(r, c, type) notifies display that potion
    // of variety type at (r, c) was used
    void notifyDisplayPotionUsed(int r, int c, std::string type);

    // notifyDisplayEnemyAttacked(enemy, amount) notifies display that enemy
    // was attacked for amount damage
    void notifyDisplayEnemyAttacked(Enemy * enemy, int amount);

    // notifyDisplayAttackMissed() notifies display the player's attack missed
    void notifyDisplayAttackMissed();

    // notifyDisplayWon(player) notifies display that player won
    void notifyDisplayWon(Playable * player);

    // notifyDisplayLoss(player) notifies display that player lost
    void notifyDisplayLoss(Playable * player);

    // notifyDisplayRestart() notifies display that player restarted
    void notifyDisplayRestart();

    // notifyDisplayQuit() notifies display that player quit
    void notifyDisplayQuit();

    // notifyDisplayCreated(charater) notifies display that character was created
    void notifyDisplayCreated(Character & character);

    // notifyDisplayStairs() notifies display that stairs was reached
    void notifyDisplayStairs();

    // notifyDisplayPlayerDamaged(amount, type) notifies display that an enemy
    // of variety type damaged player for amount damage
    void notifyDisplayPlayerDamaged(int amount, std::string type);

    // notifyDisplayGoldDropped(enemy) notifies display that enemy dropped gold
    void notifyDisplayGoldDropped(Enemy * enemy);
};

#endif

