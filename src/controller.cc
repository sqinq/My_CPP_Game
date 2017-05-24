#include "controller.h"
#include "display.h"
#include "view.h"
#include "floor.h"
#include "character.h"
#include "gold.h"
#include "player.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// see controller.h for documentation
Controller::Controller()
{
    view = NULL;
    game = NULL;
    level = 1;
    restart = false;
    play = true;
}

// see controller.h for documentation
Controller::~Controller()
{
    delete view;
    delete game;
}

// see controller.h for documentation
void Controller::setRestart(bool other)
{
    restart = other;
}

// see controller.h for documentation
void Controller::setPlay(bool other)
{
    play = other;
}

// see controller.h for documentation
string Controller::getPlayerType(string input)
{
    // note that we require input to be appropriate in order to generate
    // predictable results
    if (input == "s")       return "Shade";
    else if (input == "d")  return "Drow";
    else if (input == "v")  return "Vampire";
    else if (input == "g")  return "Goblin";
    else                    return "Troll";
}

// see controller.h for documentation
void Controller::playGame(string filename)
{
    // input receives commands
    string input;

    // randomly seed using time
    srand(time(NULL));

    Playable * player = NULL;

    // the entire game lifecycle loop (when breaks, everything ends)
    while(play)
    {
        // restart initially set to false
        restart = false;

        cout << "Enter a race: ";

        // read in the race
        while(true)
        {
            cin >> input;   

            if (input == "s" || input == "d" || input == "v" || input == "g" || input == "t")
            {
                break;
            }
        }

        // create a new game and view
        view = new Display(getPlayerType(input), filename);
        game = new Floor(this, input, filename);

        // call view's print so we can see the game
        view->print(game->getPlayer(), level);

        // player keeps track of the game's player at all times (singleton in Player class)
        player = game->getPlayer();

        // the command loop for a single game
        while(true)
        {
            // player's move
            game->playerMove();

            // if restart, quit, or loss, then break out of this single game
            if (checkRestart() || checkQuit() || checkLoss()) break;

            // if user beat a level
            if (checkBeatLevel())
            {
                // if user also won then break out of single game
                if (checkWin()) break;

                // otherwise game should keep going, so delete view and game and
                // create another
                delete view;
                delete game;

                view = new Display(getPlayerType(input));
                game = new Floor(this, input);

                // and print it for the user to see
                view->print(game->getPlayer(), level);
            }
            else
            {
                // if nothing special happened (restart, quit, loss, beat level, win)
                // then enemies move
                game->enemiesMove();

                // if loss then break out of single game
                if (checkLoss()) break;

                // print again for player to see
                view->print(game->getPlayer(), level);
            }
        }

        // if user still wants to play (represented using play variable)
        if (play && (! restart))
        {
            // does player want to play again?
            cout << "Do you want to play again? (y/n)" << endl;

            while(true)
            {
                cin >> input;

                if (input == "y" || input == "Y")
                {
                    // if yes, set the level back to 1, clean up memory, and go back to 
                    // top of loop
                    level = 1;
                    delete player;

                    delete game;
                    delete view;

                    break;
                }
                // if not then we exit from the loop by setting play to false
                else if (input == "n" || input == "N")
                {
                    play = false;
                    break;
                }
            }
        }
        else if (play && restart)
        {
            delete player;
        }
    }

    // at the very end of the game cycle we must delete the singleton player
    delete player;
}

// see controller.h for documentation
bool Controller::checkQuit()
{
    // play determines whether or not to quit
    if (! play)
    {
        notifyDisplayQuit();
        view->print(game->getPlayer(), level);

        delete game;
        delete view;

        game = NULL;
        view = NULL;

        return true;
    }

    return false;
}

// see controller.h for documentation
bool Controller::checkRestart()
{
    // restart determines whether or not to restart
    if (restart)
    {
        restart = true;
        notifyDisplayRestart();
        view->print(game->getPlayer(), level);

        delete game;
        delete view;

        game = NULL;
        view = NULL;

        level = 1;

        return true;
    }

    return false;
}

// see controller.h for documentation
bool Controller::checkWin()
{
    // if level is 6 then player won 
    if (level == 6)
    {
        notifyDisplayWon(game->getPlayer());
        view->print(game->getPlayer(), level);

        delete view;
        delete game;

        view = NULL;
        game = NULL;

        return true;
    }

    return false;
}

// see controller.h for documentation
bool Controller::checkLoss()
{
    // if health is 0 then player lost
    if (game->getPlayer()->getHp() == 0)
    {
        notifyDisplayLoss(game->getPlayer());
        view->print(game->getPlayer(), level);

        delete view;
        delete game;

        view = NULL;
        game = NULL;

        return true;
    }

    return false;
}

// see controller.h for documentation
bool Controller::checkBeatLevel()
{
    // if the game indicates that player beat the level by reaching stairs
    // then returns true
    if (game->getBeatLevel())
    {
        level++;
        notifyDisplayStairs();

        view->print(game->getPlayer(), level);

        return true;
    }

    return false;
}

// see controller.h for documentation
void Controller::notifyDisplay(int r1, int c1, int r2, int c2, string type)
{
    view->change(r1, c1, r2, c2, type);
}

// see controller.h for documentation
void Controller::notifyDisplayDead(Character * character)
{
    view->dead(character);
}

// see controller.h for documentation
void Controller::notifyDisplayGold(Gold * gold)
{
    view->gold(gold);
}

// see controller.h for documentation
void Controller::notifyDisplayPotionsSurrounding(int * directions, int length)
{
    view->potionsSurrounding(directions, length);
}

// see controller.h for documentation
void Controller::notifyDisplayPotionUsed(int r, int c, string type)
{
    view->potionUsed(r, c, type);
}

// see controller.h for documentation
void Controller::notifyDisplayEnemyAttacked(Enemy * enemy, int amount)
{
    view->enemyAttacked(enemy, amount);
}

// see controller.h for documentation
void Controller::notifyDisplayAttackMissed()
{
    view->attackMissed();
}

// see controller.h for documentation
void Controller::notifyDisplayWon(Playable * player)
{
    view->notifyWon(player);
}

// see controller.h for documentation
void Controller::notifyDisplayLoss(Playable * player)
{
    view->notifyLoss(player);
}

// see controller.h for documentation
void Controller::notifyDisplayRestart()
{
    view->notifyRestart();
}

// see controller.h for documentation
void Controller::notifyDisplayQuit()
{
    view->notifyQuit();
}

// see controller.h for documentation
void Controller::notifyDisplayCreated(Character & character)
{
    view->notifyCreated(character);
}

// see controller.h for documentation
void Controller::notifyDisplayStairs()
{
    view->notifyStairs();
}

// see controller.h for documentation
void Controller::notifyDisplayPlayerDamaged(int amount, string type)
{
    view->notifyPlayerDamaged(amount, type);
}

// see controller.h for documentation
void Controller::notifyDisplayGoldDropped(Enemy * enemy)
{
    view->notifyGoldDropped(enemy);
}



