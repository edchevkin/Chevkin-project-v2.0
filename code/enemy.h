#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace std;
using namespace sf;


class Enemy {
public:	// actually no private in the class
	///height of map
	static const int mapHeight = 10;
	///width of map
	static const int mapWidth = 10;
	///resolution of map tile
	static const int rt = 32;
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
	float speed = 0.1f; 
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
	/**
	* \brief enemy object constructor
	* 
	* \param X - desired starting x coord of enemy
	* 
	* \param Y - desired starting y coord of enemy
	*/
	Enemy(float X, float Y);

	/**
	* \brief movement function which handles enemy movement and things connected
	* such as walking animation, interacions with map borders
	* sets enemy's hitbox and sprite position
	* 
	* \param time - for smoother enemy movement and is used
	* in dirCounter to manage the direction in which enemy is moving
	*/
	void movement(float time);

	/**
	* \brief function gets dx and dy according to direction value
	*/
	void checkDxDy();

	/**
	* \brief function for making enemy not cross the map borders
	*/
	void withMapInteractions();

	/**
	* \brief animation function handles enemy movement animation
	* 
	* \param time - used in counter animCounter to select what 
	* part of enemy.png programm should give to sprite
	*/
	void animation(float time);

	/**
	*\brief manages all hero functions such as moving, obeying map borders,
	* keyboard surveillance, setting camera position and colliding with enemy
	*/
	void update(float time);
};
#endif



