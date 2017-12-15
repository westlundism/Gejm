#include "Game_State.hpp"
#include "ResourcePath.hpp"

using namespace std;
using namespace constants;

Game_State::Game_State(Game & game) :
game(game) {}

/*__  __   _   ___ _  _   __  __ ___ _  _ _   _
 |  \/  | /_\ |_ _| \| | |  \/  | __| \| | | | |
 | |\/| |/ _ \ | || .` | | |\/| | _|| .` | |_| |
 |_|  |_/_/ \_\___|_|\_| |_|  |_|___|_|\_|\___/
 */

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

/*___ _  _    ___   _   __  __ ___
 |_ _| \| |  / __| /_\ |  \/  | __|
  | || .` | | (_ |/ _ \| |\/| | _|
 |___|_|\_|  \___/_/ \_\_|  |_|___|
 */

In_Game::In_Game(Game & game) :
Game_State(game), player(make_unique<Player>())
{
    if(!world.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("World texture not loaded!");
    
    if(!other.loadFromFile(resourcePath() + "objects.png"))
        throw invalid_argument("World texture not loaded!");

    background_sprite.setTexture(world);
    background_sprite.setScale(2.0, 2.0);
    
    playerinfo_sprite.setTexture(other);
    playerinfo_sprite.setScale(3.0, 3.0);
    playerinfo_sprite.setTextureRect(sf::IntRect(0, 226, 78, 53));

    constructObjects();
}

void In_Game::handleInput(sf::Event & event)
{
    player->handleInput(event);
}

void In_Game::update(sf::Time & delta)
{
    player->update(delta);
    
    for(auto && object : objects)
    {
        object->update(delta);
        
        sf::FloatRect bounds = object->getSize();
        bounds.height = bounds.height - 40;
        
        if(player->getSize().intersects(bounds))
            player->handleCollision();
    }
}

void In_Game::draw(sf::RenderWindow & window)
{
    drawWorld(window);
    window.draw(playerinfo_sprite);
    player->draw(window);
}

void In_Game::drawWorld(sf::RenderWindow & window)
{
    // Grass background
    background_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    
    for(int columns{}; columns < window_height/32; columns++)
    {
        for(int rows{}; rows < window_width/32; rows++)
        {
            background_sprite.setPosition(32*rows, 32*columns);
            window.draw(background_sprite);
        }
    }

    for(auto && object : objects)
        object->draw(window);
}

void In_Game::constructObjects()
{
    // House
    objects.push_back(make_unique<House>(sf::Vector2f(320, 320)));

    // Grave
    objects.push_back(make_unique<Grave>(sf::Vector2f(500, 320)));
    
    // Living Tree
    objects.push_back(make_unique<Living_Tree>(sf::Vector2f(700, 520)));
}

/*___  _  _   _ ___ ___   __  __ ___ _  _ _   _
 | _ \/_\| | | / __| __| |  \/  | __| \| | | | |
 |  _/ _ \ |_| \__ \ _|  | |\/| | _|| .` | |_| |
 |_|/_/ \_\___/|___/___| |_|  |_|___|_|\_|\___/
 */

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
