#include "player.h"
#include <vector>
#include <memory>

#ifndef _GAME_H
#define _GAME_H
//dynamically allocates players and gives them turns
class Game final {
private:
    std::vector<std::unique_ptr<Player>> players; //store players
public:
    Game() = default;
    ~Game() = default;
    Game(const Game& rhs) = delete;
    Game(Game&& rhs) = delete;
    Game& operator=(Game copy) = delete;
    explicit Game(int x); //dynamically allocate x players
    void turn(); //call turn on every player
};
#endif
