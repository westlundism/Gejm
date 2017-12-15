#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
public:
    Object(sf::Vector2f);
    virtual ~Object() = default;
    virtual void update(sf::Time &) {}
    void draw(sf::RenderWindow &);
    sf::FloatRect getSize() const;
protected:
    sf::Vector2f position{};
    sf::Sprite sprite{};
};

class Outdoor_Object : public Object
{
public:
    Outdoor_Object(sf::Vector2f);
    ~Outdoor_Object() = default;
    virtual void update(sf::Time &) {}
protected:
    sf::Texture texture_pack_1{};
    sf::Texture texture_pack_2{};
};

class House : public Outdoor_Object
{
public:
    House(sf::Vector2f);
    ~House() = default;
};

class Grave : public Outdoor_Object
{
public:
    Grave(sf::Vector2f);
    ~Grave() = default;
};

class Living_Tree : public Outdoor_Object
{
public:
    Living_Tree(sf::Vector2f);
    ~Living_Tree() = default;
    void update(sf::Time &);
private:
    sf::Clock animation{};
};
#endif
