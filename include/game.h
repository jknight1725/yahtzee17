#pragma once

#include <include/player.h>
#include <include/configs.h>
#include <vector>
#include <fstream>

class Game final {

public:
    void addPlayers(int x);
    void turn();
    void menu();
    void multiPlayer();
    void saveScores();
    void printHighScores();
    std::vector<int> loadScores();

private:
    std::vector<Player<Defaults::StandardDice>> players;
    const std::string highScoresFile {"highScores.txt"};
    
    const std::string banner {
            "\n\n"
            " #     #                                          \n"
            "  #   #    ##   #    # ##### ###### ###### ###### \n"
            "   # #    #  #  #    #   #       #  #      #      \n"
            "    #    #    # ######   #      #   #####  #####  \n"
            "    #    ###### #    #   #     #    #      #      \n"
            "    #    #    # #    #   #    #     #      #      \n"
            "    #    #    # #    #   #   ###### ###### ######   "
            "\n\n"
    };

    const std::string greeting {
            "Welcome Back\n"
            "Make a Selection\n"
            "1) Quick Game\n"
            "2) Multiplayer\n"
            "3) HighScores\n"
    };
};
