#include "main.h"
#include "Game.h"
#include <iostream>

using namespace Motherload;

int main(int argc, char* argv[])
{
    Game game;
    Game::instance->startup();
    return 0;
}
