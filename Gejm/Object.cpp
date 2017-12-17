#include "Object.hpp"
#include "ResourcePath.hpp"
#include "Game.hpp"

using namespace std;
using namespace constants;

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

void Object::handleCollision(unique_ptr<Player> & player)
{
    sf::FloatRect player_bounds = player->getSize();
    sf::FloatRect object_bounds = sprite.getGlobalBounds();
    object_bounds.height -= 30;
    
    if(player->controllers->left)
    {
        --player_bounds.left;
        --player_bounds.height;
        if(player_bounds.intersects(object_bounds))
            player->position.x += player->moving_speed;
        ++player_bounds.left;
        ++player_bounds.height;
    }
    
    if(player->controllers->right)
    {
        ++player_bounds.width;
        if(player_bounds.intersects(object_bounds))
            player->position.x -= player->moving_speed;
        --player_bounds.width;
    }
    
    if(player->controllers->up)
    {
        ++player_bounds.height;
        if(player_bounds.intersects(object_bounds))
            player->position.y += player->moving_speed;
        --player_bounds.height;
    }
    
    if(player->controllers->down)
    {
        --player_bounds.top;
        if(player_bounds.intersects(object_bounds))
            player->position.y -= player->moving_speed;
        ++player_bounds.top;
    }
}

sf::FloatRect Object::getSize() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Object::getPosition() const
{
    return sprite.getPosition();
}

bool Object::isDestroyed() const
{
    return destroyed;
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

/*___ _  _ _____ ___ ___ ___ ___  ___    ___  ___    _ ___ ___ _____
 |_ _| \| |_   _| __| _ \_ _/ _ \| _ \  / _ \| _ )_ | | __/ __|_   _|
  | || .` | | | | _||   /| | (_) |   / | (_) | _ \ || | _| (__  | |
 |___|_|\_| |_| |___|_|_\___\___/|_|_\  \___/|___/\__/|___\___| |_|
 */

Interior_Object::Interior_Object(sf::Vector2f position) :
Object(position)
{
    if(!interior_pack.loadFromFile(resourcePath() + "Inner.png"))
        throw invalid_argument("Cannot load world sprites!");
    
    sprite.setScale(2.0, 2.0);
}

/*_____   ___  _   _   __  __ ___ ___    ___  ___    _ ___ ___ _____
 |   \ \ / / \| | /_\ |  \/  |_ _/ __|  / _ \| _ )_ | | __/ __|_   _|
 | |) \ V /| .` |/ _ \| |\/| || | (__  | (_) | _ \ || | _| (__  | |
 |___/ |_| |_|\_/_/ \_\_|  |_|___\___|  \___/|___/\__/|___\___| |_|
 */

Dynamic_Object::Dynamic_Object(sf::Vector2f position) :
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

bool House::canCollide() const
{
    return true;
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

bool Grave::canCollide() const
{
    return true;
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
        animation.restart();
    
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

bool Living_Tree::canCollide() const
{
    return true;
}

/*___ ___  _   _ _  _ _____ _   ___ _  _
 | __/ _ \| | | | \| |_   _/_\ |_ _| \| |
 | _| (_) | |_| | .` | | |/ _ \ | || .` |
 |_| \___/ \___/|_|\_| |_/_/ \_\___|_|\_|
 */

Fountain::Fountain(sf::Vector2f position) :
Outdoor_Object(position)
{
    sprite.setTexture(texture_pack_1);
    sprite.setTextureRect(sf::IntRect(352, 144, 48, 47));
}

bool Fountain::canCollide() const
{
    return true;
}

void Fountain::update(sf::Time & delta)
{
    if(animation.getElapsedTime() >= sf::seconds(0.3))
        animation.restart();
    
    for(float i{}; i < 3; i++)
    {
        if(animation.getElapsedTime() >= sf::seconds(i/10))
            sprite.setTextureRect(sf::IntRect(352+i*48, 144, 48, 47));
    }
}

/*___   ___   ___  ___   __  __   _ _____
 |   \ / _ \ / _ \| _ \ |  \/  | /_\_   _|
 | |) | (_) | (_) |   / | |\/| |/ _ \| |
 |___/ \___/ \___/|_|_\ |_|  |_/_/ \_\_|
 */

Door_Mat::Door_Mat(sf::Vector2f position) :
Interior_Object(position)
{
    sprite.setTexture(interior_pack);
    sprite.setTextureRect(sf::IntRect(96, 0, 16, 16));
}

bool Door_Mat::canCollide() const
{
    return false;
}


/*___ _  _ _____ ___    _   _  _  ___ ___
 | __| \| |_   _| _ \  /_\ | \| |/ __| __|
 | _|| .` | | | |   / / _ \| .` | (__| _|
 |___|_|\_| |_| |_|_\/_/ \_\_|\_|\___|___|
 */

Entrance::Entrance(sf::Vector2f position) :
Dynamic_Object(position)
{
    sprite.setTexture(texture_pack_1);
    sprite.setTextureRect(sf::IntRect(300, 300, 16, 5));
}

bool Entrance::canCollide() const
{
    return true;
}

/*_  _ ___   _   ___ _____
 | || | __| /_\ | _ \_   _|
 | __ | _| / _ \|   / | |
 |_||_|___/_/ \_\_|_\ |_|
 */

Heart::Heart(sf::Vector2f position) :
Dynamic_Object(position)
{
    sprite.setTexture(texture_pack_2);
    sprite.setTextureRect(sf::IntRect(2, 51, 11, 11));
}

bool Heart::canCollide() const
{
    return true;
}

void Heart::update(sf::Time & delta)
{
    if(animation.getElapsedTime() >= sf::seconds(0.8))
        animation.restart();
    
    for(float i{}; i < 4; i++)
    {
        if(animation.getElapsedTime() >= sf::seconds(i/5))
            sprite.setTextureRect(sf::IntRect(2+i*16, 51, 11, 11));
    }
}

void Heart::handleCollision(std::unique_ptr<Player> & player)
{
    sf::FloatRect player_bounds = player->getSize();
    sf::FloatRect object_bounds = sprite.getGlobalBounds();
    player_bounds.top += 25;
    player_bounds.height -= 35;
    player_bounds.left += 10;
    player_bounds.width -= 10;
    
    if(player_bounds.intersects(object_bounds) && player->updateHealth(0) < 10)
    {
        if(player->updateHealth(0) < 10)
            player->updateHealth(1);
        destroyed = true;
    }
}
