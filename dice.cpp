#include "dice.h"
#include <random>
#include <algorithm>

static std::random_device rd; //seed generator
static std::mt19937 generator(rd()); //generate random numbers


void Dice::rollAll() {
    for(auto& die : dice)
        die = sides(generator);
}

void Dice::rollIndividual(int index) { //TODO: currently relies on promise of sanitized input from player class
    dice[index-1] = sides(generator);
}

void Dice::show() const {
    for(const auto& die : dice) {
        std::cout << '[' << die << ']' << ' ';
    }
    std::cout << std::endl;
    std::cout << " ^   ^   ^   ^   ^\n"
                 " |   |   |   |   |\n"
                 " 1   2   3   4   5\n";
}

int Dice::total() const { //sum dice
    return std::reduce(dice.begin(), dice.end());
}

void Dice::sort() { //sort dice lowest to highest
    std::sort(dice.begin(), dice.end());
}

int Dice::count(int value) const { //how many times a die appears in dice
    return std::count(dice.begin(),dice.end(),value);
}
