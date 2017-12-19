#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Game;

class Button
{
public:
    Button() = default;
    virtual ~Button() = default;
    virtual void handle_input(sf::Event &, Game &) = 0;
    virtual void draw(sf::RenderWindow &) = 0;
    virtual bool click(sf::Event &) = 0;
    virtual void hover(sf::Event &) = 0;
};

class Text_Button : public Button
{
public:
    Text_Button();
    virtual ~Text_Button() = default;
    virtual void handle_input(sf::Event &, Game &) = 0;
    virtual void draw(sf::RenderWindow &);
    bool click(sf::Event &);
    void hover(sf::Event &);
protected:
    sf::Text button_text{};
    sf::Font font{};
};

class Start_Button : public Text_Button
{
public:
    Start_Button();
    ~Start_Button() = default;
    void handle_input(sf::Event &, Game &) override;
};

class Quit_Button : public Text_Button
{
public:
    Quit_Button();
    ~Quit_Button() = default;
    void handle_input(sf::Event &, Game &) override;
};

#endif
