#include "hero.h"

Hero::Hero(float X, float Y) {
    hitbox.setSize(Vector2f(float(w), float(h)));
    hitbox.setPosition(x, y);
    image.loadFromFile("images/hero.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
    x = X; y = Y;
    view.reset(FloatRect(x, y, camLength * 2, camLength * 2));
    dx = 0; dy = 0;
}

void Hero::movement(float time) {
    y += dy * time;
    x += dx * time;
    speed = 0;
    hitbox.setPosition(x, y);
    sprite.setPosition(hitbox.getPosition());
}

void Hero::checkDxDy() {
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
    else if (direction == 4) {
        dx = 0; dy = 0;
    }
}

void Hero::keyboard() {
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        direction = 0;
        speed = float(0.1);
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction = 1;
        speed = float(0.1);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction = 2;
        speed = float(0.1);
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        direction = 3;
        speed = float(0.1);
    }
    if ((!(Keyboard::isKeyPressed(Keyboard::S)) &&
        !(Keyboard::isKeyPressed(Keyboard::A)) &&
        !(Keyboard::isKeyPressed(Keyboard::W)) &&
        !(Keyboard::isKeyPressed(Keyboard::D)))) {
        direction = 4;
    }
}

void Hero::animation(float time) {
    if (dx == 0 && dy == 0) {
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    if (direction == 0) {
        animCounter += float(0.005) * time;
        if (animCounter > 4) animCounter -= 4;
        sprite.setTextureRect(IntRect(w * int(animCounter), 0, w, h));
    }
    if (direction == 1) {
        animCounter += float(0.005) * time;
        if (animCounter > 4) animCounter -= 4;
        sprite.setTextureRect(IntRect(w * int(animCounter), h, w, h));
    }
    if (direction == 2) {
        animCounter += float(0.005) * time;
        if (animCounter > 4) animCounter -= 4;
        sprite.setTextureRect(IntRect(w * int(animCounter), 2 * h, w, h));
    }
    if (direction == 3) {
        animCounter += float(0.005) * time;
        if (animCounter > 4) animCounter -= 4;
        sprite.setTextureRect(IntRect(w * int(animCounter), 3 * h, w, h));
    }
}

View Hero::viewCentring() {
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

void Hero::withMapInteractions() {
    if (x < rt)
        x = rt;
    if (x > (mapWidth - 1) * rt - w)
        x = (mapWidth - 1) * float(rt) - w;
    if (y < rt)
        y = rt;
    if (y > (mapHeight - 1) * rt - h)
        y = (mapHeight - 1) * float(rt) - h;
}

void Hero::withEnemyCollisions(Enemy enemy, float time) {
    float tw = float(w); float th = float(h);
    if (timeAfterCollision > 10) {
        if (FloatRect(x + tw / 4, y + th / 4, tw / 2, th / 2).intersects
        (FloatRect(enemy.x, enemy.y, float(enemy.w), float(enemy.h)))) {
            hp -= enemy.damage;
            timeAfterCollision = 0;
        }
    }
    if (hp <= 0)
        alive = false;

    timeAfterCollision += float(0.005) * time;
}

void Hero::update(float time) {
    Hero::keyboard();
    Hero::checkDxDy();
    Hero::withMapInteractions();
    Hero::animation(time);
    Hero::movement(time);
    Hero::viewCentring();
}
