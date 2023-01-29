#include "../headers/Doodle.hpp"

Doodle::Doodle(std::string_view texture_filename) {
    this->doodleTexture.loadFromFile(texture_filename.data());
    this->doodleSprite.setTexture(doodleTexture);
}

void Doodle::setPosition(sf::Vector2f newPosition) {
    this->doodlePosition = newPosition;
}

void Doodle::applyCurrentPosition() {
    doodleSprite.setPosition(doodlePosition);
}

void Doodle::setSpeed(float speed) {
    this->doodleSpeed = speed;
}

void Doodle::setX(float x) {
    this->doodlePosition.x = x;
}

void Doodle::setDy(float accelerationY) {
    this->doodleY_Acceleration = accelerationY;
}

void Doodle::setY(float y) {
    doodlePosition.y = y;
}

void Doodle::changeX(float dx) {
    doodlePosition.x += dx;
}

void Doodle::changeY(float dy) {
    doodlePosition.y += dy;
}

void Doodle::changeDy(float d_accelerationY) {
    doodleY_Acceleration += d_accelerationY;
}

[[nodiscard]] float Doodle::getX() const {
    return doodlePosition.x;
}

[[nodiscard]] float Doodle::getY() const {
    return doodlePosition.y;
}

[[nodiscard]] float Doodle::getDy() const {
    return doodleY_Acceleration;
}

[[nodiscard]] sf::Vector2f Doodle::getPosition() const {
    return doodlePosition;
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