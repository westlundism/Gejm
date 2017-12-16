#include "Game.hpp"

using namespace std;
using namespace constants;

Game::Game()
{
    player = make_unique<Player>(*this);
    
    states.push_back(make_unique<Main_Menu>(*this, player));
    states.push_back(make_unique<In_Game>(*this, player));
    states.push_back(make_unique<In_House>(*this, player));
    states.push_back(make_unique<Pause_Menu>(*this, player));
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Gejm");
    
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    
    sf::Clock clock;
    auto delta = clock.restart();
    
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
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
    states.at(1) = make_unique<In_Game>(*this, player);
}

void Game::changeState(int new_state)
{
    active_state = new_state;
}

int Game::getState() const
{
    return active_state;
}
