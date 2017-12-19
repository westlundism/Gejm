#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Game.hpp"
#include "Actor.hpp"
#include "Object.hpp"
#include "User_Interface.hpp"
#include "Button.hpp"

class Game;
class Player;
class Object;
class User_Interface;

class Game_State
{
public:
    Game_State(Game &, std::unique_ptr<Player> &,
               std::unique_ptr<User_Interface> &);
    virtual ~Game_State() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void handleCollision() {}
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
protected:
    Game & game;
    std::unique_ptr<Player> & player;
    std::unique_ptr<User_Interface> & ui;
    sf::Font font{};
};

class Main_Menu : public Game_State
{
public:
    Main_Menu(Game &, std::unique_ptr<Player> &,
              std::unique_ptr<User_Interface> &);
    ~Main_Menu() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
    sf::Sprite background_sprite{};
    sf::Texture background{};
    sf::Text title{};
    std::vector<std::unique_ptr<Button>> buttons{};
};

class In_Game : public Game_State
{
public:
    In_Game(Game &, std::unique_ptr<Player> &,
            std::unique_ptr<User_Interface> &);
    ~In_Game() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
    void handleCollision();
private:
    void drawWorld(sf::RenderWindow &);
    void constructObjects();

    std::vector<std::unique_ptr<Object>> objects{};
    sf::Sprite background_sprite{};
    sf::Texture world{};
    sf::Texture other{};
};

class In_House : public Game_State
{
public:
    In_House(Game &, std::unique_ptr<Player> &,
             std::unique_ptr<User_Interface> &);
    ~In_House() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
    void handleCollision();
private:
    void drawHouse(sf::RenderWindow &);
    void constructObjects();
    
    std::vector<std::unique_ptr<Object>> objects{};
    sf::Sprite background_sprite{};
    sf::Texture interior{};
    sf::Texture other{};
};

class Pause_Menu : public Game_State
{
public:
    Pause_Menu(Game &, std::unique_ptr<Player> &,
               std::unique_ptr<User_Interface> &);
    ~Pause_Menu() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
};

#endif
