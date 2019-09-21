#include "player.h"
#include "enumScore.h"
#include <vector>


//ACTION SECTION
void Player::rollAll() {
    dice.rollAll();
}

void Player::rollIndividual(int index) {
    dice.rollIndividual(index);
}

void Player::displayDice() {
    dice.show();
}

void Player::displayScore() {
    std::cout << scores;
}

void Player::turn() {
    rollAll(); //turn opens with a roll of all dice
    if(turnContinues()) { //choose to score or roll
        if(turnContinues())
            while(!scoreSelection()) { //until valid score is selected
                std::cout << "You already scored that section, select another!\n";
            } //turn over after three rolls
    }
    displayScore();
}

//SCORING SECTION
int Player::totalOfDice() {
    return dice.total();
}

bool Player::topScore(int value) { //calculates scores for upper section
    if(!scoreAvailable(value-1)) return false;
    int points = 0;
    for(int i = 0; i < dice.size(); i++) {
        if(dice[i] == value)
            points += value;
    }
    recordScore(value-1, points);
    checkBonus(); //determine and apply bonus
    return true;
}


void Player::recordScore(int index, int points) {
    scores[index] += points;
    scores.makeUnavailable(index);
}

bool Player::scoreAvailable(int index) {
    return scores.available(index);
}

bool Player::threeKind() { //worth total of dice
    if (!scoreAvailable(score::threeKind)) return false;
    isThreeKind() ? recordScore(score::threeKind, totalOfDice()) : recordScore(score::threeKind, 0);
    return true;
}

bool Player::fourKind() { //worth total of dice
    if (!scoreAvailable(score::fourKind)) return false;
    isFourKind() ? recordScore(score::fourKind, totalOfDice()) : recordScore(score::fourKind, 0);
    return true;
}

bool Player::fullHouse() { //worth 25 points
    if (!scoreAvailable(score::fullHouse)) return false;
    isFullHouse() ? recordScore(score::fullHouse, 25) : recordScore(score::fullHouse, 0);
    return true;
}

bool Player::smStraight() { //worth 30 points
    if (!scoreAvailable(score::smStraight)) return false;
    isSmStraight() ? recordScore(score::smStraight, 30) : recordScore(score::smStraight, 0);
    return true;
 }

bool Player::lgStraight() { //worth 40 points
    if (!scoreAvailable(score::lgStraight)) return false;
    isLgStraight() ? recordScore(score::lgStraight, 40) : recordScore(score::lgStraight, 0);
    return true;
}

bool Player::yahtzee() { //first worth 50, each additional worth 100
    if(isYahtzee()) {
        if(scoreAvailable(score::yahtzee))
            recordScore(score::yahtzee, 50);
        else
            recordScore(score::yahtzee, 100);
    }
    recordScore(score::yahtzee, 0);
    return true;
}

bool Player::chance() {
    if(isChance()) {
        recordScore(score::chance, totalOfDice());
        return true;
    }
    return false;
}

void Player::checkBonus() {
    if(scores.upperScore() >= 63 && scoreAvailable(score::bonus))
        recordScore(score::bonus, 35);
}

//VALIDATION SECTION
bool Player::isThreeKind() {
    for(int i = 1; i < 7; i++) { //count the number of times 1-6 are found in dice
        if(dice.count(i) >= 3) {
            return true;
        }
    }
    return false;
}

bool Player::isFourKind() {
    for(int i = 1; i < 7; i++) { //count the number of times 1-6 are found in dice
        if(dice.count(i) >= 4)
            return true;
    }
    return false;
}

bool Player::isFullHouse() { //pair of three and pair of two
    std::vector<int> counts{
        dice.count(1),
        dice.count(2),
        dice.count(3),
        dice.count(4),
        dice.count(5),
        dice.count(6)
    };
    for(auto count : counts) { //look for pair of three
        if(count == 3) { //pair of three found
            for(auto c : counts) { //look for pair of two
                if(c == 2) //pair of two found
                    return true;
            }
        }
    }
    return false;
}

