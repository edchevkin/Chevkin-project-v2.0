#include <SFML/Graphics.hpp>
#include "hero.h"
#include "enemy.h"
#include <sstream>
#include <iostream>
#include <vector>

using namespace sf;


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "The Dungeon Master");

    //setting font for textes on screen
    Font font;
    font.loadFromFile("fonts/Alundra.ttf");

    //loading map tiles textures
    Image mapImage;
    mapImage.loadFromFile("images/map2.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    //initializing player
    Hero hero(512, 512); 

    //initializing enemies
    Enemy enemy1(0, 0);
    Enemy enemy2(512, 0);
    Enemy enemy3(0, 512);
    

    ///time
    Clock clock;
    ///temporary score
    float scoreTemp = 0;

    ///height of map
    const int mapHeight = 10;
    ///width of map
    const int mapWidth = 10;
    ///resolution of map tile
    const int rt = 32;
    String MapLayout[mapHeight] = {
    "0000000000",
    "0        0",
    "0        0",
    "0        0",
    "0        0",
    "0        0",
    "0        0",
    "0        0",
    "0        0",
    "0000000000",
    };

    //game loop
    while (window.isOpen()) {
        //time and score counters
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        time = time * 1000;
        scoreTemp += time /1000;

        //if game window closed break from the game loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
        }

        //'Escape' for dying
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            hero.alive = false;
        //'t' for exit
        if (Keyboard::isKeyPressed(Keyboard::T)) {
            window.close();
        }

        //movement of hero and enemies if hero is alive
        if (hero.alive) {
            hero.update(time);
            hero.withEnemyCollisions(enemy1, time);
            hero.withEnemyCollisions(enemy2, time);
            hero.withEnemyCollisions(enemy3, time);

            enemy1.update(time);
            enemy2.update(time);
            enemy3.update(time);
        }
        //setting the camera position
        window.setView(hero.view);

        //clearing the game window
        window.clear();

        //drawind the map
        for (int i = 0; i < mapHeight; i++)
            for (int j = 0; j < mapWidth; j++) {
                if (MapLayout[i][j] == '0')
                    mapSprite.setTextureRect(IntRect(0, 32, rt, rt));
                if (MapLayout[i][j] == ' ')
                    mapSprite.setTextureRect(IntRect(160, 0, rt, rt));
                mapSprite.setPosition(i * rt * 1.0f, j * rt * 1.0f);
                window.draw(mapSprite);
            }

        //drawing hero sprite
        window.draw(hero.sprite);

        //drawing enemy sprites
        window.draw(enemy1.sprite);
        window.draw(enemy2.sprite);
        window.draw(enemy3.sprite);

        //if GameOver
        if (!hero.alive) {
            Text gameOverText("You have lost", font, 28);
            gameOverText.setPosition(hero.cameraX - hero.camLength, hero.cameraY - hero.camLength);
            window.draw(gameOverText);

            static int score = int(scoreTemp);
            ostringstream oss;
            oss <<"Your score is " << score;
            Text pointsText(oss.str(), font, 28);
            pointsText.setPosition(hero.cameraX - hero.camLength, hero.cameraY - hero.camLength + rt);
            window.draw(pointsText);
        }

        //show HP
        else{
            ostringstream oss;
            oss << hero.hp << "/100";
            Text hpText(oss.str(), font, 20);
            hpText.setFillColor(Color::Green);
            hpText.setPosition(hero.cameraX - hero.camLength, hero.cameraY - hero.camLength);
            window.draw(hpText);
        }

        window.display();
    }
    return 0;
}