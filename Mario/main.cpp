#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"
#include "Bullet.h"

int main()
{
    sf::Clock realTime;
    sf::Vector2i GroundStatus, hitChecker;
    sf::Texture enemytexture[3];
    sf::Texture bulletTex;
    const int MAX_GOONS = 3;
    enemytexture[0].loadFromFile("ghost.png");
    enemytexture[1].loadFromFile("goomba.png");
    enemytexture[2].loadFromFile("pig.png");
    bulletTex.loadFromFile("blueball.png");
    bool groundMoved = false, playerDead = false, enemyAlive = false;
    bool jumpDetected = false, moveDetected = false, fired = false, bulletEnabled = false;
    int direction = 1;
    int i , j , k;
    sf::FloatRect playerBounds;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
    window.setVerticalSyncEnabled(true);
    realTime.restart();

    Ground greenGround(window);
    Player SuperMario(window, greenGround);
    std::vector<Enemy> Goon;
    std::vector<Bullet> bullets;

    for (i = 0 ; i < MAX_GOONS; i++)
    {
    k = rand() % 3;
    Enemy goonie(&window, &greenGround, &enemytexture[k], k);
    Goon.push_back(goonie);
    goonie.~Enemy();

    }



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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                fired = true;
            }



        }


        SuperMario.update(moveDetected, jumpDetected, direction);
        playerBounds = SuperMario.getPlayerBounds();

        if (fired)
        {
            Bullet bullet(&window, &bulletTex, sf::Vector2f(playerBounds.left + (playerBounds.width/2), playerBounds.top + (playerBounds.height/2)), direction);
            bullets.push_back(bullet);
            bullet.~Bullet();
            fired = false;

            bulletEnabled = true;
        }

        if (bulletEnabled)
        {
            for(j=0; j < bullets.size();j++)
            {
                bullets[j].update(moveDetected, direction);
                if (bullets[j].getBulletPos().x > 820)
                {
                    bullets.erase(bullets.begin() + j);
                }
            }

            if (bullets.size() <= 0) bulletEnabled = false;

        }


        for (i = 0; i < Goon.size(); i++)
        {


            enemyAlive = Goon[i].update(direction, groundMoved);
            if (!enemyAlive || Goon[i].getEnemyBounds().left < -100)
            {
                Goon[i].~Enemy();
                new (&Goon[i]) Enemy(&window, &greenGround, &enemytexture[rand() % 3], rand() % 3);
            }
            hitChecker = Goon[i].hitCheck(playerBounds);

            if ((hitChecker.x == 1) || (hitChecker.y == 1))
            {
                playerDead = true;
            }
            else if (hitChecker.x == 9)
            {
                Goon.erase(Goon.begin() + i);
            }

            hitChecker = sf::Vector2i(0,0);

            for(j = 0; j< bullets.size() & ((hitChecker.x != 1) &  (hitChecker.y != 1)); j++)
            {


                hitChecker = Goon[i].hitCheck(bullets[j].getBulletBounds());

                if ((hitChecker.x == 1) || (hitChecker.y == 1))
                {
                    bullets.erase(bullets.begin() + j);
                    Goon.erase(Goon.begin() + i);

                }
                else if (hitChecker.x == 9)
                {


                }
            }
        }


      //  SuperMario.isGrounded = false;

        GroundStatus = greenGround.groundedCheck(SuperMario.getPlayerOrigins());

     /*   if (GroundStatus.x == 1)
            {
                SuperMario.isGrounded = true;
            }

*/


        groundMoved = greenGround.update(moveDetected, direction, playerBounds);
        if ((SuperMario.getPlayerOrigins().y > greenGround.getGroundOrigins(GroundStatus.y).y) && (GroundStatus.x == 1))
            {
                SuperMario.alignPosition(greenGround.getGroundOrigins(GroundStatus.y).y - 1.0f);
            }




        window.display();
        if (playerDead)
        {
            std::cout<<"Player Dead!"<<std::endl;
        }
    }

    return 0;
}
