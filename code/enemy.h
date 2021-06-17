#include <SFML/Graphics.hpp>
extern  const int rt;
extern const int mapWidth;
extern const int mapHeight;
extern sf::String MapLayout[];

using namespace std;
using namespace sf;

/**
* \brief enemy class
* 
* \param float x - x coordinate of enemy
* \param float y - y coordinate of enemy
* \param float dx - x axis velocity of enemy
* \param float dy - y axis velocity of enemy
* \param float w - width of enemy
* \param float h - hegth of enemy
* \param float speed - general velocity
* \param float dirCount - counter for managing enemy movement
* \param float dirCountCap - max value of dirCount
* \param float animCounter - counter for managing animation
* \param int direction - movement direction
* \param int damage - damage which enemy deals
* \param sf::RectangleShape hitbox - enemy hitxbox
* \param sf::Image image - enemy model image
* \param sf::Texture texture - enemy model texture
* \param sf::Sprite sprite - enemy sprite
*/
class Enemy {
public:	///< actually no private in the class
	float x, y, dx, dy = 0; 
	int w = 32;
	int h = 32;
	float dirCount = 0;
	float dirCountCap = 1000;
	float animCounter = 0;
	float speed = 0.1; 
	int direction = 0; 
	int damage = 20;
	RectangleShape hitbox;
	Image image;
	Texture texture;
	Sprite sprite;
	Enemy(float X, float Y) {
		x = X; y = Y;
		hitbox.setSize(Vector2f(w, h));
		hitbox.setPosition(x, y);
		hitbox.setFillColor(Color::Red);
		image.loadFromFile("images/enemy.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	/**
	* \brief movement function which handles enemy movement and things connected
	* such as walking animation, interacions with map borders
	* sets enemy's hitbox and sprite position
	* 
	* \param time is for smoother enemy movement and is used
	* in dirCounter to manage the direction in which enemy is moving
	*/
	void movement(float time) {
		getDxDy();

		if (dirCount >= dirCountCap) {
			dirCount = 0;
			direction = rand() % 4;
		}
		dirCount += time;

		x += dx * time;
		y += dy * time;
		animation(time);
		WithMapInteractions();
		hitbox.setPosition(x, y);
		sprite.setPosition(hitbox.getPosition());
	
	}

	/**
	* \brief function gets dx and dy according to direction value
	*/
	void getDxDy() {
		if (direction == 0) {
			dx = 0; dy = speed;
		}
		else if (direction == 1) {
			dx = 0; dy = -speed;
		}
		else if (direction == 2) {
			dx = speed; dy = 0;
		}
		else if (direction == 3) {
			dx = -speed; dy = 0;
		}
	}


	/**
	* \brief function for making enemy not cross the map borders
	*/
	void WithMapInteractions() { 
		
		if (x < rt) {
			x = rt;
			dirCount = dirCountCap;
		}
		if (x > (mapWidth - 1) * rt - w) {
			x = (mapWidth - 1) * rt - w;
			dirCount = dirCountCap;
		}
		if (y < rt) {
			y = rt;
			dirCount = dirCountCap;
		}
		if (y > (mapHeight - 1) * rt - h) {
			y = (mapHeight - 1) * rt - h;
			dirCount = dirCountCap;
		}
	}
	/**
	* \brief animation function handles enemy movement animation
	* 
	* \param time is used in counter animCounter to select what 
	* part of enemy.png programm should give to sprite
	*/
	void animation(float time) {
		if (direction == 0) {
			animCounter += 0.005f * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 0, w, h));
		}
		if (direction == 1) {
			animCounter += 0.005f * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 3 * h, w, h));
		}
		if (direction == 2) {
			animCounter += 0.005f * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), 2 * h, w, h));
		}
		if (direction == 3) {
			animCounter += 0.005f * time;
			if (animCounter > 3) animCounter -= 3;
			sprite.setTextureRect(IntRect(w * int(animCounter), h, w, h));
		}
	}
};



