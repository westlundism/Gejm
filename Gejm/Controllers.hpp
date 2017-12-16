#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Controllers
{
    friend class Player;
public:
    Controllers();
    ~Controllers() = default;
    void handleInput(bool, sf::Keyboard::Key);
    sf::Vector2f direction();
    bool slash() const;
private:
    bool left;
    bool left_allowed;
    bool right;
    bool right_allowed;
    bool up;
    bool up_allowed;
    bool down;
    bool down_allowed;
    bool space;
};

#endif /* Controllers_hpp */

