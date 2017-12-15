#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include "Controllers.hpp"

class Actor
{
public:
    Actor(sf::Vector2f);
    virtual ~Actor() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void handleCollision() = 0;
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
protected:
    sf::Sprite sprite{};
    sf::Vector2f position{};
};

class Player : public Actor
{
public:
    Player();
    ~Player() = default;
    void handleInput(sf::Event &);
    void handleCollision();
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
    sf::FloatRect getSize();
private:
    void handleSlashing();
    void animate();
    
    std::unique_ptr<Controllers> controllers{};
    sf::Texture player{};
    sf::Clock slash_clock{};
    sf::Clock moving_clock{};
    bool slash{false};
    char movement_direction{};
};

#endif
