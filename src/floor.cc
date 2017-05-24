

#include "floor.h"
  #include "playable.h"
  #include "player.h"
  #include "enemy.h"
  #include "potion.h"
  #include "gold.h"
  #include "controller.h"
  #include "stairs.h"
  #include "view.h"
  
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <cstdlib>
  #include <fstream>
  
  using namespace std;

// see floor.h for documentation
  Floor::Floor(Controller * controller, string playerType, string filename)
  {
    beatLevel = false;
    
    temp = '.';
    
    string line;

    this->playerType = playerType;
    
    if (filename == "")
    {
      ifstream in("FloorLayout.txt");
    
      // read in the map into the tiles array
      for (int i = 0; i < 25; i++)
      {
        getline(in, line);
        for (int q = 0; q < 79; q++)
        {
          tiles[i][q] = line[q];
        }
      }
    
      // set controller 
      this->controller = controller;
    
      player = Player::getInstance(playerType);
    
      // get player and stairs and choose their locations, ensuring stairs isn't in same
      // chamber as player
      player->setGame(this);
      chooseLocation(*player);
    
      stairs = Stairs::getStairs(this);
      chooseLocation(*stairs, chamber);
    
      // temp pointers
      Gold * temp_gold;
      Potion * temp_potion;
      Enemy * temp_enemy;
    
      // number of dragons created from gold 
      int dragons;
    
      // fill the gold, potion, and enemy vectors
      for (int i = 0; i < 10; i++)
      {
        temp_gold = Gold::getGold(this);
        chooseLocation(*temp_gold);
        gold.push_back(temp_gold);
      }
    
      for (int i = 0; i < 10; i++)
      {
        temp_potion = Potion::getPotion(this);
        chooseLocation(*temp_potion);
        potions.push_back(temp_potion);
      }
    
      dragons = enemies.size();
    
      // fill enemies with 20 - dragons other enemies
      for (int i = 0; i < 20 - dragons; i++)
      {
        temp_enemy = Enemy::getEnemy(this);
        chooseLocation(*temp_enemy);
        enemies.push_back(temp_enemy);
      }
    
      // sort the enemies so we can iterate through it and move them
      // in appropriate order
      sortEnemies();
    }
    else
    {
      ifstream in(filename.c_str());
      Gold * temp_gold;
      Potion * temp_potion;
      Enemy * temp_enemy;

      this->controller = controller;

      for(int i = 0; i < 25; i++)
      {
        getline(in, line);

        for (int q = 0; q < 79; q++)
        {
          tiles[i][q] = getChar(line[q]);

          char x = line[q];

          if (x == '@')
          {
            player = Player::getInstance(playerType);
            player->setGame(this);
            player->setCood(i, q);
          }
          else if (x == 'H')
          {
            temp_enemy = Enemy::getEnemy(this, "H");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'D')
          {
            temp_enemy = Enemy::getEnemy(this, "D");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'E')
          {
            temp_enemy = Enemy::getEnemy(this, "E");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'W')
          {
            temp_enemy = Enemy::getEnemy(this, "W");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'O')
          {
            temp_enemy = Enemy::getEnemy(this, "O");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'M')
          {
            temp_enemy = Enemy::getEnemy(this, "M");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == 'L')
          {
            temp_enemy = Enemy::getEnemy(this, "L");
            temp_enemy->setCood(i, q);
            enemies.push_back(temp_enemy);
          }
          else if (x == '\\')
          {
            stairs = Stairs::getStairs(this);
            stairs->setCood(i, q);
          }
          else if ('0' <= x && x <= '5')
          {
            temp_potion = Potion::getPotion(this, x - '0');
            temp_potion->setCood(i, q);
            potions.push_back(temp_potion);
          }
          else if ('6' <= x && x <= '9')
          {
            temp_gold = Gold::getGold(this, x - '0');
            temp_gold->setCood(i, q);
            gold.push_back(temp_gold);
          }
        }
      }
    }
  }

  
