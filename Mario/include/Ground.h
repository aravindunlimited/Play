#ifndef GROUND_H
#define GROUND_H
#include<iostream>
#include "SFML/Graphics.hpp"

class Ground
{
    public:
        Ground(sf::RenderWindow& windowPtr);
        bool update(bool moveDetected, int direction,  sf::FloatRect playerBound);
        sf::Vector2i groundedCheck(sf::Vector2f playerorigin);
        sf::Vector2i barrierCheck( sf::FloatRect playerBounds);
        sf::Vector2f getGroundOrigins(int position);
        ~Ground();

    protected:

    private:

        sf::RenderWindow& wing;
        sf::Clock groundClock;
        sf::Time groundTime;
        int counter = 0, skipLevel = 5;
        sf::Texture groundtexture;
        std::vector<sf::Sprite> spriteSheet;
        sf::Sprite superGround;
        const float TRANS_TIME = .10f, TRANS_SPEED = 300.0f, INIT_YPOS = 300.0f;
        bool skippedLevel = false;
        sf::Sprite emptySprite;
};

#endif // GROUND_H
