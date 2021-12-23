#include <include/player.h>
#include <include/enumScore.h>
#include <vector>

//ACTION SECTION
void Player::rollAll() {
    dice.rollAll();
}

void Player::rollIndividual(int index) {
    dice.rollIndividual(index-1); // 1-5 maps to dice index[0..4]
}

void Player::displayDice() {
    dice.show();
}

void Player::displayScore() const {
    std::cout << scores;
}

/*
 * The turn opens with a roll of all of the dice
 * turnContinues() returns true if the player elects to keep rolling their dice
 * turnContinues() calls scoreSelection() and returns false if the player decides to stop rolling and score
 * scoreSelection() prompts the player to pick a score on the score sheet for their dice, only returning true
 * if a valid move is selected. A player selecting a score they have not scored yet,
 * while they do not meet score criteria is counted as 'taking a zero' on that score.
 * A player may not select a score they have already taken.
 */
void Player::turn() {
    rollAll();
    if(turnContinues()) { //choose to score or roll
        if(turnContinues())
            while(!scoreSelection()) //Returns true once a valid score is chosen
            {
                std::cout << "You already scored that section, select another!\n";
            }
    }
    displayScore();     //Show the updated scorecard to the player
}

//SCORING SECTION
int Player::totalOfDice() {
    return dice.total();
}

bool Player::topScore(int value) { //calculates scores for upper section, ones-sixes
    if(!scoreAvailable(value-1)) return false; //value-1 is correct index of that score i.e. ones are index zero
    int points = 0;
    for(const auto& die : dice) {
        if(die == value)
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


/*
 * Functions to check score for validity and record appropriate score
 *
 * The score sheet is checked for availability - returning false for an invalid move
 * The score criteria is compared against the dice values - if the move is valid record appropriate points
 * otherwise record a ZERO.
 *
 */
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


//joker rules - second yahtzee or greater
//attempt to score appropriate upper section
//else attempt to score in lower section
//first available of lg, sm, full, four, three, chance
//if all unavailable place zero in an available upper section

bool Player::yahtzee() { //first worth 50, each additional worth 100
    if(isYahtzee()) {
        if (scoreAvailable(score::yahtzee))
            recordScore(score::yahtzee, 50);
        else if (scores[score::yahtzee] == 50) {  // second yahtzee or greater if true
            recordScore(score::yahtzeeBonus, 100);

            if(scoreAvailable(dice[0]-1))
                recordScore(dice[0]-1,totalOfDice());
            else if(scoreAvailable(score::lgStraight))
                recordScore(score::lgStraight, 40);
            else if(scoreAvailable(score::smStraight))
                recordScore(score::smStraight, 30);
            else if(scoreAvailable(score::fullHouse))
                recordScore(score::fullHouse, 25);
            else if(scoreAvailable(score::fourKind))
                recordScore(score::fourKind, totalOfDice());
            else if(scoreAvailable(score::threeKind))
                recordScore(score::threeKind, totalOfDice());
            else if(scoreAvailable(score::chance))
                recordScore(score::chance, totalOfDice());
            else
                ;
        }
    }
    else {//record zero if not yahtzee
        recordScore(score::yahtzee, 0);
    }
    checkBonus(); // in case second yahtzee was scored on top
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
        if(dice.count(i) >= 3)
            return true;
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
    std::vector counts{
        dice.count(1),
        dice.count(2),
        dice.count(3),
        dice.count(4),
        dice.count(5),
        dice.count(6)
    };
    return std::find(counts.begin(),counts.end(), 3) != counts.end() &&
        std::find(counts.begin(),counts.end(), 2) != counts.end();
}

bool Player::isSmStraight() {
    std::vector counts{
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


// Two possible ways sorted dice can be a large straight, [1,2,3,4,5] and [2,3,4,5,6]
bool Player::isLgStraight() {
    dice.sort();
    //[1,2,3,4,5]
    if((dice[0] == 1) && (dice[1] == 2) && (dice[2] == 3) && (dice[3] == 4) && (dice[4] == 5))
        return true;
    else // [2,3,4,5,6] or false for lgStraight test
        return (dice[0] == 2) && (dice[1] == 3) && (dice[2] == 4) && (dice[3] == 5) && (dice[4] == 6);
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
    char choice {'0'};
    displayDice();
    std::cout << "Make a selection\n['r' Roll Again | 's' Score]\n";
    std::cin >> choice;
    choice = static_cast<char>(std::tolower(choice));
    while(std::cin.fail() || (choice != 'r' && choice != 's')) //sanitize input
    {
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
        default: //undefined behavior
            exit(0);
    }
}

void Player::nextRoll() { //player selects dice to re-roll
    std::vector<int> rerolls;
    int value {-1};
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
    for (const auto& reroll : rerolls)
        rollIndividual(reroll);
}

int Player::finalScore() {
    return scores.totalScore();
}

bool Player::scoreSelection() {
    int choice {0};
    displayScore();
    displayDice();
    std::cout << "Make a selection (1-13)\n";
    std::cin >> choice;
    while(std::cin.fail() || choice < 1 || choice > 13) //sanitize input
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        displayScore();
        displayDice();
        std::cout << "Invalid Selection, Try again! (1-13)\n";
        std::cin >> choice;
    }
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
        default: //Undefined Behavior
            exit(0);
    }
}