// see floor.h for documentation
  Floor::~Floor()
  {
    // iterate through the vectors and delete the objects
    for (vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
      delete *i;
    }
    
    for (vector<Potion *>::iterator i = potions.begin(); i != potions.end(); i++)
    {
      delete *i;
    }
    
    for (vector<Gold *>::iterator i = gold.begin(); i != gold.end(); i++)
    {
      delete *i;
    }
    
    // delet stairs
    delete stairs;
    
    // if player is a potion decorator then call delete on it
    if (player->getOverallType() == "potion")
    {
      delete player;
    }
  }

// see floor.h for documentation
  char Floor::getChar(char x)
  {
    if ('0' <= x && x <= '5')       return 'P';
    else if ('6' <= x && x <= '9')  return 'G';
    else                            return x;
  }
  
// see floor.h for documentation
  void Floor::print()
  {
    for (int i = 0; i < 25; i++)
    {
      for (int q = 0; q < 79; q++)
      {
        cout << tiles[i][q];
      }
      cout << endl;
    }
  }
  
// see floor.h for documentation
  Playable * Floor::getPlayer()
  {
    return player;
  }
  
// see floor.h for documentation
  bool Floor::getBeatLevel()
  {
    return beatLevel;
  }
  
// see floor.h for documentation
  bool Floor::isEnemyTile(char other)
  {
    return (other == 'H' || other == 'D' || other == 'E' || other == 'O'
       || other == 'M' || other == 'W' || other == 'L');
  }
  
// see floor.h for documentation
  bool Floor::enemyNearPlayer()
  {
    int row = player->getRow();
    int column = player->getCol();
    int enemyRow;
    int enemyColumn;
    
    // iterate through the enemy vector
    for(vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
      enemyRow = (*i)->getRow();
      enemyColumn = (*i)->getCol();
      
      // if enemyRow and enemyColumn are within 1 square of player return true
      if (row - enemyRow >= -1 && row - enemyRow <= 1)
      {
        if (column - enemyColumn >= -1 && column - enemyColumn <= 1)
        {
          return true;
        }
      }
    }
    
    return false;
  }
  
// see floor.h for documentation
  bool Floor::rowInRange(int row)
  {
    return (0 <= row && row < 25);
  }
  
// see floor.h for documentation
  bool Floor::columnInRange(int column)
  {
    return (0 <= column && column < 79);
  }
  
// see floor.h for documentation
  bool Floor::validCardinalMove(string input)
  {
    if (input == "no" || input == "so" || input == "ea" || input == "we" ||
        input == "ne" || input == "nw" || input == "se" || input == "sw")
    {
      return true;
    }
    
    return false;
  }
  
// see floor.h for documentation
  int Floor::getNewColumn(int column, string input)
  {
    // moving north or south doesn't change column
    if (input == "no" || input == "so")
    {
      return column;
    }
    // having east or west component changes column
    else if (input == "ne" || input == "ea" || input == "se")
    {
      return column + 1;
    }
    else
    {
      return column - 1;
    }
  }
  
// see floor.h for documentation
  int Floor::getNewRow(int row, string input)
  {
    // moving east or west doesn't change row
    if (input == "ea" || input == "we")
    {
      return row;
    }
    // having north or south component changes row
    else if (input == "ne" || input == "no" || input == "nw")
    {
      return row - 1;
    }
    else
    {
      return row + 1;
    }
  }
  
// see floor.h for documentation
  bool Floor::validStepTile(int r, int c)
  {
    char tile = tiles[r][c];
    
    return (tile == '.' || tile == 'G' || tile == '+' || tile == '#' || tile == '\\');
  }
  
// see floor.h for documentation
  bool Floor::potionNearPlayer()
  {
    int row = getPlayer()->getRow();
    int col = getPlayer()->getCol();
    
    // iterate through squares surrounding player, and if there's a P return true
    for (int i = -1; i <= 1; i++)
    {
      for (int q = -1; q <= 1; q++)
      {
        if ((rowInRange(row + i) && columnInRange(col + q)) && tiles[row + i][col + q] == 'P')
        {
          return true;
        }
      }
    }
    
    return false;
  }
  