bool Player::isSmStraight() {
    std::vector<int> counts{
            dice.count(1),
            dice.count(2),
            dice.count(3),
            dice.count(4),
            dice.count(5),
            dice.count(6)
    };
    //smStraight must have one three and one four but no more than 2 of either
    if((counts[score::threes] < 1) || (counts[score::threes] > 2))
        return false;
    else if((counts[score::fours] < 1) || (counts[score::fours] > 2))
        return false;
    //dice is guaranteed a 3 and 4 now. A 1/2 , 2/5, or 5/6 completes the straight
    else if((counts[score::ones] >= 1) && (counts[score::twos] >= 1))
        return true;
    else if((counts[score::twos] >= 1) && (counts[score::fives] >= 1))
        return true;
    //true if last condition met, false otherwise
    else return (counts[score::fives] >= 1) && (counts[score::sixes] >= 1);
}

bool Player::isLgStraight() { //two possible ways to obtain
    dice.sort();
    // 1,2,3,4,5
    if((dice[0]==1)&&(dice[1]==2)&&(dice[2]==3)&&(dice[3]==4)&&(dice[4]==5))
        return true;
    //true if [2,3,4,5,6] false otherwise
    else return (dice[0] == 2) && (dice[1] == 3) && (dice[2] == 4) && (dice[3] == 5) && (dice[4] == 6);
}

bool Player::isChance() {
    return scoreAvailable(score::chance);
}

bool Player::isYahtzee() {
    for (int i = 1; i < dice.size(); i++) { //compare die 2-5 to first die
        if (dice[i] != dice[0]) //if not equal, not a yahtzee
            return false;
    }
    return true;
}

bool Player::turnContinues() { //roll again or select a score
    char choice = '0';
    displayDice();
    std::cout << "Make a selection\n['r' Roll Again | 's' Score]\n";
    std::cin >> choice;
    choice = static_cast<char>(std::tolower(choice));
    while(std::cin.fail() || (choice != 'r' && choice != 's')) { //if bad input
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        displayScore();
        std::cout<<"Invalid Selection\n['r' Roll Again | 's' Score]\n";
        displayDice();
        std::cin >> choice;
    }
    switch(choice)
    {
        case('r'):
            nextRoll();
            return true;
        case('s'):
            while(!scoreSelection()) {
                std::cout << "You already scored that section, select another!\n";
            }
            return false;
        default:
            std::cout << "Program terminating.";
            exit(0);
    }
}

void Player::nextRoll() { //player selects dice to re-roll
    std::vector<int> rerolls;
    int value = -1;
    std::cout << "Pick which die to re-roll(1-5)\nEnter 0 when complete\n";
    while(value != 0) {
        std::cin >> value;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cin >> value;
        }
        if(value > 0 && value < 6)
            rerolls.push_back(value);
    }
    for (auto reroll : rerolls)
        rollIndividual(reroll);
}

bool Player::scoreSelection() {
    int choice = 0;
    displayScore();
    displayDice();
    std::cout << "Make a selection (1-13)\n";
    std::cin >> choice;
    while(std::cin.fail() || choice < 1 || choice > 13) { //if bad input
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        displayScore();
        displayDice();
        std::cout<<"Invalid Selection, Try again! (1-13)\n";
        std::cin >> choice;
    } //while
    switch(choice)
    {
        case(1):
            return topScore(1);
        case(2):
            return topScore(2);
        case(3):
            return topScore(3);
        case(4):
            return topScore(4);
        case(5):
            return topScore(5);
        case(6):
            return topScore(6);
        case(7):
            return threeKind();
        case(8):
            return fourKind();
        case(9):
            return fullHouse();
        case(10):
            return smStraight();
        case(11):
            return lgStraight();
        case(12):
            return yahtzee();
        case(13):
            return chance();
        default: 
            std::cout << "Program terminating.";
            exit(0);
    }
    
}
