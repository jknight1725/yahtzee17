#include "../include/scoreSheet.h"
#include "../include/enumScore.h"

int ScoreSheet::upperScore() const { //tally ones-sixes
    int upperScore {0};
    for(int i = 0; i < bonus; ++i) {
        upperScore += scores[i].first;
    }
    return upperScore;
}

int ScoreSheet::lowerScore() const { //tally from threeKind to last score
    int lowerScore {0};
    for(std::size_t i = threeKind; i < scores.size(); ++i) {
        lowerScore += scores[i].first;
    }
    return lowerScore;
}

int ScoreSheet::totalScore() const { //tally all scores on sheet
    int total {0};
    for(const auto& [points, _] : scores) {
        total += points;
    }
    return total;
}

bool ScoreSheet::available(int index) const {
    const auto [_, available] = scores[index];
    return available;
}

void ScoreSheet::makeUnavailable(int index) {
    auto& [_, available] = scores[index];
    available = false;
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
