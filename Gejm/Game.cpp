#include "Game.hpp"

using namespace std;
using namespace constants;

Game::Game()
{
    player = make_unique<Player>(*this);
    ui = make_unique<User_Interface>();
    
    states.push_back(make_unique<Main_Menu>(*this, player, ui));
    states.push_back(make_unique<In_Game>(*this, player, ui));
    states.push_back(make_unique<In_House>(*this, player, ui));
    states.push_back(make_unique<Pause_Menu>(*this, player, ui));
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Gejm");
    
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    
    sf::Clock clock;
    auto delta = clock.restart();
    
    while (!quit)
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    quit = true;
                    break;
                default:
                    states.at(active_state)->handleInput(event);
                    break;
            }
        }
        
        window.clear();
        states.at(active_state)->update(delta);
        delta = clock.restart();
        states.at(active_state)->draw(window);
        window.display();
    }
}

void Game::restart()
{
    changeState(0);
    player = make_unique<Player>(*this);
    ui = make_unique<User_Interface>();
    states.at(1) = make_unique<In_Game>(*this, player, ui);
}

void Game::changeState(int new_state)
{
    active_state = new_state;
}

int Game::getState() const
{
    return active_state;
}

void Game::quitGame()
{
    quit = true;
}
