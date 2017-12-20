#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <SFML/Graphics.hpp>

class User_Interface
{
public:
    User_Interface();
    ~User_Interface() = default;
    void update(sf::Time &, int, float);
    void draw(sf::RenderWindow &);
private:
    void drawStats(sf::RenderWindow &);
    
    sf::Sprite hud{};
    sf::Sprite healthBar{};
    sf::Sprite energyBar{};
    sf::Sprite barBackground{};
    sf::Sprite barEndings{};
    sf::Texture texturePack{};
    int health{};
    float energy{};
};

#endif
