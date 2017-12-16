#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include "Controllers.hpp"
#include "Object.hpp"
#include <algorithm>

class Object;

class Actor
{
public:
    Actor(sf::Vector2f);
    virtual ~Actor() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void handleCollision(std::unique_ptr<Object> &) = 0;
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &);
    sf::FloatRect getSize() const;
protected:
    sf::Sprite sprite{};
    sf::Vector2f position{};
};

class Player : public Actor
{
public:
    Player(sf::Vector2f);
    ~Player() = default;
    void handleInput(sf::Event &);
    void handleCollision(std::unique_ptr<Object> &);
    void update(sf::Time &);
    void setPosition(sf::Vector2f);
    sf::FloatRect getSize();
private:
    void handleSlashing();
    void animate();
    
    std::unique_ptr<Controllers> controllers{};
    sf::Texture player{};
    sf::Clock slash_clock{};
    sf::Clock moving_clock{};
    bool slash{};
    char movement_direction{};
    float moving_speed;
};

#endif
