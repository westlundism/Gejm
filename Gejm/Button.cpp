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
    window.draw(buttonText);
}

bool Text_Button::click(sf::Event & event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        if (buttonText.getGlobalBounds().contains(x, y))
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
        if (buttonText.getGlobalBounds().contains(x, y))
            buttonText.setFillColor(sf::Color::Green);
        else
            buttonText.setFillColor(sf::Color::Black);
    }
}

Start_Button::Start_Button()
{
    buttonText = sf::Text("START", font, 50);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(windowWidth/2 - buttonText.getGlobalBounds().width / 2, windowHeight/2);
}

void Start_Button::handleInput(sf::Event & event, Game & game)
{
    hover(event);
    
    if (click(event))
        game.changeState(1);
}

Quit_Button::Quit_Button()
{
    buttonText = sf::Text("QUIT", font, 50);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(windowWidth/2 - buttonText.getGlobalBounds().width / 2, windowHeight/2 + 100);
}

void Quit_Button::handleInput(sf::Event & event, Game & game)
{
    hover(event);
    
    if (click(event))
        game.quitGame();
}
