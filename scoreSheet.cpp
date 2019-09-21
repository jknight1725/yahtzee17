#include "scoreSheet.h"
#include "enumScore.h"

ScoreSheet::ScoreSheet() { //by default all scores set to zero
    for(auto& [points, available] : scores) {
        points = 0;
        available = true;
    }
}

int const ScoreSheet::upperScore() const { //tally ones-sixes
    int upperScore = 0;
    for(int i = 0; i < bonus; ++i) {
        upperScore += scores[i].first;
    }
    return upperScore;
}

int const ScoreSheet::lowerScore() const { //tally from threeKind to last score
    int lowerScore = 0;
    for(int i = threeKind; i < scores.size(); ++i) {
        lowerScore += scores[i].first;
    }
    return lowerScore;
}

int const ScoreSheet::totalScore() const { //tally all scores on sheet
    return upperScore() + lowerScore();
}

bool ScoreSheet::available(int index) const {
    return scores[index].second;
}

void ScoreSheet::makeUnavailable(int index) {
    scores[index].second = false;
}

std::ostream & operator<<(std::ostream & out, const ScoreSheet& sheet)
{
    out << "\n\n"
    << "(1)Ones:          "   << sheet[ones] << "\t\t"
    << "(7)3 of a kind:    "  << sheet[threeKind] << "\n\n"
    << "(2)Twos:          "   << sheet[twos] << "\t\t"
    << "(8)4 of a kind:    "  << sheet[fourKind] << "\n\n"
    << "(3)Threes:        "   << sheet[threes] << "\t\t"
    << "(9)Full House:     "  << sheet[fullHouse] << "\n\n"
    << "(4)Fours:         "   << sheet[fours] << "\t\t"
    << "(10)Sm. Straight:  "  << sheet[smStraight] << "\n\n"
    << "(5)Fives:         "   << sheet[fives] << "\t\t"
    << "(11)Lg. Straight:  "  << sheet[lgStraight] << "\n\n"
    << "(6)Sixes:         "   << sheet[sixes] << "\t\t"
    << "(12)Yahtzee:       "  << sheet[yahtzee] << "\n\n\t\t\t\t"
    << "(13)Chance:        "  << sheet[chance] << "\t\t\n\n"
    << "Bonus:            "   << sheet[bonus] <<"\t\t"
    << "Upper Score:       "  << (sheet.upperScore() + sheet[bonus]) << "\n\n"
    << "Yahtzee Bonus:    "   << sheet[yahtzeeBonus] << "\t\t"
    << "Lower Score:       "  << sheet.lowerScore() << "\n\n\t\t\t\t"
    << "Total:             "  << sheet.totalScore() << "\n\n";
    return out;
}
