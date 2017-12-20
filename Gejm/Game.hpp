#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Game_State.hpp"
#include "Actor.hpp"
#include "User_Interface.hpp"
#include <vector>

namespace constants
{
    const int windowWidth = 1280;
    const int windowHeight = 960;
}

class Game_State;
class Player;

class Game
{
public:
    Game();
    ~Game() = default;
    void run();
    void restart();
    void quitGame();
    void changeState(int);
    int getState() const;
private:
    std::vector<std::unique_ptr<Game_State>> states{};
    std::unique_ptr<Player> player;
    std::unique_ptr<User_Interface> ui;
    int activeState{};
    bool quit{};
};

#endif
