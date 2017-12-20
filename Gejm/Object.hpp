#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include "Actor.hpp"

class Game;
class Player;

class Object
{
public:
    Object(sf::Vector2f);
    virtual ~Object() = default;
    virtual bool canCollide() const {}
    virtual void update(sf::Time &) {}
    void draw(sf::RenderWindow &);
    virtual void handleCollision(std::unique_ptr<Player> &);
    sf::FloatRect getSize() const;
    sf::Vector2f getPosition() const;
    bool isDestroyed() const;
protected:
    sf::Vector2f position{};
    sf::Sprite sprite{};
    bool destroyed{};
};

class Outdoor_Object : public Object
{
public:
    Outdoor_Object(sf::Vector2f);
    ~Outdoor_Object() = default;
protected:
    sf::Texture worldPack{};
    sf::Texture objectPack{};
};

class Interior_Object : public Object
{
public:
    Interior_Object(sf::Vector2f);
    ~Interior_Object() = default;
protected:
    sf::Texture interiorPack{};
};

class Dynamic_Object : public Object
{
public:
    Dynamic_Object(sf::Vector2f);
    ~Dynamic_Object() = default;
protected:
    sf::Texture worldPack{};
    sf::Texture objectPack{};
};

class House : public Outdoor_Object
{
public:
    House(sf::Vector2f);
    ~House() = default;
    bool canCollide() const override;
};

class Grave : public Outdoor_Object
{
public:
    Grave(sf::Vector2f);
    ~Grave() = default;
    bool canCollide() const override;
};

class Living_Tree : public Outdoor_Object
{
public:
    Living_Tree(sf::Vector2f);
    ~Living_Tree() = default;
    bool canCollide() const override;
    void update(sf::Time &) override;
private:
    sf::Clock animationClock{};
};

class Fountain : public Outdoor_Object
{
public:
    Fountain(sf::Vector2f);
    ~Fountain() = default;
    bool canCollide() const override;
    void update(sf::Time &) override;
private:
    sf::Clock animationClock{};
};

class Door_Mat : public Interior_Object
{
public:
    Door_Mat(sf::Vector2f);
    ~Door_Mat() = default;
    bool canCollide() const override;
};

class Entrance : public Dynamic_Object
{
public:
    Entrance(sf::Vector2f);
    ~Entrance() = default;
    bool canCollide() const override;
};

class Heart : public Dynamic_Object
{
public:
    Heart(sf::Vector2f);
    ~Heart() = default;
    bool canCollide() const override;
    void update(sf::Time &) override;
    void handleCollision(std::unique_ptr<Player> &) override;
private:
    sf::Clock animationClock{};
};
#endif
