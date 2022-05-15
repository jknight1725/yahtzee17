#include <array>
#include <iostream>

#ifndef _scoreSheet_H
#define _scoreSheet_H

 /// Array of 15 <int/bool> pairs corresponding to different yahtzee scores.
 /// bool indicates if the score sheet has already recorded the respective score
 /// sheet can read/write/tally/print its scores

class ScoreSheet final
{
public:
    ScoreSheet() noexcept { //by default all scores set to zero
        for(auto& [points, available] : scores) {
            points = 0;
            available = true;
        }
    }
    int upperScore() const;
    int lowerScore() const;
    int totalScore() const;
    bool available(int index) const;
    void makeUnavailable(int index);
    int const& operator [] (int index) const {return scores[index].first;}
    int& operator[] (int index) {return scores[index].first;}
    friend std::ostream & operator<<(std::ostream & out, const ScoreSheet& sheet);

private:
    std::array<std::pair<int, bool>, 15> scores;
};

#endif
