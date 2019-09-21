#include "dice.h"
#include "scoreSheet.h"

#ifndef _Player_H
#define _Player_H
/*
Player has dice and a score sheet
Player rolls dice during turns and checks if their dice are valid scores before placing
appropriate score on sheet.
 */
class Player
{
private:
    Dice dice;
    ScoreSheet scores;
public:
    //action section
    void rollAll();
    void rollIndividual(int index);
    void displayDice();
    void displayScore();
    void turn();
    bool turnContinues(); //choose to score or roll
    void nextRoll(); //continue turn, choose which dice to roll
    bool scoreSelection(); //end turn, choose score
    //scoring section
    void recordScore(int index, int points);
    bool scoreAvailable(int index);
    int totalOfDice();
    bool topScore(int value); //score 1-6
    bool threeKind();
    bool fourKind();
    bool fullHouse();
    bool smStraight();
    bool lgStraight();
    bool yahtzee();
    bool chance();
    void checkBonus(); //if appropriate apply topScore bonus
    //validation section
    bool isThreeKind();
    bool isFourKind();
    bool isFullHouse();
    bool isSmStraight();
    bool isLgStraight();
    bool isChance();
    bool isYahtzee();
};

#endif
