#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "SFML/Graphics.hpp"
#include "Ground.h"

class Player
{
    public:
        Player(sf::RenderWindow& windowPtr, Ground& ground);
        void update(bool moveDetected, bool jumpDetected, int direction);
        void alignPosition(float alignYpos);
        sf::FloatRect getPlayerBounds();
        sf::Vector2f getPlayerOrigins();
        virtual ~Player();

        sf::Sprite mainPlayer;

    protected:

    private:
        int marioState = 1, MAXSTATE = 6;
        sf::Texture mariotexture;
        sf::Sprite Mario[6];
        sf::Clock playerClock, jumpClock;
        sf::Time playerTime, jumpTime;
        sf::RenderWindow& win;
        Ground& greenGround;
        sf::Vector2f currPos;
        float initPushVel = 0.0f, yTrans = 0.0f;
        bool isJumping = false;
        const float ACLTN_GRAVITY = 50.0f, TRANSITION_TIME = .10f, JUMP_TIME = 0.01f;
        bool isGrounded();
};

#endif // PLAYER_H
