#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Ground.h"

int main()
{
    sf::Clock realTime;
    sf::Sprite PlayerSprite, groundSprite;
    sf::Vector2i barrierMatrix = sf::Vector2i(0,0);
    bool jumpDetected = false, moveDetected = false;
    int direction = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
    window.setVerticalSyncEnabled(true);
    realTime.restart();
    Player SuperMario(window);
    Ground greenGround(window);
    //grounds.push_back(greenGround);

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

        //Ground.update(realTime.getElapsedTime(), moveDetected, jumpDetected, direction);

        PlayerSprite = SuperMario.update(realTime.getElapsedTime(), moveDetected, jumpDetected, direction);
        window.draw(PlayerSprite);
        SuperMario.isGrounded = false;
        //for (int i = 0; i < grounds.max_size();i++)
        //{
            //grounds[i].update(moveDetected, direction);
            //if (grounds[i].groundedCheck(SuperMario.getPlayerBounds())) { SuperMario.isGrounded = true;}

            if (greenGround.groundedCheck(PlayerSprite.getPosition()))
                {
                    SuperMario.isGrounded = true;
                    //SuperMario.alignPosition(300);
            }

            barrierMatrix = greenGround.barrierCheck(SuperMario.getPlayerBounds());

            groundSprite = greenGround.update(moveDetected, direction, barrierMatrix);
            if ((PlayerSprite.getPosition().y > groundSprite.getPosition().y) && (SuperMario.isGrounded))
            {
                SuperMario.alignPosition(groundSprite.getPosition().y - 1.0f);
            }
            window.draw(groundSprite);

        //}


        window.display();
    }

    return 0;
}
