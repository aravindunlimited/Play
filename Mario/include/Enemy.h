#ifndef ENEMY_H
#define ENEMY_H
#include<iostream>
#include "SFML/Graphics.hpp"
#include "Ground.h"


class Enemy
{
    public:
        /** Default constructor */
        Enemy(sf::RenderWindow* windowPtr, Ground* ground, sf::Texture* enemyTex, int floater );
        bool update(int direction, bool moveDetected);
        sf::Vector2i hitCheck( sf::FloatRect playerBounds);
        sf::FloatRect getEnemyBounds();
        void alignPosition(float alignYpos);


        /** Default destructor */
        ~Enemy();

    protected:

    private:
        int enemyState = 1, MAXSTATE = 6;
        sf::Sprite Goons;
        int reverseMove;
        sf::Texture* enemytexture;
        sf::Clock enemyClock, jumpClock;
        sf::Time enemyTime, jumpTime;
        sf::RenderWindow* wine;
        int groundNum = 0;
        Ground* greenGround;
        sf::Vector2f currPos;
        float xPos = 0.0f;
        float ACLTN_GRAVITY = 50.0f, TRANSITION_TIME = .05f;
        sf::Sprite emptySprite;
        int floatType = 0;
        bool isGrounded();
        float previousXval;
        int prevCounter;
};

#endif // ENEMY_H
