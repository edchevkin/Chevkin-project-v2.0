#include "doctest.h"
#include "hero.h"
#include "enemy.h"
#include "map.h"


TEST_CASE("1") {
	REQUIRE(1 == 1);
}
////!hero
////hero.viewCentersOnHero()
//TEST_CASE("cameraCheck"){
//	Hero hero(100, 100);
//	hero.x = 32; hero.y = 32;
//	hero.viewCentersOnHero();
//	REQUIRE(hero.cameraX == hero.camLength);
//	REQUIRE(hero.cameraY == hero.camLength);
//}
//
////hero.heroWithMapInteractions()
//TEST_CASE("checking left border") {
//	Hero hero(0, 100);
//	hero.WithMapInteractions();
//	REQUIRE(hero.x == rt);
//}
//TEST_CASE("checking right border") {
//	Hero hero(mapWidth * rt, 100);
//	hero.WithMapInteractions();
//	REQUIRE(hero.x == (mapWidth - 1) * rt - hero.w);
//}
//TEST_CASE("checking bottom border") {
//	Hero hero(100, mapHeight * rt);
//	hero.WithMapInteractions();
//	REQUIRE(hero.y == (mapHeight - 1) * rt - hero.h);
//}
//TEST_CASE("checking upper border") {
//	Hero hero(100, 0);
//	hero.WithMapInteractions();
//	REQUIRE(hero.y == rt);
//}
//
////hero.WithEnemyCollision(Enemy enemy, float time)
//TEST_CASE("checking collision") {
//	Hero hero(100, 100);
//	Enemy enemy(100, 100);
//	float time = 2;
//	hero.timeAfterCollision = 11;
//	hero.heroWithEnemyCollision(enemy, time);
//	REQUIRE(hero.hp == 80);
//	REQUIRE(hero.timeAfterCollision == 2 * 0.005f);
//	hero.hp = 20;
//	hero.timeAfterCollision = 11;
//	hero.heroWithEnemyCollision(enemy, time);
//	REQUIRE(hero.hp == 0);
//	REQUIRE(hero.alive == false);
//}
//
////hero.movement(float time) and hero.checkDxDy()
//TEST_CASE("testing movement down") {
//	Hero hero(100, 100);
//	float time = 2;
//	hero.direction = 0;
//	hero.speed = 0.1;
//	hero.checkDxDy();
//	float prevX = hero.x;
//	float prevY = hero.y;
//	REQUIRE(hero.dx == 0);
//	REQUIRE(hero.dy == 0.1f);
//	hero.movement(time);
//	REQUIRE(hero.x == prevX);
//	REQUIRE(hero.y > prevY);
//}
//TEST_CASE("testing movement up") {
//	Hero hero(100, 100);
//	float time = 2;
//	hero.direction = 3;
//	hero.speed = 0.1;
//	hero.checkDxDy();
//	float prevX = hero.x;
//	float prevY = hero.y;
//	REQUIRE(hero.dx == 0);
//	REQUIRE(hero.dy == -0.1f);
//	hero.movement(time);
//	REQUIRE(hero.x == prevX);
//	REQUIRE(hero.y < prevY);
//}
//TEST_CASE("testing movement left") {
//	Hero hero(100, 100);
//	float time = 2;
//	hero.direction = 1;
//	hero.speed = 0.1;
//	hero.checkDxDy();
//	float prevX = hero.x;
//	float prevY = hero.y;
//	REQUIRE(hero.dx == -0.1f);
//	REQUIRE(hero.dy == 0.0f);
//	hero.movement(time);
//	REQUIRE(hero.x < prevX);
//	REQUIRE(hero.y == prevY);
//}
//TEST_CASE("testing movement left") {
//	Hero hero(100, 100);
//	float time = 2;
//	hero.direction = 2;
//	hero.speed = 0.1;
//	hero.checkDxDy();
//	float prevX = hero.x;
//	float prevY = hero.y;
//	REQUIRE(hero.dx == 0.1f);
//	REQUIRE(hero.dy == 0.0f);
//	hero.movement(time);
//	REQUIRE(hero.x > prevX);
//	REQUIRE(hero.y == prevY);
//}
//
////enemy
////enemy.WithMapInteractions()
//TEST_CASE("checking left border") {
//	Enemy enemy(0, 100);
//	enemy.WithMapInteractions();
//	REQUIRE(enemy.x == rt);
//}
//TEST_CASE("checking right border") {
//	Enemy enemy(mapWidth * rt, 100);
//	enemy.WithMapInteractions();
//	REQUIRE(enemy.x == (mapWidth - 1) * rt - enemy.w);
//}
//TEST_CASE("checking bottom border") {
//	Enemy enemy(100, mapHeight * rt);
//	enemy.WithMapInteractions();
//	REQUIRE(enemy.y == (mapHeight - 1) * rt - enemy.h);
//}
//TEST_CASE("checking upper border") {
//	Enemy enemy(100, 0);
//	enemy.WithMapInteractions();
//	REQUIRE(enemy.y == rt);
//}
//
