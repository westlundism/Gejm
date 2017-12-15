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
    sprite.setTextureRect(sf::IntRect(0, 6, 16, 22));
    sprite.setScale(2.0, 2.0);
    sprite.setPosition(window_width/2, window_height/2);
    
    slash_clock.restart();
    moving_clock.restart();
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
    
    if(controllers->slash())
        slash = true;
}

void Player::update(sf::Time & delta)
{
    float distance = 250.0f * (delta.asMicroseconds() / 2000000.0f);
    position += controllers->direction() * distance;
    sprite.setPosition(position);

    animate();
    
    if(slash)
        handleSlashing();
}

void Player::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

void Player::handleCollision()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        position.y += 3.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        position.x += 3.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        position.y -= 3.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        position.x -= 3.0f;
}

sf::FloatRect Player::getSize()
{
    return sprite.getGlobalBounds();
}

void Player::handleSlashing()
{
    if(movement_direction == 'l')
    {
        if(slash_clock.getElapsedTime() >= sf::seconds(0.6))
            slash_clock.restart();
        if(slash_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 230, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 230, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 230, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 230, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 102, 16, 22));
            slash = false;
        }
    }
    
    if(movement_direction == 'r')
    {
        if(slash_clock.getElapsedTime() >= sf::seconds(0.6))
            slash_clock.restart();
        if(slash_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 198, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 198, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 198, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 198, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 38, 16, 22));
            slash = false;
        }
    }

    if(movement_direction == 'u')
    {
        if(slash_clock.getElapsedTime() >= sf::seconds(0.6))
            slash_clock.restart();
        if(slash_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 166, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 166, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 166, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 166, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 69, 16, 22));
            slash = false;
        }
    }
    
    if(movement_direction == 'd')
    {
        if(slash_clock.getElapsedTime() >= sf::seconds(0.6))
            slash_clock.restart();
        if(slash_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 134, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 134, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 134, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 134, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 6, 16, 22));
            slash = false;
        }
    }
}

void Player::animate()
{
    if(controllers->direction() == sf::Vector2f(-1.0, 0))
    {
        movement_direction = 'l';
        if(moving_clock.getElapsedTime() >= sf::seconds(0.4))
            moving_clock.restart();
        if(moving_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(17, 102, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(33, 102, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(49, 102, 16, 22));
    }
    
    if(controllers->direction() == sf::Vector2f(1.0, 0))
    {
        movement_direction = 'r';
        if(moving_clock.getElapsedTime() >= sf::seconds(0.4))
            moving_clock.restart();
        if(moving_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(18, 38, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(34, 38, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(50, 38, 16, 22));
    }
    
    if(controllers->direction() == sf::Vector2f(0, -1.0))
    {
        movement_direction = 'u';
        if(moving_clock.getElapsedTime() >= sf::seconds(0.4))
            moving_clock.restart();
        if(moving_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(16, 69, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(32, 69, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(49, 69, 16, 22));
    }
    
    if(controllers->direction() == sf::Vector2f(0, 1.0))
    {
        movement_direction = 'd';
        if(moving_clock.getElapsedTime() >= sf::seconds(0.4))
            moving_clock.restart();
        if(moving_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(17, 6, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(33, 6, 16, 22));
        if(moving_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(49, 6, 16, 22));
    }
    
}
