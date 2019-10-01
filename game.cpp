#include "game.h"
#include <thread>
#include <chrono>

void Game::addPlayers(int x)  { //make x players
    for(int i = 0; i < x; ++i) {
        players.push_back(std::make_unique<Player>());
    }
}


void Game::menu() {
    std::cout << ascii_art << std::endl;
    std::cout << greeting << std::endl;
    int choice {-1};
    std::cin >> choice;
    while(std::cin.fail() || (choice < 0 || choice > 3)) //sanitize input
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cin >> choice;
    }
    switch(choice)
    {
        case(1):
            addPlayers(1);
            break;
        case(2):
            multiPlayer();
            break;
        case(3): {
            printHighScores();
            break;
        }
        default:
            break;
    }
}

void Game::multiPlayer() {
    std::cout << "How many players?\n";
    int choice{0};
    std::cin >> choice;
    while(std::cin.fail() || (choice < 0 )) //sanitize input
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cin >> choice;
    }
    addPlayers(choice);
}

void Game::turn() { //each player takes a turn in order
    for(const auto& player : players) {
        player->turn();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::saveScores() {
    std::ofstream scores {high_scores, std::ios::app};
    for (const auto& player : players) {
        scores << player->finalScore() << std::endl;
    }
}

std::vector<int> Game::loadScores() {
    std::ifstream saved {high_scores, std::ios::in};
    std::vector<int> scores;
    int score;
    while(saved >> score) {
        scores.emplace_back(score);
    }
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    return scores;
}

void Game::printHighScores() {
    int rank{1};
    std::cout << "HIGH SCORES\n\n";
    for (const auto &score : loadScores()) {
        std::cout << rank << ")\t" << score << "\n";
        ++rank;
    }
    menu();
}


