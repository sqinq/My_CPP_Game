#include "controller.h"

int main(int argc, char* argv[])
{
    // create a controller and call play game
    Controller controller;
    if (argc > 1) {
        controller.playGame(argv[1]);
    } else {
         controller.playGame();
    }
}

