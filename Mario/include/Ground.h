#ifndef GROUND_H
#define GROUND_H
#include<iostream>
#include "SFML/Graphics.hpp"

class Ground
{
    public:
        Ground(sf::RenderWindow& windowPtr);
        sf::Sprite& update(bool moveDetected, int direction, sf::Vector2i barMatrix);
        bool groundedCheck(sf::Vector2f playerorigin);
        sf::Vector2i barrierCheck( sf::FloatRect playerBounds);
        float getAlign();
        ~Ground();

    protected:

    private:

        sf::RenderWindow& wing;
        std::vector<sf::Sprite> spriteSheet;
        sf::Clock groundClock;
        sf::Time groundTime;
        sf::Texture groundtexture;
        sf::Sprite superGround;
        const float TRANS_TIME = .10f, TRANS_SPEED = 300.0f;
        void GroundPos(sf::Vector2f playerorigin);
};

#endif // GROUND_H
