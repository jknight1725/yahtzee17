#include <include/scoreSheet.h>
#include <include/enumScore.h>

 //tally ones-sixes
int const ScoreSheet::upperScore() const {
    int upperScore {0};
    for(int i = 0; i < bonus; ++i) {
        upperScore += scores[i].value_or(0);
    }
    return upperScore;
}

//tally from threeKind to last score
int const ScoreSheet::lowerScore() const { 
    int lowerScore {0};
    for(int i = threeKind; i < scores.size(); ++i) {
        lowerScore += scores[i].value_or(0);
    }
    return lowerScore;
}

//tally all scores on sheet
int const ScoreSheet::totalScore() const { 
    int total {0};
    for(const auto& score : scores) {
        total += score.value_or(0);
    }
    return total;
}

bool ScoreSheet::available(int index) const {
    return !scores[index].has_value();
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
