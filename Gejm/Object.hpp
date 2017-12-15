#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object
{
public:
    Object(sf::Vector2f);
    virtual ~Object() = default;
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
protected:
    sf::Texture texture{};
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
#endif
