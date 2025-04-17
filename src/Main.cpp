#include "Game.h"
#include<bits/stdc++.h>

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.Run();
    return 0;
}