// see floor.h for documentation
  void Floor::removeGoldIfNecessary(int row, int column)
  {
    // iterate through gold vector
    for (vector<Gold *>::iterator i = gold.begin(); i != gold.end(); i++)
    {
      // if the row and column of the gold is same as arguments
      if ((*i)->getRow() == row && (*i)->getCol() == column)
      {
        notifyGold(*i);
        
        player->changeGold((*i)->getValue());
        
        notifyDead(*i);
        
        delete (*i);
        
        gold.erase(i);
        break;
      }
    }
  }
  
// see floor.h for documentation
  void Floor::enemyDropsGold(Enemy * enemy)
  {
    string type = enemy->getType();
    int row = enemy->getRow();
    int column = enemy->getCol();
    
    Gold * temp_gold;
    
    // drop a different type of gold depending on type of enemy
    if (type == "human")
    {
      temp_gold = Gold::getHumanGold(this);
    }
    else if (type == "merchant")
    {
      temp_gold = Gold::getMerchantGold(this);
    }
    else if (type != "dragon")
    {
      temp_gold = Gold::getOrdinaryDrop(this);
    }
    else
    {
      return;
    }
    
    // set the gold's location to the enemy, notify created, and push into vector
    temp_gold->setCood(row, column);
    notifyCreated(*temp_gold);
    
    gold.push_back(temp_gold);
  }
  
// see floor.h for documentation
  void Floor::allMerchantsAttack()
  {
    // find all merchants and set their attack to true
    for (vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
      if ((*i)->getType() == "merchant")
      {
        (*i)->setAttack(true);
      }
    }
  }
  
// see floor.h for documentation
  void Floor::checkStairs(int row, int column)
  {
    // check if the tile is the stairs and set beatLevel
    beatLevel = (tiles[row][column] == '\\');
    
    // if beatLevel then we remove the stairs 
    if (beatLevel)
    {
      tiles[row][column] = '.';
      notifyDead(stairs);
    }
  }
  
