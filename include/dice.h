#include <array>
#include <iostream>
#include <random>

#pragma once

/// Defines a set of five dice that can change their values to a random number
/// in a specified range (1,6) upon being rolled.

class Dice final {
public:
    Dice() : dice {0,0,0,0,0}, sides {1, 6}
    {
    }

    using iterator = std::array<int, 5>::iterator;
    using const_iterator = std::array<int, 5>::const_iterator;
    
    void rollAll();
    void rollIndividual(std::size_t index);
    void sort(); 
    void display() const noexcept;
    int sum() const noexcept;
    int count(int value) const noexcept;

    std::size_t size() const {
        return dice.size();
    }

    int operator [](std::size_t index) const {
        return dice[index];
    }

    inline iterator begin() noexcept {
        return dice.begin();
    }

    inline const_iterator cbegin() const noexcept {
        return dice.cbegin();
    }

    inline iterator end() noexcept {
        return dice.end(); 
    }

    inline const_iterator cend() const noexcept {
        return dice.cend(); 
    }
    
private:
    std::array<int, 5> dice;
    std::uniform_int_distribution<int> sides;
};
