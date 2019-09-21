#include <array>
#include <iostream>

#ifndef _scoreSheet_H
#define _scoreSheet_H
/*
 Array of 15 <int/bool> pairs corresponding to different yahtzee scores.
 bool indicates if the score sheet has already recorded the respective score
 sheet can read/write/tally/print its scores
 */
 
class ScoreSheet
{
private:
    std::array<std::pair<int, bool>, 15> scores;
public:
    //Only allow construction and destruction no move/copy operations
    ScoreSheet();
    ~ScoreSheet() = default;
    ScoreSheet(const ScoreSheet& rhs) = delete;
    ScoreSheet(ScoreSheet&& rhs) = delete;
    ScoreSheet& operator=(ScoreSheet copy) = delete;


    int const upperScore() const;
    int const lowerScore() const;
    int const totalScore() const;
    bool available(int index) const;
    void makeUnavailable(int index);
    int const& operator [] (int index) const {return scores[index].first;}
    int& operator[] (int index) {return scores[index].first;}
    friend std::ostream & operator<<(std::ostream & out, const ScoreSheet& sheet);
};

#endif
