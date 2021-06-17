#pragma once
#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
//#include "enemy.h"
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace sf;


class Hero {
public:
    ///x coordinate of player
    float x = 0;
    ///y coordinate of enemy
    float y = 0;
    ///x axis player velocity
    float dx = 0;
    ///y axis player velocity
    float dy = 0;
    ///general player velocity
    float speed = 0;
    ///x coordinate of camera
    float cameraX = 0;
    ///y coordinate of camera
    float cameraY = 0;
    ///axis x and axis y length of camera
    float camLength = rt * mapWidth / 2;
    ///width of hero
    int w = 32;
    ///heigth of hero
    int h = 48;
    ///variable for handling direction of movement
    int direction = 0;
    /// amount of hero's hp
    int hp = 100;
    ///counter for makin hero immune after collision
    float timeAfterCollision = 0; 
    ///counter for managing hero animation
    float animCounter = 0;
    /// if hero is alive
    bool alive = true;
    ///hero hitbox
    RectangleShape hitbox;
    ///hero model image
    Image image; 
    ///hero model texture 
    Texture texture; 
    ///hero sprite 
    Sprite sprite; 
    ///camera 
    View view; 

    /**
    * \brief hero object constructor
    * 
    * \param X - desired starting x coord of hero
    * 
    * \param Y - desired starting y coord of hero
    * 
    */
    Hero(float X, float Y);

    /**
    * \brief function which handles general hero movement and things connected
    * such as keyboard surveillance, moving animation,
    * interactions of hero with map, sets position of hitbox
    * and sprite
    * 
    * \param time is time elapsed since the last game window
    * update and is used for smoother hero movement
    */
    void movement(float time);
    /**
    * \brief function which checks direction and sets dx and
    * dy to certain value according to conditions
    */
    void checkDxDy();

    /**
    * \brief keyboard function handles key pressings
    */
    void keyboard();

    /**
    * \brief animation function manages hero movement animation
    * 
    * \param time is time elapsed since the last game window update
    * and is used for changing hero's sprite
    */
    void animation(float time);

    /**
    * \brief utility function for centering camera on hero
    * 
    * \return sf::View view which is camera 
    */
    View viewCentring();

    /**
    * \brief function which oversees hero not crossing map borders
    */
    void withMapInteractions();

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
    //void withEnemyCollision(Enemy enemy, float time);
};
#endif