// see floor.h for documentation
  void Floor::playerMove()
  {
    // input receives commands
    string input;
    
    // row and column are the player's current position
    int row = getPlayer()->getRow();
    int column = getPlayer()->getCol();
    
    // newRow, newColumn hold values around the player square
    int newRow;
    int newColumn;
    
    // whether the player made a move
    bool moveDone = false;
    
    while(true)
    {
      cin >> input;
      
      // if input was a valid cardinal move
      if (validCardinalMove(input))
      {
        // get the row and column associated with that direction relative to
        // current position
        newRow = getNewRow(row, input);
        newColumn = getNewColumn(column, input);
        
        // if the newRow and newColumn are in game board range and a valid step tile
        if ((rowInRange(newRow) && columnInRange(newColumn)) && validStepTile(newRow, newColumn))
        {
          // remove the gold and stairs at that new location if necessary
          removeGoldIfNecessary(newRow, newColumn);
          checkStairs(newRow, newColumn);
          
          // player moves to that new location
          player->move(newRow, newColumn);
          
          // player made a move
          moveDone = true;
        }
      }
      // if input was to use a potion
      else if (input == "u")
      {
        // if there is in fact a potion near player
        if (potionNearPlayer())
        {
          bool potionUsed = false;
          
          // keep reading in until player enters a valid cardinal direction
          // of a potion
          while (true)
          {
            cin >> input;
            
            // if valid cardinal move
            if (validCardinalMove(input))
            {
              newRow = getNewRow(row, input);
              newColumn = getNewColumn(column, input);
              
              // if the new square is in game board and is a potion
              if ((rowInRange(newRow) && columnInRange(newColumn)) && tiles[newRow][newColumn] == 'P')
              {
                int potionRow, potionColumn;
                
                // iterate through potion vector
                for (vector<Potion *>::iterator i = potions.begin(); i != potions.end(); i++)
                {
                  potionRow = (*i)->getRow();
                  potionColumn = (*i)->getCol();
                  
                  // when the desired potion is found
                  if (potionRow == newRow && potionColumn == newColumn)
                  {
                    // set the potion's pointer to player
                    (*i)->takePotion(player);
                    
                    // player now refers to the potion decorator and change
                    // its coordinates to the player
                    player = *i;
                    (*i)->setCood(row, column);
                    
                    // set the tile at the potion's former location to '.'
                    tiles[newRow][newColumn] = '.';
                    
                    // erase that potion from the vector
                    potions.erase(i);
                    potionUsed = true;
                    break;
                  }
                }
              }
            }
            
            // if a potion was used then moveDone is true
            if (potionUsed)
            {
              moveDone = true;
              break;
            }
          }
        }
      }
      // documentation for attack is very similar to potion use, and so
      // similar documentation is mostly omitted
      else if (input == "a")
      {
        if (enemyNearPlayer())
        {
          bool enemyAttacked = false;
          
          while (true)
          {
            cin >> input;
            
            if (validCardinalMove(input))
            {
              newRow = getNewRow(row, input);
              newColumn = getNewColumn(column, input);
              
              if ((rowInRange(newRow) && columnInRange(newColumn)) && isEnemyTile(tiles[newRow][newColumn]))
              {
                int enemyRow, enemyColumn;
                
                for (vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); i++)
                {
                  enemyRow = (*i)->getRow();
                  enemyColumn = (*i)->getCol();
                  
                  // when desired enemy is found by iterating through vector
                  if (enemyRow == newRow && enemyColumn == newColumn)
                  {
                    // enemy gets damage taken by player
                    (*i)->takeDamage(*player, playerType);
                    enemyAttacked = true;
                    
                    // if attacked enemy was merchant then all merchants
                    // should now attack
                    if ((*i)->getType() == "merchant")
                    {
                      allMerchantsAttack();
                    }
                    
                    // if the enemy's health is 0 
                    if ((*i)->getHp() == 0)
                    {
                      // gold is dropped
                         if ((*i)->getType() != "dragon"){
                          notifyGoldDropped(*i);
                         }
                      enemyDropsGold(*i);
                      
                      // clean up memory, delete from vector
                      delete (*i);
                      enemies.erase(i);
                      
                      // if player is a goblin then gains 5 gold
                      if (playerType == "g")
                      {
                        player->changeGold(5);
                      }
                    }
                    
                    break;
                  }
                }
              }
            }
            
            if (enemyAttacked)
            {
              moveDone = true;
              break;
            }
          }
        }
      }
      // if player restarts
      else if (input == "r")
      {
        moveDone = true;
        controller->setRestart(true);
      }
      // if player quits
      else if (input == "q")
      {
        moveDone = true;
        controller->setPlay(false);
      }
      
      // if the move is done
      if (moveDone)
      {
        notifyPotionsSurrounding();

        // if the player's health is 0 then game over
        if (player->getHp() == 0)
        {
          gameOn = false;
          
          return;
        }
        
        // if the player's type is troll then gain health
        if (playerType == "t")
        {
          player->changeHp(5);
        }
        
        return;
      }
    }
  }
  
// see floor.h for documentation
  int Floor::getMapValue(int row, int column)
  {
    return tiles[row][column];
  }
  
// see floor.h for documentation
  int Floor::compare(Enemy * enemy1, Enemy * enemy2)
  {
    // the rows and columns of the enemies
    int row1 = enemy1->getRow();
    int column1 = enemy1->getCol();
    int row2 = enemy2->getRow();
    int column2 = enemy2->getCol();
    
    // compare first based on row, then column
    if (row1 < row2)        return -1;
    else if (row1 > row2)   return 1;
    else
    {
      if (column1 < column2)        return -1;
      else if (column1 > column2)   return 1;
      else                    return 0;
    }
  }
  
