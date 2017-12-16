#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "Actor.hpp"

class Game;

class Object
{
public:
    Object(sf::Vector2f);
    virtual ~Object() = default;
    virtual bool canCollide() const = 0;
    virtual void update(sf::Time &) {}
    void draw(sf::RenderWindow &);
    sf::FloatRect getSize() const;
    sf::Vector2f getPosition() const;
protected:
    sf::Vector2f position{};
    sf::Sprite sprite{};
};

class Outdoor_Object : public Object
{
public:
    Outdoor_Object(sf::Vector2f);
    ~Outdoor_Object() = default;
protected:
    sf::Texture texture_pack_1{};
    sf::Texture texture_pack_2{};
};

class Interior_Object : public Object
{
public:
    Interior_Object(sf::Vector2f);
    ~Interior_Object() = default;
protected:
    sf::Texture interior_pack{};
};

class Entrance : public Outdoor_Object
{
public:
    Entrance(sf::Vector2f);
    ~Entrance() = default;
    bool canCollide() const;
};

class House : public Outdoor_Object
{
public:
    House(sf::Vector2f);
    ~House() = default;
    bool canCollide() const;
};

class Grave : public Outdoor_Object
{
public:
    Grave(sf::Vector2f);
    ~Grave() = default;
    bool canCollide() const;
};

class Living_Tree : public Outdoor_Object
{
public:
    Living_Tree(sf::Vector2f);
    ~Living_Tree() = default;
    bool canCollide() const;
    void update(sf::Time &);
private:
    sf::Clock animation{};
};

class Door_Mat : public Interior_Object
{
public:
    Door_Mat(sf::Vector2f);
    ~Door_Mat() = default;
    bool canCollide() const;
};
#endif
