#include "../include/dice.h"
#include "../include/player.h"
#include "../include/scoreSheet.h"
#include "../include/game.h"
#include "../include/enumScore.h"
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
