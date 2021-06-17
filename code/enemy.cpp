#include "enemy.h"

Enemy::Enemy(float X, float Y) 
{
	x = X; y = Y;
	hitbox.setSize(Vector2f(float(w), float(h)));
	hitbox.setPosition(x, y);
	hitbox.setFillColor(Color::Red);
	image.loadFromFile("images/enemy.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Enemy::movement(float time) {
	if (dirCount >= dirCountCap) {
		dirCount = 0;
		direction = rand() % 4;
	}
	dirCount += time;

	x += dx * time;
	y += dy * time;
	hitbox.setPosition(x, y);
	sprite.setPosition(hitbox.getPosition());

}

void Enemy::checkDxDy() {
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

 void Enemy::withMapInteractions() {
	if (x < rt) {
		x = rt;
		dirCount = dirCountCap;
	}
	if (x > (mapWidth - 1) * rt - float(w)) {
		x = (mapWidth - 1) * rt - float(w);
		dirCount = dirCountCap;
	}
	if (y < rt) {
		y = rt;
		dirCount = dirCountCap;
	}
	if (y > (mapHeight - 1) * rt - float(h)) {
		y = (mapHeight - 1) * rt - float(h);
		dirCount = dirCountCap;
	}
}

void Enemy::animation(float time) {
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

void Enemy::update(float time) {
	Enemy::checkDxDy();
	Enemy::withMapInteractions();
	Enemy::animation(time);
	Enemy::movement(time);
}