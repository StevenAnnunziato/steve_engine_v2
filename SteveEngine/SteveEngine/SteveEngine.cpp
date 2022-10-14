//#include <crtdbg.h>


#include "System.h"
#include "Game.h"

#include "Utils.h"

int main(int argc, char* argv[])
{

    Vector2 size(800, 600);

    Game::initInstance();
    Game::getInstance()->initGame(size);

    Game::getInstance()->cleanupGame();
    Game::cleanupInstance();

    return 0;
}
