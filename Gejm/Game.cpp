#include "Game.hpp"

using namespace std;

Game::Game()
{
    states.push_back(make_unique<Main_Menu>(*this));
    states.push_back(make_unique<In_Game>(*this));
    states.push_back(make_unique<Pause_Menu>(*this));
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Gejm");
    
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
    states.at(1) = make_unique<In_Game>(*this);
}

void Game::changeState(int new_state)
{
    active_state = new_state;
}
