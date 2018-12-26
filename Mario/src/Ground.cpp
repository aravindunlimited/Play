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
    superGround.setTextureRect(sf::IntRect(0,0,100,600));
    groundClock.restart();
    superGround.setPosition(0, 300);

}

void Ground::GroundPos(sf::Vector2f playerorigin)

{

    superGround.setPosition(superGround.getPosition().x,playerorigin.y + 2.0f);
}

bool Ground::groundedCheck(sf::Vector2f playerorigin)
{
    sf::FloatRect groundBounds = superGround.getGlobalBounds();
    playerorigin.y += 5.0f;

    if (groundBounds.contains(playerorigin))
    {
        //GroundPos(playerorigin);
        return true;
    }
    else return false;
}

sf::Vector2i Ground::barrierCheck( sf::FloatRect playerBounds)
{
    sf::FloatRect groundBounds = superGround.getGlobalBounds();
    sf::Vector2f leftCorner, rightCorner;
    sf::Vector2i barMatrix;
    barMatrix.x = 0; barMatrix.y = 0;

    leftCorner.x = playerBounds.left;
    leftCorner.y = playerBounds.top + playerBounds.height;
    rightCorner.x = playerBounds.left + playerBounds.width;
    rightCorner.y = playerBounds.top + playerBounds.height;


    if (groundBounds.contains(leftCorner))
    {
        barMatrix.x =  1;
    }

    if (groundBounds.contains(rightCorner))
    {
        barMatrix.y = 1;
    }

    return barMatrix;
}

sf::Sprite& Ground::update(bool moveDetected, int direction, sf::Vector2i barMatrix)
{
    sf::Vector2f currPos = superGround.getPosition();



    if (moveDetected &&
        (((barMatrix.x == 0) && (direction == -1)) ||
         ((barMatrix.y == 0) && (direction == 1))))
    {
        //groundTime = groundClock.getElapsedTime();
        //if (groundTime.asSeconds() > TRANS_TIME)
        //{
            superGround.move(5.0f * direction * -1.0f, 0.0f);
          //  groundClock.restart();
        //}

    }

    return(superGround);

}

float Ground::getAlign()
{
    return(superGround.getPosition().y);
}

Ground::~Ground()
{
    //dtor
}
