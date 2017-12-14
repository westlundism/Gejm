#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>

class Actor
{
public:
    Actor() = default;
    virtual ~Actor() = default;
    virtual void handleInput(sf::Event &) = 0;
    virtual void update(sf::Time &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
protected:
};

class Player : public Actor
{
public:
    Player();
    ~Player() = default;
    void handleInput(sf::Event &);
    void update(sf::Time &);
    void draw(sf::RenderWindow &);
private:
};

#endif