// see floor.h for documentation
  void Floor::sortEnemies()
  {
    int length = enemies.size();
    
    Enemy * temp = NULL;
    
    // bubble sorts the enemies vector
    for (int i = length - 1; i >= 0; i--)
    {
      for (int q = 0; q < i; q++)
      {
        if (compare(enemies.at(q), enemies.at(i)) == 1)
        {
          temp = enemies.at(q);
          enemies.at(q) = enemies.at(i);
          enemies.at(i) = temp;
        }
      }
    }
  }
  
// see floor.h for documentation
  void Floor::enemiesMove()
  {
    // assumes enemy vector already sorted
    
    // iterate through vector and have enemy do action
    for (vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
      (*i)->action();
      
      // after each enemy's action, return if player died
      if (player->getHp() == 0) return;
    }
    
    sortEnemies();
  }


// see floor.h for documentation
  void Floor::notifyPotionsSurrounding()
  {
    int row = player->getRow();
    int column = player->getCol();

    int cardinal = 1;

    int * directions = new int[8];

    int length = 0;

    for (int i = -1; i <= 1; i++)
    {
      for (int q = -1; q <= 1; q++)
      {
        if (tiles[row + i][column + q] == 'P')
        {
          directions[length] = cardinal;
          length++;
        }

        if (!(i == 0 && q == 0)) cardinal++;
      }
    }

    controller->notifyDisplayPotionsSurrounding(directions, length);
  }

  
// see floor.h for documentation
  void Floor::notifyGold(Gold * gold)
  {
    controller->notifyDisplayGold(gold);
    
    tiles[gold->getRow()][gold->getCol()] = 'G';
  }
  
// see floor.h for documentation
  void Floor::notifyEnemyAttacked(Enemy * enemy, int amount)
  {
    controller->notifyDisplayEnemyAttacked(enemy, amount);
  }
  
// see floor.h for documentation
  void Floor::notifyAttackMissed()
  {
    controller->notifyDisplayAttackMissed();
  }
  
// see floor.h for documentation
  void Floor::notifyPotionUsed(int r, int c, string type)
  {
    controller->notifyDisplayPotionUsed(r, c, type);
    
    tiles[r][c] = '.';
  }
  
// see floor.h for documentation
  void Floor::notifyMoved(int r1, int c1, int r2, int c2, string type)
  {
    controller->notifyDisplay(r1, c1, r2, c2, type);
    
    // if the type is player or potion then we have to update 
    // the temp variable too, otherwise we can just swap the chars
    if (type == "player"||type == "potion") {
      char temp1 = tiles[r2][c2];
      tiles[r2][c2] = tiles[r1][c1];
      tiles[r1][c1] = temp;
      temp = temp1;
    } else {
      char temp1 = tiles[r2][c2];
      tiles[r2][c2] = tiles[r1][c1];
      tiles[r1][c1] = temp1;
    }
  }
  
// see floor.h for documentation
  void Floor::notifyDead(Character * character)
  {
    controller->notifyDisplayDead(character);
    
    tiles[character->getRow()][character->getCol()] = '.';
  }
  
// see floor.h for documentation
  void Floor::notifyCreated(Character & character)
  {
    controller->notifyDisplayCreated(character);
    
    string overallType = character.getOverallType();
    string type = character.getType();
    int row = character.getRow();
    int column = character.getCol();
    
    // based on overallType and type, change the square at 
    // the character's row and column as necessary
    if (overallType == "player")
    {
      tiles[row][column] = '@';
    }
    else if (overallType == "potion")
    {
      tiles[row][column] = 'P';
    }
    else if (overallType == "gold")
    {
      tiles[row][column] = 'G';
    }
    else if (overallType == "stairs")
    {
      tiles[row][column] = '\\';
    }
    else
    {
      if (type == "human")
      {
        tiles[row][column] = 'H';
      }
      else if (type == "dwarf")
      {
        tiles[row][column] = 'W';
      }
      else if (type == "elf")
      {
        tiles[row][column] = 'E';
      }
      else if (type == "orc")
      {
        tiles[row][column] = 'O';
      }
      else if (type == "merchant")
      {
        tiles[row][column] = 'M';
      }
      else if (type == "dragon")
      {
        tiles[row][column] = 'D';
      }
      else
      {
        tiles[row][column] = 'L';
      }
    }
  }
  
