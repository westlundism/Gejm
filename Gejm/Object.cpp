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
    if(!texture.loadFromFile(resourcePath() + "Overworld.png"))
        throw invalid_argument("Cannot load world sprites!");
    
    sprite.setTexture(texture);
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
    sprite.setTextureRect(sf::IntRect(567, 83, 20, 24));
}
