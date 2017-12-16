#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Game_State.hpp"
#include <vector>

namespace constants
{
    const int window_width = 1280;
    const int window_height = 960;
}

class Game_State;

class Game
{
public:
    Game();
    ~Game() = default;
    void run();
    void restart();
    void changeState(int);
    int getState() const;
private:
    std::vector<std::unique_ptr<Game_State>> states{};
    int active_state{1};
};

#endif
