#include "Game_State.hpp"
#include "ResourcePath.hpp"

using namespace std;
using namespace constants;

Game_State::Game_State(Game & game) :
game(game) {}

Main_Menu::Main_Menu(Game & game) :
Game_State(game)
{
    if(!background.loadFromFile(resourcePath() + "background0.png"))
        throw invalid_argument("Background not loaded!");
    background_sprite.setTexture(background);
    
    if(!font.loadFromFile(resourcePath() + "Powerful.ttf"))
        throw invalid_argument("Font not loaded!");
    
    title = sf::Text("GEJM", font, 150);
    title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
    title.setPosition(window_width/2, 200);
    title.setFillColor(sf::Color::Black);
}

void Main_Menu::handleInput(sf::Event &)
{
    
}

void Main_Menu::update(sf::Time &)
{
    
}

void Main_Menu::draw(sf::RenderWindow & window)
{
    window.draw(background_sprite);
    window.draw(title);
}

In_Game::In_Game(Game & game) :
Game_State(game), player(make_unique<Player>())
{
    if(!world.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("World texture not loaded!");

    background_sprite.setTexture(world);
    background_sprite.setScale(2.0, 2.0);
    
    for(int count{}; count < 2; count++)
        sprites.push_back(sf::Sprite(world));
    
    for(unsigned count{}; count < sprites.size(); count++)
        sprites.at(count).setScale(2.0, 2.0);
    
    constructObjects();
}

void In_Game::handleInput(sf::Event & event)
{
    player->handleInput(event);
}

void In_Game::update(sf::Time & delta)
{
    player->update(delta);
    
    for(unsigned count{}; count < sprites.size(); count++)
    {
        sf::FloatRect bounds = sprites.at(count).getGlobalBounds();
        bounds.height = bounds.height - 45;
        
        if(player->getSize().intersects(bounds))
            player->hitObject(sprites.at(count));
    }
}

void In_Game::draw(sf::RenderWindow & window)
{
    drawWorld(window);
    player->draw(window);
}

void In_Game::drawWorld(sf::RenderWindow & window)
{
    // Grass background
    background_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    
    for(int j{}; j < window_height/32; j++)
    {
        for(int i{}; i < window_width/32; i++)
        {
            background_sprite.setPosition(32*i, 32*j);
            window.draw(background_sprite);
        }
    }
    
    // Objects
    for(unsigned count{}; count < sprites.size(); count++)
        window.draw(sprites.at(count));
}

void In_Game::constructObjects()
{
    // House
    sprites.at(0).setTextureRect(sf::IntRect(96, 0, 74, 80));
    sprites.at(0).setPosition(320, 320);
    
    // Grave
    sprites.at(1).setTextureRect(sf::IntRect(567, 83, 20, 24));
    sprites.at(1).setPosition(500, 320);
}

Pause_Menu::Pause_Menu(Game & game) :
Game_State(game)
{
    
}

void Pause_Menu::handleInput(sf::Event &)
{
    
}

void Pause_Menu::update(sf::Time &)
{
    
}

void Pause_Menu::draw(sf::RenderWindow &)
{
    
}
