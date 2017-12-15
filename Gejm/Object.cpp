#include "Object.hpp"
#include "ResourcePath.hpp"

using namespace std;

/*___   ___     _  ___  ___  _____
 / _ \ | _ ) _ | || __|/ __||_   _|
| (_) || _ \| || || _|| (__   | |
 \___/ |___/ \__/ |___|\___|  |_|
 */

Object::Object(sf::Vector2f position) :
position(position)
{
    sprite.setPosition(position);
}

void Object::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

sf::FloatRect Object::getSize() const
{
    return sprite.getGlobalBounds();
}

/*___  _   _ _____ ___   ___   ___  ___    ___  ___    _ ___ ___ _____
 / _ \| | | |_   _|   \ / _ \ / _ \| _ \  / _ \| _ )_ | | __/ __|_   _|
| (_) | |_| | | | | |) | (_) | (_) |   / | (_) | _ \ || | _| (__  | |
 \___/ \___/  |_| |___/ \___/ \___/|_|_\  \___/|___/\__/|___\___| |_|
 */

Outdoor_Object::Outdoor_Object(sf::Vector2f position) :
Object(position)
{
    if(!texture_pack_1.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("Cannot load world sprites!");
    if(!texture_pack_2.loadFromFile(resourcePath() + "objects.png"))
        throw invalid_argument("Cannot load world sprites!");

    sprite.setScale(2.0, 2.0);
}

/*_  _  ___  _   _ ___ ___
 | || |/ _ \| | | / __| __|
 | __ | (_) | |_| \__ \ _|
 |_||_|\___/ \___/|___/___|
 */

House::House(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTexture(texture_pack_1);
    sprite.setTextureRect(sf::IntRect(99, 0, 74, 80));
}

/*___  ___    _ __   __ ___
 / __|| _ \  /_\\ \ / /| __|
| (_ ||   / / _ \\ V / | _|
 \___||_|_\/_/ \_\\_/  |___|
 */

Grave::Grave(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTexture(texture_pack_1);
    sprite.setTextureRect(sf::IntRect(567, 83, 20, 24));
}

/*_    _____   _____ _  _  ___   _____ ___ ___ ___
 | |  |_ _\ \ / /_ _| \| |/ __| |_   _| _ \ __| __|
 | |__ | | \ V / | || .` | (_ |   | | |   / _|| _|
 |____|___| \_/ |___|_|\_|\___|   |_| |_|_\___|___|
 */

Living_Tree::Living_Tree(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTexture(texture_pack_2);
    sprite.setTextureRect(sf::IntRect(1, 165, 31, 26));
    
    animation.restart();
}

void Living_Tree::update(sf::Time & delta)
{
    if(animation.getElapsedTime() >= sf::seconds(5))
    {
        animation.restart();
    }
    
    for(float i{}; i < 17.0; i++)
    {
        if(animation.getElapsedTime() >= sf::seconds(i/10) &&
           animation.getElapsedTime() <= sf::seconds(0.8) )
            sprite.setTextureRect(sf::IntRect((i*32), 160, 32, 31));
        
        if(animation.getElapsedTime() >= sf::seconds(i/10) &&
           animation.getElapsedTime() >= sf::seconds(0.8) )
            sprite.setTextureRect(sf::IntRect((i*32 - 224), 192, 32, 31));
        
        if(animation.getElapsedTime() >= sf::seconds(1.6))
            sprite.setTextureRect(sf::IntRect(256, 192, 32, 31));
    }
    
    for(float i{}; i < 17; i++)
    {
        if(animation.getElapsedTime() >= sf::seconds(2.0 + i/10) &&
           animation.getElapsedTime() <= sf::seconds(2.8) )
            sprite.setTextureRect(sf::IntRect((256-i*32), 192, 32, 31));
        
        if(animation.getElapsedTime() >= sf::seconds(2.0 + i/10) &&
           animation.getElapsedTime() >= sf::seconds(2.8) )
            sprite.setTextureRect(sf::IntRect((480-i*32), 160, 32, 31));
        
        if(animation.getElapsedTime() >= sf::seconds(3.6))
            sprite.setTextureRect(sf::IntRect(0, 160, 32, 31));
    }
}
