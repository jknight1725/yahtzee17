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

void Dice::rollIndividual(std::size_t index) {
    dice[index] = sides(generator);
}

void Dice::display() const noexcept {
    for(const auto& die : dice) {
        std::cout << '[' << die << ']' << ' ';
    }
    std::cout << std::endl;
    std::cout << " ^   ^   ^   ^   ^\n"
                 " |   |   |   |   |\n"
                 " 1   2   3   4   5\n";
}

int Dice::sum() const noexcept {
    return std::accumulate(dice.cbegin(), dice.cend(), 0);
}

void Dice::sort() {
    std::sort(dice.begin(), dice.end());
}

int Dice::count(int value) const noexcept {
    return std::count(dice.cbegin(),dice.cend(),value);
}
