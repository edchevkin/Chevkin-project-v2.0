#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace std;
using namespace sf;


class Enemy {
public:	// actually no private in the class
	///x coordinate of enemy
	float x = 0;
	/// y coordinate of enemy
	float y = 0;
	///x axis velocity of enemy
	float dx = 0;
	///y axis velocity of enemy
	float dy = 0;
	///width of enemy
	int w = 32;
	///heigth of enemy
	int h = 32;
	///counter for managing enemy movement
	float dirCount = 0;
	///max value of dirCount
	float dirCountCap = 1000;
	///counter for managing animation
	float animCounter = 0;
	///general velocity
	float speed = 0.1; 
	///variable for managing enemy movement
	int direction = 0; 
	///damage which enemy deals
	int damage = 20;
	///enemy hitxbox
	RectangleShape hitbox;
	///enemy model image
	Image image;
	///enemy model texture
	Texture texture;
	///enemy sprite
	Sprite sprite;
	Enemy(float X, float Y);

	/**
	* \brief movement function which handles enemy movement and things connected
	* such as walking animation, interacions with map borders
	* sets enemy's hitbox and sprite position
	* 
	* \param time is for smoother enemy movement and is used
	* in dirCounter to manage the direction in which enemy is moving
	*/
	void movement(float time);

	/**
	* \brief function gets dx and dy according to direction value
	*/
	void getDxDy();

	/**
	* \brief function for making enemy not cross the map borders
	*/
	void WithMapInteractions();

	/**
	* \brief animation function handles enemy movement animation
	* 
	* \param time is used in counter animCounter to select what 
	* part of enemy.png programm should give to sprite
	*/
	void animation(float time);
};
#endif



