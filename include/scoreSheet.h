#pragma once

#include <array>
#include <iostream>
#include <optional>

class ScoreSheet final
{

private:
    std::array<std::optional<int>, 15> scores;

public:
    int const upperScore() const;
    int const lowerScore() const;
    int const totalScore() const;
    bool available(int index) const;
    int const operator [] (int index) const {return scores[index].value_or(0);}
    std::optional<int>& operator[] (int index) {return scores[index];}
    friend std::ostream & operator<<(std::ostream & out, const ScoreSheet& sheet);
};
