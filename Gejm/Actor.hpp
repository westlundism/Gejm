#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include "Controllers.hpp"

class Actor
{
public:
    Actor() = default;
    virtual ~Actor() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
protected:
    sf::Sprite sprite{};
};

class Player : public Actor
{
public:
    Player();
    ~Player() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
    void hitObject(sf::Sprite &);
    sf::FloatRect getSize();
private:
    sf::Texture player{};
    sf::Vector2f position{};
    std::unique_ptr<Controllers> controllers{};
};

#endif
