#include "User_Interface.hpp"
#include "ResourcePath.hpp"

User_Interface::User_Interface()
{
    if(!texture_pack.loadFromFile(resourcePath() + "ui.png"))
        throw std::invalid_argument("Player texture not found.");
    
    hud = sf::Sprite(texture_pack, sf::IntRect(448, 180, 84, 64));
    hud.setScale(2.0, 2.0);
    bar_background = sf::Sprite(texture_pack, sf::IntRect(533, 184, 8, 16));
    bar_background.setScale(2.0, 2.0);
    bar_endings = sf::Sprite(texture_pack, sf::IntRect(551, 182, 32, 60));
    bar_endings.setPosition(sf::Vector2f(328, 4));
    bar_endings.setScale(2.0, 2.0);
    health_bar = sf::Sprite(texture_pack, sf::IntRect(601, 186, 8, 12));
    health_bar.setScale(2.0, 2.0);
    energy_bar = sf::Sprite(texture_pack, sf::IntRect(601, 226, 8, 12));
    energy_bar.setScale(2.0, 2.0);
}

void User_Interface::update(sf::Time &, int player_health, float player_energy)
{
    health = player_health;
    energy = player_energy;
}

void User_Interface::draw(sf::RenderWindow & window)
{
    window.draw(hud);
    
    for(int j{}; j < 3; j++)
    {
        for(int i{}; i < 10; i++)
        {
            bar_background.setPosition(168+i*16, 8+j*40);
            window.draw(bar_background);
        }
    }
    
    window.draw(bar_endings);
    
    drawStats(window);
}

void User_Interface::drawStats(sf::RenderWindow & window)
{
    for(int i{}; i < health; i++)
    {
        health_bar.setPosition(168+i*16, 12);
        window.draw(health_bar);
    }
    
    for(int i{}; i < energy; i++)
    {
        energy_bar.setPosition(168+i*16, 92);
        window.draw(energy_bar);
    }
}