// see floor.h for documentation
  void Floor::notifyPlayerDamaged(int amount, string type)
  {
    controller->notifyDisplayPlayerDamaged(amount, type);
  }
  
// see floor.h for documentation
  void Floor::notifyGoldDropped(Enemy * enemy)
  {
    controller->notifyDisplayGoldDropped(enemy);
    
    tiles[enemy->getRow()][enemy->getCol()] = 'G';
  }
  
// see floor.h for documentation
  void Floor::chooseLocation(Character &character, int playerChamber) {
    //playerChamber is needed because when we choose location for stairs, it should not be in the same chamber as player, so
    //if we are choosing location for stairs, playerChamber = the player's chamber, otherwith it is -1 by default
    int temp=playerChamber;
    int r, c;
    bool taken = true;
    while (taken) {
      temp = rand() % 5; //randomly generate a number between 0 to 4
      if (temp == playerChamber) continue;//if it is the same chamber as the player's chamber, choose again
       //if it's the first chamber
      if (temp == 0) {
        int row = 4;
        int col = 25;
        int cood = rand() % (row*col);
        r = 4 + cood / col;
        c = 4 + cood % col; 
      } else if (temp == 1) {       //if it's the second chamber
        int row = 7;
        int col = 20;
        int cood = rand() % (row*col);
        r = 16 + cood / col;
        c = 5 + cood % col; 
      } else if (temp == 2) {      //if it's the third chamber
        int row = 3;
        int col = 12;
        int cood = rand() % (row*col);
        r = 11 + cood / col;
        c = 39 + cood % col; 
      } else if (temp == 3) {      //if it's the forth chamber
        int cood = rand() % 201;
        if (cood < 46) {
          r = 4 + cood / 23;
          c = 40 + cood % 23; 
        } else if (cood < 77) {
          r = 6;
          c = 40 + cood - 46;
        } else if (cood < 111) {
          r = 7;
          c = 40 + cood - 77;
        } else {
          r = 8 + (cood - 111)/15;
          c = 62 + (cood - 111)%15;
        }
      } else {      //if it's the fifth chamber
        int cood = rand() % 150;
        if (cood < 33) {
          r = 17 + cood / 11;
          c = 66 + cood % 11;
        } else {
          r = 20 + (cood - 33)/39;
          c = 38 + (cood - 33)%39;
        }
      }
      --r;
      --c;
       
       //check if the tile is empty
      if (tiles[r][c] == '.') 
           taken = false;
      // if the thing we are choosing location for is a dragon hoard, choose a location for dragon
      if (character.getType() == "gold" && character.getHoard() == "dragon hoard") {
        bool aroundTaken = true;
         //looking for an empty tile for the dragon
        for (int i=r-1; i<r+1; i++) {
          for (int j=c-1; j<c+1; j++) {
            if (i!=r && j!=c && tiles[i][j]=='.'){
              aroundTaken = false;
              Enemy* dragon = Enemy::getDragon(this); //creating dragon
              dragon->setCood(i, j);
              enemies.push_back(dragon);
              notifyCreated(*dragon);
              break;
            }
          }
          if (!aroundTaken) break;
        }
        if (!taken && !aroundTaken) break;//if the tile is 
      }
    }
    character.setCood(r, c);
    if (character.getOverallType() == "player")
      chamber = temp;                //if it is a player, record which chamber it is in
    notifyCreated(character);      //notify the character is created
  }


