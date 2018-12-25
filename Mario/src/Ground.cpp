#include<iostream>
#include<math.h>
#include "SFML/Graphics.hpp"
#include "Ground.h"

Ground::Ground(sf::RenderWindow& windowPtr) : wing(windowPtr)
{
    groundtexture.loadFromFile("grounds.png", sf::IntRect(0,0,30,30));
    groundtexture.setRepeated(true);
    superGround.setTexture(groundtexture);
    //superGround.setTextureRect(sf::IntRect(groundPos.x,groundPos.y,1000,600));
    superGround.setTextureRect(sf::IntRect(0,0,1000,600));
    groundClock.restart();
    superGround.setPosition(0.0f,300.0f);
}

bool Ground::groundedCheck(sf::FloatRect playerBounds, sf::Vector2f playerorigin)
{
    sf::FloatRect groundBounds = superGround.getGlobalBounds();
    sf::Vector2f actualOrigin;

    actualOrigin.x = playerBounds.left + playerorigin.x;
    actualOrigin.y = playerBounds.top + playerorigin.y;

    if (groundBounds.intersects(playerBounds))
    {
        return true;
    }
    else return false;
}

void Ground::update(bool moveDetected, int direction)
{
    sf::Vector2f currPos = superGround.getPosition();

    if (moveDetected)
    {
        //groundTime = groundClock.getElapsedTime();
        //if (groundTime.asSeconds() > TRANS_TIME)
        //{
            superGround.move(5.0f * direction * -1.0f, 0.0f);
          //  groundClock.restart();
        //}

    }

    wing.draw(superGround);

}

float Ground::getAlign()
{
    return(superGround.getPosition().y);
}

Ground::~Ground()
{
    //dtor
}
