#include "Button.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"

using namespace std;
using namespace constants;

Text_Button::Text_Button()
{
    if(!font.loadFromFile(resourcePath() + "PDOS.ttf"))
        throw invalid_argument("Font not found!");
}

void Text_Button::draw(sf::RenderWindow & window)
{
    window.draw(button_text);
}

bool Text_Button::click(sf::Event & event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        if (button_text.getGlobalBounds().contains(x, y))
            return true;
    }
    return false;
}

void Text_Button::hover(sf::Event & event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        float x = event.mouseMove.x;
        float y = event.mouseMove.y;
        if (button_text.getGlobalBounds().contains(x, y))
            button_text.setFillColor(sf::Color::Green);
        else
            button_text.setFillColor(sf::Color::Black);
    }
}

Start_Button::Start_Button()
{
    button_text = sf::Text("START", font, 50);
    button_text.setFillColor(sf::Color::Black);
    button_text.setPosition(window_width/2 - button_text.getGlobalBounds().width / 2, window_height/2);
}

void Start_Button::handle_input(sf::Event & event, Game & game)
{
    hover(event);
    
    if (click(event))
        game.changeState(1);
}

Quit_Button::Quit_Button()
{
    button_text = sf::Text("QUIT", font, 50);
    button_text.setFillColor(sf::Color::Black);
    button_text.setPosition(window_width/2 - button_text.getGlobalBounds().width / 2, window_height/2 + 100);
}

void Quit_Button::handle_input(sf::Event & event, Game & game)
{
    hover(event);
    
    if (click(event))
        game.quitGame();
}
