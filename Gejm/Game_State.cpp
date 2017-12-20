#include "Game_State.hpp"
#include "ResourcePath.hpp"

using namespace std;
using namespace constants;

Game_State::Game_State(Game & game, std::unique_ptr<Player> & player,
                       std::unique_ptr<User_Interface> & ui) :
game(game), player(player), ui(ui) {}

/*__  __   _   ___ _  _   __  __ ___ _  _ _   _
 |  \/  | /_\ |_ _| \| | |  \/  | __| \| | | | |
 | |\/| |/ _ \ | || .` | | |\/| | _|| .` | |_| |
 |_|  |_/_/ \_\___|_|\_| |_|  |_|___|_|\_|\___/
 */

Main_Menu::Main_Menu(Game & game, std::unique_ptr<Player> & player,
                     std::unique_ptr<User_Interface> & ui) :
Game_State(game, player, ui)
{
    if(!background.loadFromFile(resourcePath() + "background0.png"))
        throw invalid_argument("Background not loaded!");
    backgroundSprite.setTexture(background);
    
    if(!font.loadFromFile(resourcePath() + "Powerful.ttf"))
        throw invalid_argument("Font not loaded!");
    
    title = sf::Text("GEJM", font, 150);
    title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
    title.setPosition(windowWidth/2, 200);
    title.setFillColor(sf::Color::Black);
    
    buttons.push_back(make_unique<Start_Button>());
    buttons.push_back(make_unique<Quit_Button>());
}

void Main_Menu::handleInput(sf::Event & event)
{
    for(auto && button : buttons)
        button->handleInput(event, game);
}

void Main_Menu::update(sf::Time &)
{

}

void Main_Menu::draw(sf::RenderWindow & window)
{
    window.draw(backgroundSprite);
    window.draw(title);
    
    for(auto && button : buttons)
        button->draw(window);
}

/*___ _  _    ___   _   __  __ ___
 |_ _| \| |  / __| /_\ |  \/  | __|
  | || .` | | (_ |/ _ \| |\/| | _|
 |___|_|\_|  \___/_/ \_\_|  |_|___|
 */

In_Game::In_Game(Game & game, std::unique_ptr<Player> & player,
                 std::unique_ptr<User_Interface> & ui) :
