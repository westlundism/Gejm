#include "Actor.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"
#include "Game_State.hpp"

using namespace constants;
using namespace std;

void Actor::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

void Actor::setPosition(sf::Vector2f pos)
{
    position = pos;
}

sf::Vector2f Actor::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Actor::getSize() const
{
    return sprite.getGlobalBounds();
}

/*___  _       _ __   __ ___  ___
 | _ \| |     /_\\ \ / /| __|| _ \
 |  _/| |__  / _ \\ V / | _| |   /
 |_|  |____|/_/ \_\|_|  |___||_|_\
 */

Player::Player(Game & game) :
controllers(make_unique<Controllers>())
{
    if(!player.loadFromFile(resourcePath() + "character.png"))
        throw std::invalid_argument("Player texture not found.");
    
    sprite.setTexture(player);
    sprite.setTextureRect(sf::IntRect(0, 69, 16, 22));
    sprite.setScale(2.0, 2.0);
    sprite.setPosition(window_width/2 - 16, window_height/2);
    
    if(game.getState() == 1)
        sprite.setPosition(window_width/2 - 16, window_height/2);
    else if(game.getState() == 2)
        sprite.setPosition(window_width/2 - 16, window_height/2 + 100);
    
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

void Player::handleCollision(Game & game)
{
    if(game.getState() == 2)
    {
        if(position.x < window_width/3)
            position.x = window_width/3;
        if(position.x > window_width*2/3 - 32)
            position.x = window_width*2/3 - 32;
        if(position.y < window_height/3)
            position.y = window_height/3;
        if(position.y > window_height*2/3 - 32)
            position.y = window_height*2/3 - 32;
    }
    else
    {
        if(position.x < 0)
            position.x = 0;
        if(position.x > window_width - 32)
            position.x = window_width - 32;
        if(position.y < 0)
            position.y = 0;
        if(position.y > window_height - 32)
            position.y = window_height - 32;
    }
}

void Player::update(sf::Time & delta)
{
    if(energy_clock.getElapsedTime() >= sf::seconds(5.0) && energy < 10.0)
    {
        energy += 1.0;
        energy_clock.restart();
    }
    
    if(controllers->shift && energy > 0)
    {
        moving_speed = 250.0f * (delta.asMicroseconds() / 1000000.0f);
        energy -= 0.1;
    }
    else
        moving_speed = 250.0f * (delta.asMicroseconds() / 2000000.0f);
    position += controllers->direction() * moving_speed;
    sprite.setPosition(position);
    
    animate();
    
    if(slash)
        handleSlashing();
}

int Player::updateHealth(int health_update)
{
    if(health_update < 0 && health > 0)
        health += health_update;
    else if(health_update > 0 && health < 10)
        health += health_update;
    return health;
}

float Player::updateEnergy(float energy_update)
{
    if(energy_update < 0 && energy > 0)
        energy += energy_update;
    else if(energy_update > 0 && energy < 10.0)
        energy += energy_update;
    return energy;
}

void Player::handleSlashing()
{
    if(movement_direction == 'l')
    {
        if(slash_clock.getElapsedTime() >= sf::seconds(0.6))
            slash_clock.restart();
        if(slash_clock.getElapsedTime() >= sf::seconds(0.1))
            sprite.setTextureRect(sf::IntRect(7,   230, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40,  230, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72,  230, 16, 26));
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
            sprite.setTextureRect(sf::IntRect(7,   198, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40,  198, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72,  198, 16, 26));
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
            sprite.setTextureRect(sf::IntRect(7,   166, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40,  166, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72,  166, 16, 26));
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
            sprite.setTextureRect(sf::IntRect(7,   134, 16, 25));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.2))
            sprite.setTextureRect(sf::IntRect(40,  134, 16, 26));
        if(slash_clock.getElapsedTime() >= sf::seconds(0.3))
            sprite.setTextureRect(sf::IntRect(72,  134, 16, 26));
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
