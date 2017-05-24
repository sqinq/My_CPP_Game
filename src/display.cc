#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "enemy.h"
#include "playable.h"
#include "display.h"
#include "character.h"
#include "gold.h"

using namespace std;

// see display.h for documentation
Display::Display(string type, string filename)
{
    playerType = type;
    string line;

    ifstream * in;

    if (filename == "")
    {
        in = new ifstream("FloorLayout.txt");
    }
    else
    {
        in = new ifstream(filename.c_str());
    }

    // read into the map using FloorLayout.txt
    for (int i = 0; i < 25; i++)
    {
        getline(*in, line);
        for (int q = 0; q < 79; q++)
        {
            squares[i][q] = getChar(line[q]);
        }
    }
     
     // player starts on a normal floor tile
     temp = '.';

    // action initially set to empty string
    action = "";

    delete in;
}

// see display.h for documentation
Display::~Display()
{

}

// see display.h for documentation
char Display::getChar(char x)
{
    if ('0' <= x && x <= '5')       return 'P';
    else if ('6' <= x && x <= '9')  return 'G';
    else                            return x;
}

// see display.h for documentation
string Display::getCardinal(int row, int column)
{
    // based on row and column, returns the appropriate cardinal direction
    // but we require row and column to be between -1 and 1
    if (row == 1)
    {
        if (column == 1)       return "south east";
        else if (column == 0)  return "south";
        else                   return "south west";
    }
    else if (row == 0)
    {
        if (column == 1)       return "east";
        else                   return "west";
    }
    else
    {
        if (column == 1)       return "north east";
        else if (column == 0)  return "north";
        else                   return "north west";
    }
}

// see display.h for documentation
string Display::getSingleCardinal(int cardinal)
{
    if      (cardinal == 1) return "north west";
    else if (cardinal == 2) return "north";
    else if (cardinal == 3) return "north east";
    else if (cardinal == 4) return "west";
    else if (cardinal == 5) return "east";
    else if (cardinal == 6) return "south west";
    else if (cardinal == 7) return "south";
    else                    return "south east";
}

// see display.h for documentation
void Display::print(Playable * player, int level)
{
    cout << endl;

    // print the whole board
    for (int i = 0; i < 25; i++)
    {
        for (int q = 0; q < 79; q++)
        {
            cout << squares[i][q];
        }

        cout << endl;
    }

    // print relevant game stats
    cout << "Race: " << playerType << " Gold: " << player->getGold() << setw(50) << "Floor: " << level << endl;
    cout << "HP: " << player->getHp() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    cout << "Action: " << action << endl;

    cout << endl;

    // action is now empty string to prepare for next turn
    action = "";
}

// see display.h for documentation
void Display::change(int r1, int c1, int r2, int c2, string type)
{ 
    // if the type is player or potion, we need to update temp as well
    // we essentially swap the chars at (r1, c1) and (r2, c2)
    if (type == "player"||type == "potion") {
         char temp1 = squares[r2][c2];
        squares[r2][c2] = squares[r1][c1];
        squares[r1][c1] = temp;
        temp = temp1;
    } else {
         char temp1 = squares[r2][c2];
         squares[r2][c2] = squares[r1][c1];
         squares[r1][c1] = temp1;
    }

    // if type is player or potion we append to the action string that the
    // player moved
    if (type == "player"||type == "potion")
    {
        stringstream ss;
        ss << "PC moves " << getCardinal(r2 - r1, c2 - c1) << ". ";
        action += ss.str();
    }
}

// see display.h for documentation
void Display::potionsSurrounding(int * directions, int length)
{
    if (length == 0)
    {
        delete [] directions;
        return;
    }

    action += "Player sees unknown potion ";

    for (int i = 0; i < length; i++)
    {
        action += getSingleCardinal(directions[i]);

        if (i == length - 1)
        {
            action += ". ";
        }
        else
        {
            action += ", ";
        }
    }

    delete [] directions;
}

// see display.h for documentation
void Display::potionUsed(int r, int c, string type)
{
    stringstream ss;
    ss << "PC uses " << type << ". ";
    action += ss.str();
    squares[r][c] = '.';
}

// see display.h for documentation
void Display::gold(Gold * gold)
{
    stringstream ss;

    // gold->getHoard() gets the name string of the hoard (e.g. merchant hoard)
    ss << "PC obtained " << gold->getHoard() << ". ";
    action += ss.str();
}

// see display.h for documentation
void Display::dead(Character * character)
{
    int row = character->getRow();
    int column = character->getCol();
    squares[row][column] = '.';
}

// see display.h for documentation
void Display::enemyAttacked(Enemy * enemy, int amount)
{
    stringstream ss;

    int newHp = enemy->getHp() - amount;

    newHp = (newHp < 0)? 0 : newHp;

    ss << "PC deals " << amount << " damage to " << enemy->getType() << "(" << newHp << " HP). ";
    action += ss.str();
}

// see display.h for documentation
void Display::attackMissed()
{
    action += "PC's attack missed... ";
}

// see display.h for documentation
void Display::notifyWon(Playable * player)
{
    stringstream ss;

    int score;

    if (playerType == "Shade")
    {
        score = player->getGold() * 1.5;
    }
    else
    {
        score = player->getGold();
    }

    ss << "PC has escaped the dungeon! \n\n**FINAL SCORE** " << score;
    action += ss.str();
}

// see display.h for documentation
void Display::notifyLoss(Playable * player)
{
    stringstream ss;

    int score;

    if (playerType == "Shade")
    {
        score = player->getGold() * 1.5;
    }
    else
    {
        score = player->getGold();
    }

    ss << "PC has been slain! \n\n**FINAL SCORE** " << score;
    action += ss.str();
}

// see display.h for documentation
void Display::notifyRestart()
{
    action += "Restarting...";
}

// see display.h for documentation
void Display::notifyQuit()
{
    action += "Quitting...";
}

// see display.h for documentation
void Display::notifyCreated(Character & character)
{
    // we first get relevant variables from character
    string overallType = character.getOverallType();
    string type = character.getType();
    int row = character.getRow();
    int column = character.getCol();

    // depending on the overallType and type of character, we draw the
    // appropriate symbol at (row, column)
    if (overallType == "player")
    {
        squares[row][column] = '@';
        action += "Player character has spawned. ";
    }
    else if (overallType == "potion")
    {
        squares[row][column] = 'P';
    }
    else if (overallType == "gold")
    {
        squares[row][column] = 'G';
    }
    else if (overallType == "stairs")
    {
        squares[row][column] = '\\';
    }
    else
    {
        if (type == "human")
        {
            squares[row][column] = 'H';
        }
        else if (type == "dwarf")
        {
            squares[row][column] = 'W';
        }
        else if (type == "elf")
        {
            squares[row][column] = 'E';
        }
        else if (type == "orc")
        {
            squares[row][column] = 'O';
        }
        else if (type == "merchant")
        {
            squares[row][column] = 'M';
        }
        else if (type == "dragon")
        {
            squares[row][column] = 'D';
        }
        else
        {
            squares[row][column] = 'L';
        }
    }
}

// see display.h for documentation
void Display::notifyStairs()
{
    action += "PC reached stairs. Moving on... ";
}

// see display.h for documentation
void Display::notifyPlayerDamaged(int amount, string type)
{
    stringstream ss;
    ss << type << " deals " << amount << " damage to PC. ";
    action += ss.str();
}

// see display.h for documentation
void Display::notifyGoldDropped(Enemy * enemy)
{
    squares[enemy->getRow()][enemy->getCol()] = 'G';
}


