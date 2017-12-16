#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Controllers
{
    friend class Player;
    friend class Object;
public:
    Controllers();
    ~Controllers() = default;
    void handleInput(bool, sf::Keyboard::Key);
    sf::Vector2f direction();
    bool slash() const;
private:
    bool left;
    bool right;
    bool up;
    bool down;
    bool space;
};

#endif /* Controllers_hpp */

