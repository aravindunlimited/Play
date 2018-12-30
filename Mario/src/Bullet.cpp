#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow* windowPtr, sf::Texture* bulletTex, sf::Vector2f initialPos, int origdir) : winb(windowPtr), original_dir(origdir)
{
    initPos = initialPos;
    //sf::Texture bulletTexture;
    bullet.setTexture(*bulletTex);
    bullet.setTextureRect(sf::IntRect(0,0,20,20));
    bullet.setOrigin(10,10);
    bullet.setPosition(initPos);
    bulletClock.restart();

}

void Bullet::update(bool moveDetected, int direction)
{
    float screenMove = 0, moveBullet = 0;
    bulletTime = bulletClock.getElapsedTime();
        if (bulletTime.asSeconds() > TRANSITION_TIME)
        {
            moveBullet = 6.0f * original_dir;
            bulletClock.restart();
        }
        else
        {
            moveBullet = 0;
        }

        if(moveDetected)
        {
            screenMove = -5.0f * direction;
        }
        else
        {
            screenMove = 0.0f;
        }

        bullet.move( moveBullet + screenMove , 0);
        winb->draw(bullet);

}

sf::Vector2f Bullet::getBulletPos()
{
    return(bullet.getPosition());
}

sf::FloatRect Bullet::getBulletBounds()
{
    return(bullet.getGlobalBounds());

}

Bullet::~Bullet()
{
    //dtor

}
