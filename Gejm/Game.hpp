#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Game_State.hpp"
#include <vector>

class Game_State;

class Game
{
public:
    Game();
    ~Game() = default;
    void run();
    void restart();
    void changeState(int);
private:
    std::vector<std::unique_ptr<Game_State>> states{};
    int active_state{};
};

#endif
