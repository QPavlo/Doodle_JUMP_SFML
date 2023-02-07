#include "../headers/Doodle.hpp"
#include <iostream>

Doodle::Doodle(std::string_view textureFilename) {
    this->doodleTexture.loadFromFile(textureFilename.data());
    this->doodleSprite.setTexture(doodleTexture);
}

void Doodle::setPosition(sf::Vector2f newPosition) {
    doodleSprite.setPosition(newPosition);
}

void Doodle::setSpeed(float speed) {
    this->doodleSpeed = speed;
}

void Doodle::setX(float x) {
    doodleSprite.setPosition(x, doodleSprite.getPosition().y);
}

void Doodle::setDy(float accelerationY) {
    this->doodleY_Acceleration = accelerationY;
}

void Doodle::setY(float y) {
    doodleSprite.setPosition(doodleSprite.getPosition().x, y);
}

void Doodle::changeX(float dx) {
    doodleSprite.setPosition(doodleSprite.getPosition().x + dx, doodleSprite.getPosition().y);
}

void Doodle::changeY(float dy) {
    doodleSprite.setPosition(doodleSprite.getPosition().x, doodleSprite.getPosition().y + dy);
}

void Doodle::changeDy(float d_accelerationY) {
    doodleY_Acceleration += d_accelerationY;
}

[[nodiscard]] float Doodle::getX() const {
    return doodleSprite.getPosition().x;
}

[[nodiscard]] float Doodle::getY() const {
    return doodleSprite.getPosition().y;
}

[[nodiscard]] float Doodle::getDy() const {
    return doodleY_Acceleration;
}

[[nodiscard]] sf::Vector2f Doodle::getPosition() const {
    return doodleSprite.getPosition();
}

[[nodiscard]] sf::Vector2f Doodle::getSize() const {
    return static_cast<sf::Vector2f>(doodleTexture.getSize());
}

[[nodiscard]] float Doodle::getSpeed() const {
    return doodleSpeed;
}

[[nodiscard]] const sf::Texture &Doodle::getTexture() const {
    return doodleTexture;
}

[[nodiscard]] sf::Texture &Doodle::getTexture() {
    return doodleTexture;
}

[[nodiscard]] sf::Sprite &Doodle::getSprite() {
    return doodleSprite;
}

[[nodiscard]] const sf::Sprite &Doodle::getSprite() const {
    return doodleSprite;
}

void Doodle::drawDoodle(sf::RenderWindow &window) {
        window.draw(doodleSprite);
}