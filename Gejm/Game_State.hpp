#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Game.hpp"
#include "Actor.hpp"

class Game;

class Game_State
{
public:
    Game_State(Game &);
    virtual ~Game_State() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
protected:
    Game & game;
    sf::Sprite sprite{};
    sf::Font font{};
};

class Main_Menu : public Game_State
{
public:
    Main_Menu(Game &);
    ~Main_Menu() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
    sf::Texture background{};
    sf::Text title{};
};

class In_Game : public Game_State
{
public:
    In_Game(Game &);
    ~In_Game() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
    void drawWorld(sf::RenderWindow &);
    std::unique_ptr<Player> player{};
    sf::Texture world{};
};

class Pause_Menu : public Game_State
{
public:
    Pause_Menu(Game &);
    ~Pause_Menu() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
};

#endif