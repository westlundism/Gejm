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
    sf::Sprite health_bar{};
    sf::Sprite energy_bar{};
    sf::Sprite bar_background{};
    sf::Sprite bar_endings{};
    sf::Texture texture_pack{};
    int health{};
    float energy{};
};

#endif
