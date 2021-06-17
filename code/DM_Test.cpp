#include "doctest.h"
#include "hero.h"
#include "enemy.h"

//!hero
//hero.viewCentring()
TEST_CASE("cameraCheck"){
	Hero hero(100, 100);
	hero.x = 32; hero.y = 32;
	hero.viewCentring();
	REQUIRE(hero.cameraX == hero.camLength);
	REQUIRE(hero.cameraY == hero.camLength);
}
TEST_CASE("cameraCheck2") {
	Hero hero(100, 100);
	hero.x = float((Hero::mapWidth - 1) * Hero::rt - hero.w); hero.y = float((Hero::mapHeight - 1) * Hero::rt - hero.h);
	hero.viewCentring();
	REQUIRE(hero.cameraX == Hero::mapWidth * Hero::rt - hero.camLength);
	REQUIRE(hero.cameraY == Hero::mapHeight * Hero::rt - hero.camLength);
}

//hero.withMapInteractions()
TEST_CASE("checking left border") {
	Hero hero(0, 100);
	hero.withMapInteractions();
	REQUIRE(hero.x == Hero::rt);
}
TEST_CASE("checking right border") {
	Hero hero(Hero::mapWidth * Hero::rt, 100);
	hero.withMapInteractions();
	REQUIRE(hero.x == (Hero::mapHeight - 1) * Hero::rt - hero.w);
}
TEST_CASE("checking bottom border") {
	Hero hero(100, Hero::mapHeight * Hero::rt);
	hero.withMapInteractions();
	REQUIRE(hero.y == (Hero::mapHeight - 1) * Hero::rt - hero.h);
}
TEST_CASE("checking upper border") {
	Hero hero(100, 0);
	hero.withMapInteractions();
	REQUIRE(hero.y == Hero::rt);
}

//hero.WithEnemyCollisions(Enemy enemy, float time)
TEST_CASE("checking collision") {
	Hero hero(100, 100);
	Enemy enemy(100, 100);
	float time = 2;
	hero.timeAfterCollision = 11;
	hero.withEnemyCollisions(enemy, time);
	REQUIRE(hero.hp == 80);
	REQUIRE(hero.timeAfterCollision == 2 * float(0.005));
	hero.hp = 20;
	hero.timeAfterCollision = 11;
	hero.withEnemyCollisions(enemy, time);
	REQUIRE(hero.hp == 0);
	REQUIRE(hero.alive == false);
}

//hero.movement(float time) and hero.checkDxDy()
TEST_CASE("testing movement down") {
	Hero hero(100, 100);
	float time = 2;
	hero.direction = 0;
	hero.speed = 0.1f;
	hero.checkDxDy();
	float prevX = hero.x;
	float prevY = hero.y;
	REQUIRE(hero.dx == 0);
	REQUIRE(hero.dy == float(0.1));
	hero.movement(time);
	REQUIRE(hero.x == prevX);
	REQUIRE(hero.y > prevY);
}
TEST_CASE("testing movement up") {
	Hero hero(100, 100);
	float time = 2;
	hero.direction = 3;
	hero.speed = 0.1f;
	hero.checkDxDy();
	float prevX = hero.x;
	float prevY = hero.y;
	REQUIRE(hero.dx == 0);
	REQUIRE(hero.dy == float(-0.1));
	hero.movement(time);
	REQUIRE(hero.x == prevX);
	REQUIRE(hero.y < prevY);
}
TEST_CASE("testing movement left") {
	Hero hero(100, 100);
	float time = 2;
	hero.direction = 1;
	hero.speed = float(0.1);
	hero.checkDxDy();
	float prevX = hero.x;
	float prevY = hero.y;
	REQUIRE(hero.dx == float(-0.1));
	REQUIRE(hero.dy == float(0));
	hero.movement(time);
	REQUIRE(hero.x < prevX);
	REQUIRE(hero.y == prevY);
}
TEST_CASE("testing movement left") {
	Hero hero(100, 100);
	float time = 2;
	hero.direction = 2;
	hero.speed = 0.1f;
	hero.checkDxDy();
	float prevX = hero.x;
	float prevY = hero.y;
	REQUIRE(hero.dx == float(0.1));
	REQUIRE(hero.dy == float(0));
	hero.movement(time);
	REQUIRE(hero.x > prevX);
	REQUIRE(hero.y == prevY);
}

//enemy
//enemy.WithMapInteractions()
TEST_CASE("checking left border") {
	Enemy enemy(0, 100);
	enemy.withMapInteractions();
	REQUIRE(enemy.x == Enemy::rt);
}
TEST_CASE("checking right border") {
	Enemy enemy(Enemy::mapWidth * Enemy::rt, 100);
	enemy.withMapInteractions();
	REQUIRE(enemy.x == (Enemy::mapWidth - 1) * Enemy::rt - enemy.w);
}
TEST_CASE("checking bottom border") {
	Enemy enemy(100, Enemy::mapHeight * Enemy::rt);
	enemy.withMapInteractions();
	REQUIRE(enemy.y == (Enemy::mapHeight - 1) * Enemy::rt - enemy.h);
}
TEST_CASE("checking upper border") {
	Enemy enemy(100, 0);
	enemy.withMapInteractions();
	REQUIRE(enemy.y == Enemy::rt);
}

