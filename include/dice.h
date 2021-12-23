#pragma once

#include <array>
#include <iostream>
#include <random>

/// @tparam NUM_DICE The amount of die to use
/// @tparam MAX_PIPS How many sides each die will have
template<auto NUM_DICE = 5, auto MAX_PIPS = 6>
class Dice final {

public:
    Dice()
    {
        this->rollAll();
    }

    void rollAll() noexcept {
        std::for_each(dice.begin(),dice.end(),[](auto& d){ d = getRandomDie(); });
    }

    void rollIndividual(int index) noexcept {
        dice.at(index) = getRandomDie();
    }

    void sort() noexcept {
        std::sort(dice.begin(), dice.end());
    }

    void show() const noexcept {
        std::for_each(dice.begin(),dice.end(),[](const auto& die){ std::cout << '[' << die << ']' << ' '; });
        std::cout << "\n"   " ^   ^   ^   ^   ^\n"
                            " |   |   |   |   |\n"
                            " 1   2   3   4   5\n";
    }

    int total() const noexcept {
        return std::reduce(dice.cbegin(), dice.cend());
    }

    auto count(int value) const noexcept {
        return std::count(dice.cbegin(), dice.cend(), value);
    } 

    [[nodiscard]] constexpr auto size() const noexcept{
        return NUM_DICE;
    }

    inline std::size_t operator [] (const std::size_t index) const  {
        return dice.at(index); 
    }

    inline auto static getRandomDie() noexcept {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::uniform_int_distribution<int> pips{1, MAX_PIPS};
        return pips(generator);
    }

    using iterator =  typename std::array<int, NUM_DICE>::iterator;
    using const_iterator = typename std::array<int, NUM_DICE>::const_iterator;
    inline iterator begin() noexcept { return dice.begin(); }
    inline const_iterator cbegin() const noexcept { return dice.cbegin(); }
    inline iterator end() noexcept { return dice.end(); }
    inline const_iterator cend() const noexcept { return dice.cend(); }

private:
    std::array<int, NUM_DICE> dice;
};

