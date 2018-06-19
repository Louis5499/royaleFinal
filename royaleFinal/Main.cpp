#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *RoyaleGame = new GameWindow();

    RoyaleGame->game_play();

    delete RoyaleGame;
    return 0;
}
