#include "dice.h"
#include "player.h"
#include "scoreSheet.h"
#include "game.h"
#include "enumScore.h"
//A game of yahtzee
int main()
{
    Game game;
    game.menu();
    for(int i = 0; i < 13; ++i) {
        game.turn();
    }
    game.saveScores();
}
