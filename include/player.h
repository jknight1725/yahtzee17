#include "dice.h"
#include "scoreSheet.h"

#ifndef _Player_H
#define _Player_H
/*
Player has dice and a score sheet
Player rolls dice during turns and checks if their dice are valid scores before placing
appropriate score on sheet.
 */
class Player final
{
private:
    Dice dice;
    ScoreSheet scores;
public:
    Player() = default;
    ~Player() = default;
    Player(const Player& rhs) = delete;
    Player(Player&& rhs) = delete;
    Player& operator=(Player copy) = delete;

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
    int finalScore();
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
