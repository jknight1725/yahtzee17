#include "dice.h"
#include "scoreSheet.h"

#ifndef _Player_H
#define _Player_H

/// Player has dice and a score sheet
/// Player rolls dice during turns and checks if their dice are valid scores before placing
/// appropriate score on sheet.

class Player final {
public:
    void rollAll();
    void rollIndividual(int index);
    void displayDice();
    void displayScore() const;
    void turn();
    bool turnContinues();
    void nextRoll();
    bool scoreSelection();
    void recordScore(int index, int points);
    bool scoreAvailable(int index);
    int totalOfDice();
    bool topScore(int value);
    bool threeKind();
    bool fourKind();
    bool fullHouse();
    bool smStraight();
    bool lgStraight();
    bool yahtzee();
    bool chance();
    void checkBonus();
    int finalScore();
    bool isThreeKind();
    bool isFourKind();
    bool isFullHouse();
    bool isSmStraight();
    bool isLgStraight();
    bool isChance();
    bool isYahtzee();

private:
    Dice dice;
    ScoreSheet scores;
};

#endif
