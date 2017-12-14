#include "Actor.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"

using namespace constants;
using namespace std;

Player::Player() :
position(window_width/2, window_height/2), controllers(make_unique<Controllers>())
{
    if(!player.loadFromFile(resourcePath() + "character.png"))
        throw std::invalid_argument("Player texture not found.");
    
    sprite.setTexture(player);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 32));
    sprite.setScale(2.0, 2.0);
    sprite.setPosition(window_width/2, window_height/2);
}

void Player::handleInput(sf::Event & event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            controllers->handleInput(true, event.key.code);
            break;
        case sf::Event::KeyReleased:
            controllers->handleInput(false, event.key.code);
            break;
        default:
            break;
    }
}

void Player::update(sf::Time & delta)
{
    float distance = 250.0f * (delta.asMicroseconds() / 1000000.0f);
    position += controllers->direction() * distance;
    sprite.setPosition(position);
    
    if(controllers->direction() == sf::Vector2f(1.0f, 0.0f))
        sprite.setTextureRect(sf::IntRect(0, 32, 16, 32));
    if(controllers->direction() == sf::Vector2f(-1.0f, 0.0f))
        sprite.setTextureRect(sf::IntRect(0, 96, 16, 32));
    if(controllers->direction() == sf::Vector2f(0.0f, 1.0f))
        sprite.setTextureRect(sf::IntRect(0, 0, 16, 32));
    if(controllers->direction() == sf::Vector2f(0.0f, -1.0f))
        sprite.setTextureRect(sf::IntRect(0, 64, 16, 32));
}

void Player::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}
