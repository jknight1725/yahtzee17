#include <array>
#include <iostream>
#include <random>

#ifndef _DICE_H
#define _DICE_H
/*
Defines a set of five dice that can change their values to a random number
in a specified range (1,6) upon being rolled.
*/
class Dice final {
private:
    std::array<int, 5> dice;
    std::uniform_int_distribution<int> sides;

public:
    Dice() : sides {1, 6},
             dice {0,0,0,0,0}
             {
             }
    ~Dice() = default;
    
    void rollAll(); //roll every die
    void rollIndividual(int index); //roll one selected die
    void sort(); //lowest - highest
    void show() const; //display all die
    int total() const; //sum of all die
    int count(int value) const; //how many times a die appears in dice
    auto size() const {return dice.size();} //number of die in dice
    int operator [] (int index) const  {return dice[index];} //read dice

    // iterators - treat dice class like a container
    using iterator = std::array<int, 5>::iterator;
    using const_iterator = std::array<int, 5>::const_iterator;
    inline iterator begin() noexcept { return dice.begin(); }
    inline const_iterator cbegin() const noexcept { return dice.cbegin(); }
    inline iterator end() noexcept { return dice.end(); }
    inline const_iterator cend() const noexcept { return dice.cend(); }
};
#endif
