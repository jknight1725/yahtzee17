#include "player.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#ifndef _GAME_H
#define _GAME_H

class Game final {
public:
    Game() = default;
    ~Game() = default;
    Game(const Game& rhs) = delete;
    Game(Game&& rhs) = delete;
    Game& operator=(Game copy) = delete;
    void addPlayers(int x);
    void turn();
    void menu();
    void multiPlayer();
    void saveScores();
    void printHighScores();
    std::vector<int> loadScores();

private:
    std::vector<Player> players;
    std::string high_scores {"highScores.txt"};
    std::string ascii_art {
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
    std::string greeting {
            "Welcome Back\n"
            "Make a Selection\n"
            "1) Quick Game\n"
            "2) Multiplayer\n"
            "3) HighScores\n"
    };
};
#endif
