#include<iostream>
#include<math.h>
#include "SFML/Graphics.hpp"
#include "Player.h"

Player::Player( sf::RenderWindow& windowPtr) : win(windowPtr)
{
    mariotexture.loadFromFile("supermario.png");
    for (marioState = 0; marioState < MAXSTATE; marioState++)
    {
        Mario[marioState].setTexture(mariotexture);
        Mario[marioState].setTextureRect(sf::IntRect((marioState*30),0, 30, 35));
        Mario[marioState].setScale(1.5f,1.5f);
        Mario[marioState].setOrigin(15,35);
    }
    Mario[4] = Mario[2];
    mainPlayer = Mario[0];
    mainPlayer.setPosition(100,100);
    playerClock.restart();
    marioState = 1;

}

void Player::update(sf::Time realTime,  bool moveDetected, bool jumpDetected, int direction)
{
    std::cout << "Player class entered " << direction << " " << moveDetected << std::endl;

    currPos = mainPlayer.getPosition();
    if (isGrounded) {
    // calculate the time taken, initial velocity, range etc

    //detect the keyboard actions and react to that

    if (jumpDetected) {
             initPushVel = 30.0f;
             playerClock.restart();
             mainPlayer = Mario[5];
             playerTime = playerClock.getElapsedTime();
             yTrans = (initPushVel * playerTime.asSeconds() ) +
                (0.5f * ACLTN_GRAVITY * (playerTime.asSeconds() * playerTime.asSeconds()));

    }

    else if (moveDetected) {

            initPushVel = 0;
            yTrans = 0;
            playerTime = playerClock.getElapsedTime();
            if (playerTime.asSeconds() > TRANSITION_TIME)
            {
                marioState++;
                if (marioState > 4)  { marioState = 1;}
                playerClock.restart();

            }
            mainPlayer = Mario[marioState];
            std::cout << "Mario State " << marioState << " " << moveDetected << std::endl;
    }
    else
    {
            initPushVel = 0;
            marioState = 1;
            yTrans = 0;
            playerClock.restart();
            mainPlayer = Mario[0];

    }
    }


    else
        { // let the body flow with the formula

            initPushVel = 0;
            yTrans = 0;
            marioState = 1;
            mainPlayer = Mario[5];
            playerTime = playerClock.getElapsedTime();
            yTrans = (initPushVel * playerTime.asSeconds() ) +
                (0.5f * ACLTN_GRAVITY * (playerTime.asSeconds() * playerTime.asSeconds()));



    }




    mainPlayer.setPosition(currPos);
    mainPlayer.scale(direction,1);
    mainPlayer.move(0, yTrans);

    win.draw(mainPlayer);
    std::cout << "End of Player class " << direction << " " << moveDetected << std::endl;
}


Player::~Player()
{
    //dtor
}
