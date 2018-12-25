#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"

int main()
{
    sf::Clock realTime;
    bool jumpDetected = false, moveDetected = false;
    int direction = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
    window.setVerticalSyncEnabled(true);
    realTime.restart();
    Player SuperMario(window);

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
					std::cout << "Right key pressed " << direction << " " << moveDetected << std::endl;
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

        SuperMario.update(realTime.getElapsedTime(), moveDetected, jumpDetected, direction);

        window.display();
    }

    return 0;
}
