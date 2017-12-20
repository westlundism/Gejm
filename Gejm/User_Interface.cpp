#include "User_Interface.hpp"
#include "ResourcePath.hpp"

User_Interface::User_Interface()
{
    if(!texturePack.loadFromFile(resourcePath() + "ui.png"))
        throw std::invalid_argument("Player texture not found.");
    
    hud = sf::Sprite(texturePack, sf::IntRect(448, 180, 84, 64));
    hud.setScale(2.0, 2.0);
    barBackground = sf::Sprite(texturePack, sf::IntRect(533, 184, 8, 16));
    barBackground.setScale(2.0, 2.0);
    barEndings = sf::Sprite(texturePack, sf::IntRect(551, 182, 32, 60));
    barEndings.setPosition(sf::Vector2f(328, 4));
    barEndings.setScale(2.0, 2.0);
    healthBar = sf::Sprite(texturePack, sf::IntRect(601, 186, 8, 12));
    healthBar.setScale(2.0, 2.0);
    energyBar = sf::Sprite(texturePack, sf::IntRect(601, 226, 8, 12));
    energyBar.setScale(2.0, 2.0);
}

void User_Interface::update(sf::Time &, int playerHealth, float playerEnergy)
{
    health = playerHealth;
    energy = playerEnergy;
}

void User_Interface::draw(sf::RenderWindow & window)
{
    window.draw(hud);
    
    for(int j{}; j < 3; j++)
        for(int i{}; i < 10; i++)
        {
            barBackground.setPosition(168+i*16, 8+j*40);
            window.draw(barBackground);
        }
    
    window.draw(barEndings);
    
    drawStats(window);
}

void User_Interface::drawStats(sf::RenderWindow & window)
{
    for(int i{}; i < health; i++)
    {
        healthBar.setPosition(168+i*16, 12);
        window.draw(healthBar);
    }
    
    for(int i{}; i < energy; i++)
    {
        energyBar.setPosition(168+i*16, 92);
        window.draw(energyBar);
    }
}
