#include "Controllers.hpp"

#include "Controllers.hpp"

Controllers::Controllers() :
left(false), right(false), up(false), down(false), space(false),
left_allowed(true), right_allowed(true), down_allowed(true),
up_allowed(true) {}

void Controllers::handleInput(bool pressed, sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            left = pressed;
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            right = pressed;
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            up = pressed;
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            down = pressed;
            break;
        case sf::Keyboard::Space:
            space = pressed;
            break;
        default:
            break;
    }
}

sf::Vector2f Controllers::direction()
{
    sf::Vector2f direction;
    
    if (left && left_allowed)
        direction.x -= 1.0f;
    else if (right && right_allowed)
        direction.x += 1.0f;
    else if (up && up_allowed)
        direction.y -= 1.0f;
    else if (down && down_allowed)
        direction.y += 1.0f;
    
    float length = sqrt(direction.x*direction.x + direction.y*direction.y);
    
    if (length <= 0.0f)
        direction = sf::Vector2f(0, 0);
    else
        direction = direction * (1.0f/length);
    
    return direction;
}

bool Controllers::slash() const
{
    return space;
}