Game_State(game, player, ui)
{
    if(!world.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("World texture not loaded!");
    
    if(!other.loadFromFile(resourcePath() + "objects.png"))
        throw invalid_argument("World texture not loaded!");

    backgroundSprite.setTexture(world);
    backgroundSprite.setScale(2.0, 2.0);
    
    player->setPosition(sf::Vector2f(windowWidth/2 - 16,
                                     windowHeight/2));
    
    constructObjects();
}

void In_Game::handleInput(sf::Event & event)
{
    player->handleInput(event);
}

void In_Game::update(sf::Time & delta)
{
    player->update(delta);
    ui->update(delta, player->updateHealth(0), player->updateEnergy(0));
    
    for(auto && object : objects)
        object->update(delta);
    
    for(int i{}; i < objects.size(); i++)
        if(objects.at(i)->isDestroyed())
            objects.erase(objects.begin() + i);
    
    handleCollision();
}

void In_Game::draw(sf::RenderWindow & window)
{
    drawWorld(window);
    player->draw(window);
    ui->draw(window);
}

void In_Game::handleCollision()
{
    player->handleCollision(game);
    
    for(auto && object : objects)
    {
        Entrance * temp = dynamic_cast<Entrance*>(object.get());
        
        if(object->canCollide() && temp == nullptr)
            object->handleCollision(player);
        
        if(temp != nullptr && player->getSize().intersects(object->getSize()))
        {
            game.changeState(2);
            player->setPosition(sf::Vector2f(windowWidth/2  - 16,
                                             windowHeight/2 + 100));
        }
    }
}

void In_Game::drawWorld(sf::RenderWindow & window)
{
    // Grass background
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    
    for(int columns{}; columns < windowHeight/32; columns++)
        for(int rows{}; rows < windowWidth/32; rows++)
        {
            backgroundSprite.setPosition(32*rows, 32*columns);
            window.draw(backgroundSprite);
        }

    for(auto && object : objects)
        object->draw(window);
}

void In_Game::constructObjects()
{
    // House
    objects.push_back(make_unique<House>(sf::Vector2f(320, 320)));
    
    // Entrance
    objects.push_back(make_unique<Entrance>(sf::Vector2f(378, 440)));
    
    // Grave
    objects.push_back(make_unique<Grave>(sf::Vector2f(500, 320)));
    
    // Living Tree
    objects.push_back(make_unique<Living_Tree>(sf::Vector2f(700, 520)));
    
    // Fountain
    objects.push_back(make_unique<Fountain>(sf::Vector2f(700, 320)));
    
    // Heart
    objects.push_back(make_unique<Heart>(sf::Vector2f(600, 450)));
}

/*___ _  _   _  _  ___  _   _ ___ ___
 |_ _| \| | | || |/ _ \| | | / __| __|
  | || .` | | __ | (_) | |_| \__ \ _|
 |___|_|\_| |_||_|\___/ \___/|___/___|
 */

In_House::In_House(Game & game, std::unique_ptr<Player> & player,
                   std::unique_ptr<User_Interface> & ui) :
Game_State(game, player, ui)
{
    if(!interior.loadFromFile(resourcePath() + "Inner.png"))
        throw invalid_argument("World texture not loaded!");
    
    if(!other.loadFromFile(resourcePath() + "objects.png"))
        throw invalid_argument("World texture not loaded!");
    
    backgroundSprite.setTexture(interior);
    backgroundSprite.setScale(2.0, 2.0);
    
    player->setPosition(sf::Vector2f(windowWidth/2 - 16,
                                     windowHeight/2 + 100));
    
    constructObjects();
}

void In_House::handleInput(sf::Event & event)
{
    player->handleInput(event);
}

void In_House::update(sf::Time & delta)
{
    player->update(delta);
    ui->update(delta, player->updateHealth(0), player->updateEnergy(0));
    for(auto && object : objects)
        object->update(delta);
    handleCollision();
}

void In_House::draw(sf::RenderWindow & window)
{
    drawHouse(window);
    player->draw(window);
    ui->draw(window);
}

void In_House::handleCollision()
{
    player->handleCollision(game);
    
    for(auto && object : objects)
    {
        Entrance * temp = dynamic_cast<Entrance*>(object.get());
        
        if(object->canCollide() && temp == nullptr)
            object->handleCollision(player);
        
        if(temp != nullptr && player->getSize().intersects(object->getSize()))
        {
            game.changeState(1);
            player->setPosition(sf::Vector2f(320+74-16, 320+160-16));
        }
    }
}

void In_House::drawHouse(sf::RenderWindow & window)
{
    // Floor
    backgroundSprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
    
    for(int columns{}; columns < windowHeight/32/3; columns++)
        for(int rows{}; rows < windowWidth/32/3; rows++)
        {
            backgroundSprite.setPosition(windowWidth/3  + 32*rows,
                                          windowHeight/3 + 32*columns);
            window.draw(backgroundSprite);
        }
    
    for(auto && object : objects)
        object->draw(window);
}

void In_House::constructObjects()
{
    // Entrance
    objects.push_back(make_unique<Entrance>(sf::Vector2f(windowWidth/2 - 16,
                                                         windowHeight/2 + 160)));
    
    // Door Mat
    objects.push_back(make_unique<Door_Mat>(sf::Vector2f(windowWidth/2 - 16,
                                                         windowHeight/2 + 128)));
}

/*___  _  _   _ ___ ___   __  __ ___ _  _ _   _
 | _ \/_\| | | / __| __| |  \/  | __| \| | | | |
 |  _/ _ \ |_| \__ \ _|  | |\/| | _|| .` | |_| |
 |_|/_/ \_\___/|___/___| |_|  |_|___|_|\_|\___/
 */

Pause_Menu::Pause_Menu(Game & game, std::unique_ptr<Player> & player,
                       std::unique_ptr<User_Interface> & ui) :
Game_State(game, player, ui)
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
