#include "player.h"
#include <vector>
#include <memory>
#include <fstream>
#include <string>

#ifndef _GAME_H
#define _GAME_H
//dynamically allocates players and gives them turns
class Game final {
private:
    std::vector<Player> players; //store players
    std::string high_scores {"highScores.txt"};
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
