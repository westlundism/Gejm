#include "Object.hpp"
#include "ResourcePath.hpp"

using namespace std;

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

Outdoor_Object::Outdoor_Object(sf::Vector2f position) :
Object(position)
{
    if(!texture.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("Cannot load world sprites!");
    
    sprite.setTexture(texture);
    sprite.setScale(2.0, 2.0);
}

House::House(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTextureRect(sf::IntRect(99, 0, 74, 80));
}

Grave::Grave(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTextureRect(sf::IntRect(567, 83, 20, 24));
}
