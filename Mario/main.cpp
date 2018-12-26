#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Ground.h"

int main()
{
    sf::Clock realTime;
    sf::Vector2i GroundStatus;
    bool jumpDetected = false, moveDetected = false;
    int direction = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
    window.setVerticalSyncEnabled(true);
    realTime.restart();
    Player SuperMario(window);
    Ground greenGround(window);


    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
               {
                 window.close();
               }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    direction = -1;
					moveDetected = true;
                }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    direction = 1;
					moveDetected = true;

                }
            else
                {
                    moveDetected = false;

                }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    jumpDetected = true;
                }
            else jumpDetected = false;



        }


        SuperMario.update(realTime.getElapsedTime(), moveDetected, jumpDetected, direction);

        SuperMario.isGrounded = false;

        GroundStatus = greenGround.groundedCheck(SuperMario.getPlayerOrigins());

        if (GroundStatus.x == 1)
            {
                SuperMario.isGrounded = true;
            }


        greenGround.update(moveDetected, direction, SuperMario.getPlayerBounds());
        if ((SuperMario.getPlayerOrigins().y > greenGround.getGroundOrigins(GroundStatus.y).y) && (SuperMario.isGrounded))
            {
                SuperMario.alignPosition(greenGround.getGroundOrigins(GroundStatus.y).y - 1.0f);
            }




        window.display();
    }

    return 0;
}
