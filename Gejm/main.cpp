#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //update
        //draw
        window.display();
    }

    return 0;
}
