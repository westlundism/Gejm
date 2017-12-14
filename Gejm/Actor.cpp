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
    
    clock.restart();
}

void Player::handleInput(sf::Event & event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            controllers->handleInput(true, event.key.code);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                slash = true;
            
            temp = sprite.getTextureRect();
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
        sprite.setTextureRect(sf::IntRect(0, 38, 16, 22));
    if(controllers->direction() == sf::Vector2f(-1.0f, 0.0f))
        sprite.setTextureRect(sf::IntRect(0, 102, 16, 22));
    if(controllers->direction() == sf::Vector2f(0.0f, 1.0f))
        sprite.setTextureRect(sf::IntRect(0, 6, 16, 22));
    if(controllers->direction() == sf::Vector2f(0.0f, -1.0f))
        sprite.setTextureRect(sf::IntRect(0, 69, 16, 22));
    
    if(slash)
        handleSlashing();
}

void Player::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

void Player::hitObject(sf::Sprite & object)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        position.y += 5.00f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        position.x += 5.00f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        position.y -= 5.00f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        position.x -= 5.00f;
}

sf::FloatRect Player::getSize()
{
    return sprite.getGlobalBounds();
}

void Player::handleSlashing()
{
    if(temp == sf::IntRect(0, 38, 16, 22))
    {
        if(clock.getElapsedTime() >= sf::seconds(0.6))
            clock.restart();
        if(clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 198, 16, 25));
        if(clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 198, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 198, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 198, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 38, 16, 22));
            slash = false;
        }
    }
    
    if(temp == sf::IntRect(0, 102, 16, 22))
    {
        if(clock.getElapsedTime() >= sf::seconds(0.6))
            clock.restart();
        if(clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 230, 16, 25));
        if(clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 230, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 230, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 230, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 102, 16, 22));
            slash = false;
        }
    }
    
    if(temp == sf::IntRect(0, 6, 16, 22))
    {
        if(clock.getElapsedTime() >= sf::seconds(0.6))
            clock.restart();
        if(clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 134, 16, 25));
        if(clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 134, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 134, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 134, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 6, 16, 22));
            slash = false;
        }
    }
    
    if(temp == sf::IntRect(0, 69, 16, 22))
    {
        if(clock.getElapsedTime() >= sf::seconds(0.6))
            clock.restart();
        if(clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7, 166, 16, 25));
        if(clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40, 166, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72, 166, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.4))
            sprite.setTextureRect(sf::IntRect(104, 166, 16, 26));
        if(clock.getElapsedTime() >= sf::seconds(0.5))
        {
            sprite.setTextureRect(sf::IntRect(0, 69, 16, 22));
            slash = false;
        }
    }
}
