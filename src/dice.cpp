#include "../include/dice.h"
#include <random>
#include <algorithm>
#include <numeric>

static std::random_device rd; //seed generator
static std::mt19937 generator(rd()); //generate random numbers


void Dice::rollAll() {
    for(auto& die : dice)
        die = sides(generator);
}

void Dice::rollIndividual(int index) {
    dice[index] = sides(generator);
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
    return std::reduce(dice.cbegin(), dice.cend());
}

void Dice::sort() { //sort dice lowest to highest
    std::sort(dice.begin(), dice.end());
}

int Dice::count(int value) const { //how many times a die appears in dice
    return static_cast<int>(std::count(dice.cbegin(),dice.cend(),value));
}
