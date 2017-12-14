#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Controllers
{
public:
    Controllers();
    ~Controllers() = default;
    void handleInput(bool, sf::Keyboard::Key);
    sf::Vector2f direction();
private:
    bool left{};
    bool right{};
    bool up{};
    bool down{};
};

#endif /* Controllers_hpp */

