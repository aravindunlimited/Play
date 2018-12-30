#ifndef BULLET_H
#define BULLET_H


class Bullet
{
    public:
        /** Default constructor */
        Bullet(sf::RenderWindow* windowPtr, sf::Texture* bulletTex, sf::Vector2f initialPos, int origdir);
        void update(bool moveDetected, int direction);
        sf::Vector2f getBulletPos();
        sf::FloatRect getBulletBounds();
        /** Default destructor */
        ~Bullet();

    protected:

    private:
        sf::Sprite bullet;
        sf::RenderWindow* winb;
        sf::Clock bulletClock;
        sf::Time bulletTime;
        sf::Vector2f initPos;
        int original_dir = 1;
        float TRANSITION_TIME = .01f;

};

#endif // BULLET_H
