#include "game.h"
#include <thread>
#include <chrono>

Game::Game(int x) { //make x players
    for(int i = 0; i < x; ++i) {
        players.push_back(std::make_unique<Player>());
    }
}

void Game::turn() { //each player takes a turn in order
    for(const auto& player : players) {
        player->turn();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
