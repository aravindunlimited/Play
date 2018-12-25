#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "SFML/Graphics.hpp"

class Player
{
    public:
        bool isGrounded = true;
        Player(sf::RenderWindow& windowPtr);
        void update(sf::Time realTime, bool moveDetected, bool jumpDetected, int direction);
        virtual ~Player();

        sf::Sprite mainPlayer;

    protected:

    private:
        int marioState = 1, MAXSTATE = 6;
        sf::Texture mariotexture;
        sf::Sprite Mario[6];
        sf::Clock playerClock;
        sf::Time playerTime;
        sf::RenderWindow& win;
        sf::Vector2f currPos;
        float initPushVel = 0.0f, yTrans = 0.0f;
        bool isJumping = false;
        const float ACLTN_GRAVITY = 9.8f, TRANSITION_TIME = .10f;
};

#endif // PLAYER_H
