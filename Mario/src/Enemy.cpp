#include<iostream>
#include<math.h>
#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include "Ground.h"

Enemy::Enemy( sf::RenderWindow* windowPtr, Ground* ground, sf::Texture* enemyTex, int floater) : wine(windowPtr), greenGround(ground), enemytexture(enemyTex)
{

    Goons.setTexture(*enemytexture);
    Goons.setTextureRect(sf::IntRect(0,0,35,35));
    floatType = floater;
    Goons.setOrigin(Goons.getTextureRect().width/2, Goons.getTextureRect().height);
    Goons.setPosition(200 + ((rand() % 7) * 100),-100 + (floatType * 200));
    enemyClock.restart();

    reverseMove = 1;
    previousXval = 0;
    prevCounter = 0;
}

bool Enemy::update(int direction, bool moveDetected)
{
    float screenMove = 0, moveGoon = 0;
    sf::Vector2i barMatrix;

    if (isGrounded())
    {

        barMatrix = greenGround->barrierCheck(Goons.getGlobalBounds());
        if (barMatrix.x == 1)
        {
            reverseMove = -1;

        }
        if (barMatrix.y == 1)
        {
            reverseMove = 1;

        }

        enemyTime = enemyClock.getElapsedTime();
        if (enemyTime.asSeconds() > TRANSITION_TIME)
        {
            moveGoon = -3.0f * reverseMove;
            enemyClock.restart();
        }
        else
        {
            moveGoon = 0;
        }

        if(moveDetected)
        {
            screenMove = -5.0f * direction;
        }
        else
        {
            screenMove = 0.0f;
        }

        Goons.move( moveGoon + screenMove , 0);
        //previousXval = greenGround.getGroundOrigins(groundNum).x - Goons.getPosition().x ;





    }
    else
        { // let the body flow with the formula

            enemyTime = enemyClock.getElapsedTime();
            if (floatType == 1)
            {
                moveGoon = 2 * (sin(enemyTime.asSeconds()));
                screenMove = -1.0f;

            }
            else if (floatType == 2)
            {

                moveGoon = 0;
                screenMove = -3.0f;

            }
            else
            {
                moveGoon = 0.5f * ACLTN_GRAVITY * (enemyTime.asSeconds() * enemyTime.asSeconds());
                screenMove = 0.0f;
            }

            if(moveDetected)
            {
                screenMove += -5.0f * direction;
            }
            else
            {
                screenMove += 0.0f;
            }
            Goons.move(screenMove , moveGoon );

        }

    wine->draw(Goons);

    if (Goons.getPosition().y > 500) return(false);
    else return(true);

}

sf::Vector2i Enemy::hitCheck( sf::FloatRect playerBounds)
{

    sf::Vector2f leftCorner, rightCorner, bottom;
    sf::Vector2i barMatrix;
    sf::FloatRect groundBounds;

    barMatrix.x = 0; barMatrix.y = 0;
    //for (counter = 0; counter < 10; counter++)
    //{


    groundBounds = Goons.getGlobalBounds();

    leftCorner.x = playerBounds.left;
    bottom.y = playerBounds.top + playerBounds.height;
    leftCorner.y, rightCorner.y =  playerBounds.top + (playerBounds.height/2);
    rightCorner.x = playerBounds.left + playerBounds.width;
    bottom.x = playerBounds.left + (playerBounds.width/2);
    //rightCorner.y = playerBounds.top + playerBounds.height;

    if (groundBounds.contains(bottom))
    {
        barMatrix.x =  9;
        barMatrix.y = 9;
        Goons = emptySprite;

    }

    else if (groundBounds.contains(leftCorner))
    {
        barMatrix.x =  1;

    }

    else if (groundBounds.contains(rightCorner))
    {
        barMatrix.y = 1;

    }
    //}


    return barMatrix;


}

sf::FloatRect Enemy::getEnemyBounds()
{

    return(Goons.getGlobalBounds());
}

void Enemy::alignPosition(float alignYpos)
{
    Goons.setPosition(Goons.getPosition().x, alignYpos);
}

bool Enemy::isGrounded()
{
    sf::Vector2i GroundStatus;
    GroundStatus = greenGround->groundedCheck(Goons.getPosition());
    if ((GroundStatus.x == 1) && (floatType == 0))
        {
            if (Goons.getPosition().y > greenGround->getGroundOrigins(GroundStatus.y).y)
                {
                    alignPosition(greenGround->getGroundOrigins(GroundStatus.y).y - 1.0f);
                }
            groundNum = GroundStatus.y;
            return(true);
        }
    else return(false);
}

Enemy::~Enemy()
{
//    delete Goons;
}
