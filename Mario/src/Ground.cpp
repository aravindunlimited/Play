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
    skipLevel = 100;
    float k;

    for (counter = 0; counter < 10; counter ++)
    {
        if (counter != skipLevel) {
        if (rand() % 7 == 4) k = (rand() % 7) * 10;
        else k = 0;

        superGround.setPosition((counter - 1) * (superGround.getTextureRect().width), INIT_YPOS + k) ;
        spriteSheet.push_back(superGround);
        }
        else
        {
            emptySprite.setPosition((counter) * superGround.getTextureRect().width, 600);
            spriteSheet.push_back(emptySprite);
        }

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

bool Ground::update(bool moveDetected, int direction, sf::FloatRect playerBound)
{
    bool groundMoved = false;
    float k;
    sf::Vector2i barMatrix = barrierCheck(playerBound);

    for (counter = 0; counter < 10; counter++)
    {
        if (moveDetected &&
            (((barMatrix.x == 0) && (direction == -1)) ||
            ((barMatrix.y == 0) && (direction == 1))))
        {
            spriteSheet[counter].move(5.0f * direction * -1.0f, 0.0f);
            groundMoved = true;

        }


    wing.draw(spriteSheet[counter]);
    }

    if (spriteSheet[0].getPosition().x   < superGround.getTextureRect().width * -1)
    {

        if (rand() % 9 == 3 )
        {
            emptySprite.setPosition((spriteSheet[9].getPosition().x + superGround.getTextureRect().width), 600);
            spriteSheet.push_back(emptySprite);
        }
        else
        {
            if (rand() % 7 == 4) k = (rand() % 7) * 10;
            else k = 0;

            superGround.setPosition(spriteSheet[9].getPosition().x + (superGround.getTextureRect().width), INIT_YPOS + k) ;
            spriteSheet.push_back(superGround);

        }
        spriteSheet.erase(spriteSheet.begin());

    }

    if (spriteSheet[9].getPosition().x    > superGround.getTextureRect().width * 8)
    {
        if (rand() % 7 == 4) k = (rand() % 7) * 10;
        else k = 0;
        superGround.setPosition(spriteSheet[0].getPosition().x - (superGround.getTextureRect().width), INIT_YPOS + k) ;
        spriteSheet.erase(spriteSheet.end());
        spriteSheet.insert(spriteSheet.begin(), superGround);

    }

    return(groundMoved);


}

sf::Vector2f Ground::getGroundOrigins(int position)
{
    return(spriteSheet[position].getPosition());

}

Ground::~Ground()
{
    //dtor
}
