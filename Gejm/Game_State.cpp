#include "Game_State.hpp"
#include "ResourcePath.hpp"

using namespace std;

Game_State::Game_State(Game & game) :
game(game) {}

Main_Menu::Main_Menu(Game & game) :
Game_State(game)
{
    if(!background.loadFromFile(resourcePath() + "background0.png"))
        throw invalid_argument("Background not loaded!");
    sprite.setTexture(background);
    if(!font.loadFromFile(resourcePath() + "Powerful.ttf"))
        throw invalid_argument("Font not loaded!");
    title = sf::Text("GEJM", font, 150);
    title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
    title.setPosition(1600/2, 300);
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
    window.draw(sprite);
    window.draw(title);
}

In_Game::In_Game(Game & game) :
Game_State(game), player(make_unique<Player>())
{
    
}

void In_Game::handleInput(sf::Event &)
{
    
}

void In_Game::update(sf::Time &)
{
    
}

void In_Game::draw(sf::RenderWindow &)
{
    
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
