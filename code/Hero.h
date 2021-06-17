#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace sf;
using namespace std;

/**
* \brief hero class
* \param float x - x coordinate of player
* \param float y - y coordinate of enemy
* \param float dx - x axis player velocity
* \param float dy - y axis player velocity
* \param float speed - general player velocity
* \param float cameraX - x coordinate of camera
* \param float cameraY - y coordinate of camera
* \param float w - width of hero
* \param float h - heigth of hero
* \param float camLength - axis x and axis y length of camera
* \param float timeAfterCollision - counter for makin hero immune after collision
* \param float animCounter - counter for managing hero animation
* \param int hp - amount of hero's hp
* \param int direction - variable for handling direction of movement
* \param bool alive - if hero is alive - alive = true;
* \param sf::RectangleShape hitbox - hero hitbox
* \param sf::Image image - hero model image
* \param sf::Texture texture - hero model texture
* \param sf::Sprite sprite - hero sprite
* \param sf::View view - camera
*/
class Hero {
public:
    float x, y, dx, dy, speed = 0;
    float cameraX, cameraY = 0;
    int w = 32;
    int h = 48;
    int direction = 0;
    int hp = 100;
    float camLength = rt * mapWidth / 2 ;
    float timeAfterCollision = 0; 
    float animCounter = 0;
    bool alive = true;
    RectangleShape hitbox; ///< hitbox
    Image image; ///< image of models
    Texture texture; ///< texture of models
    Sprite sprite; ///< hero sprite
    View view; ///< camera

    /**
    * \brief hero object constructor
    * 
    * \param X - desired starting x coord of hero
    * 
    * \param Y - desired starting y coord of hero
    * 
    * \param W - desired width of hero hitbox and sprite
    * 
    * \param H - desired height of hero hitbox and sprite
    * 
    */
    Hero(float X, float Y) {
        hitbox.setSize(Vector2f(w, h));
        hitbox.setPosition(x, y);
        image.loadFromFile("images/hero.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        x = X; y = Y;
        view.reset(FloatRect(x, y, camLength * 2, camLength * 2));
        dx = 0; dy = 0;
    }

    /**
    * \brief function which handles general hero movement and things connected
    * such as keyboard surveillance, moving animation,
    * interactions of hero with map, sets position of hitbox
    * and sprite
    * 
    * \param time is time elapsed since the last game window
    * update and is used for smoother hero movement
    */
    void movement(float time) {
        
        keyboard();
        
        checkDxDy();

        y += dy * time;
        x += dx * time;
        speed = 0;

        WithMapInteractions();
        animation(time);
        hitbox.setPosition(x, y);
        sprite.setPosition(hitbox.getPosition());
        viewCentersOnHero();
    }
    /**
    * \brief function which checks direction and sets dx and
    * dy to certain value according to conditions
    */
    void checkDxDy() {
        if (direction == 0) {
            dx = 0.0f; dy = speed;
        }
        else if (direction == 1) {
            dx = -speed; dy = 0;
        }
        else if (direction == 2) {
            dx = speed; dy = 0;
        }
        else if (direction == 3) {
            dx = 0; dy = -speed;
        }
    }

    /**
    * \brief keyboard function handles key pressings
    */
    void keyboard() {
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 0;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 2;
            speed = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3; 
            speed = 0.1;
             
        }
    }

    /**
    * \brief animation function manages hero movement animation
    * 
    * \param time is time elapsed since the last game window update
    * and is used for changing hero's sprite
    */
    void animation(float time) {
        
        if (direction == 0) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 0, w, h));
        }
        if (direction == 1) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), h, w, h));
        }
        if (direction == 2) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 2 * h, w, h));
        }
        if (direction == 3) {
            animCounter += 0.005 * time;
            if (animCounter > 4) animCounter -= 4;
            sprite.setTextureRect(IntRect(w * int(animCounter), 3 * h, w, h));
        }
    }

    /**
    * \brief utility function for centering camera on hero
    * 
    * \return sf::View view which is camera 
    */
    View viewCentersOnHero() {   
        cameraX = x + w / 2; cameraY = y + h / 2;
        if (cameraX < camLength)
            cameraX = camLength;
        if (cameraY < camLength)
            cameraY = camLength;
        if (cameraX > mapWidth * rt - camLength)
            cameraX = mapWidth * rt - camLength;
        if (cameraY > mapHeight * rt - camLength)
            cameraY = mapHeight * rt - camLength;
        view.setCenter(cameraX, cameraY);
        return view;
    }

    /**
    * \brief function which oversees hero not crossing map borders
    */
    void WithMapInteractions() {
        if (x < rt)
            x = rt;
        if (x > (mapWidth - 1) * rt - w)
            x = (mapWidth - 1) * rt - w;
        if (y < rt)
            y = rt;
        if (y > (mapHeight - 1) * rt - h)
            y = (mapHeight - 1) * rt - h;
    }

    /**
    * \brief function which checks if hero collides with enemy and
    * reduces hp if so
    * 
    * \param enemy class object
    * 
    * \param time is time elapsed after last game window clear
    * and is used in  timeAfterCollision counter to make hero
    * immune for certain amount of time
    */
    void heroWithEnemyCollision(Enemy enemy, float time) {
        
        if (timeAfterCollision > 10) {
            if (FloatRect(x + w / 4, y + h / 4, w / 2 , h / 2).intersects(FloatRect(enemy.x, enemy.y, enemy.w, enemy.h))) {
                hp -= enemy.damage;
                timeAfterCollision = 0;
            }
        }
        if (hp <= 0) 
            alive = false;

        timeAfterCollision += 0.005 * time;
    }
};