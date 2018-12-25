#ifndef GROUND_H
#define GROUND_H
#include<iostream>
#include "SFML/Graphics.hpp"

class Ground
{
    public:
        Ground(sf::RenderWindow& windowPtr);
        void update(bool moveDetected, int direction);
        bool groundedCheck(sf::FloatRect playerBounds, sf::Vector2f playerorigin);
        float getAlign();
        ~Ground();

    protected:

    private:

        sf::RenderWindow& wing;
        sf::Clock groundClock;
        sf::Time groundTime;
        sf::Texture groundtexture;
        sf::Sprite superGround;
        const float TRANS_TIME = .10f, TRANS_SPEED = 300.0f;
};

#endif // GROUND_H
