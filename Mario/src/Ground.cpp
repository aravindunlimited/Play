#include<iostream>
#include<math.h>
#include "SFML/Graphics.hpp"
#include "Ground.h"

Ground::Ground(sf::RenderWindow& windowPtr) : wing(windowPtr)
{
    groundtexture.loadFromFile("brick.jpg", sf::IntRect(0,0,30,30));
    groundtexture.setRepeated(true);
    superGround.setTexture(groundtexture);
    superGround.setTextureRect(sf::IntRect(0,0,100,600));
    groundClock.restart();
    for (counter = 0; counter < 10; counter ++)
    {
        superGround.setPosition((counter - 1) * (superGround.getTextureRect().width), INIT_YPOS + ((rand() % 7) * 10)) ;
        spriteSheet.push_back(superGround);

    }


}

sf::Vector2i Ground::groundedCheck(sf::Vector2f playerorigin)
{
    sf::Vector2i GroundStatus;
    sf::FloatRect groundBounds;
    GroundStatus.x = 0;
    GroundStatus.y = 0;
    playerorigin.y += 3.0f;

    for (counter = 0; counter < 10; counter++)
    {
        groundBounds = spriteSheet[counter].getGlobalBounds();

        if (groundBounds.contains(playerorigin))
        {
            GroundStatus.x = 1;
            GroundStatus.y = counter;
        }

    }

    return(GroundStatus);
}

sf::Vector2i Ground::barrierCheck( sf::FloatRect playerBounds)
{

    sf::Vector2f leftCorner, rightCorner;
    sf::Vector2i barMatrix;
    sf::FloatRect groundBounds;

    barMatrix.x = 0; barMatrix.y = 0;
    for (counter = 0; counter < 10; counter++)
    {


    groundBounds = spriteSheet[counter].getGlobalBounds();

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
    }


    return barMatrix;


}

void Ground::update(bool moveDetected, int direction, sf::FloatRect playerBound)
{
    sf::Vector2i barMatrix = barrierCheck(playerBound);



    for (counter = 0; counter < 10; counter++)
    {
        if (moveDetected &&
            (((barMatrix.x == 0) && (direction == -1)) ||
            ((barMatrix.y == 0) && (direction == 1))))
        {
            spriteSheet[counter].move(5.0f * direction * -1.0f, 0.0f);

        }


    wing.draw(spriteSheet[counter]);
    }

    if (spriteSheet[0].getPosition().x   < superGround.getTextureRect().width * -1)
    {
        superGround.setPosition(spriteSheet[9].getPosition().x + (superGround.getTextureRect().width), INIT_YPOS + ((rand() % 7) * 10)) ;
        spriteSheet.erase(spriteSheet.begin());
        spriteSheet.push_back(superGround);

    }

    if (spriteSheet[9].getPosition().x    > superGround.getTextureRect().width * 8)
    {
        superGround.setPosition(spriteSheet[0].getPosition().x - (superGround.getTextureRect().width), INIT_YPOS + ((rand() % 7) * 10)) ;
        spriteSheet.erase(spriteSheet.end());
        spriteSheet.insert(spriteSheet.begin(), superGround);

    }


}

sf::Vector2f Ground::getGroundOrigins(int position)
{
    return(spriteSheet[position].getPosition());

}

Ground::~Ground()
{
    //dtor
}
