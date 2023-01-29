#include "../headers/Doodle.hpp"

Doodle::Doodle(sf::Vector2f size) : doodleSize{size} {}

void Doodle::setPosition(sf::Vector2f newPosition) {
    this->doodlePosition = newPosition;
}

void Doodle::setSpeed(float speed) {
    this->doodleSpeed = speed;
}

void Doodle::setSize(sf::Vector2f size) {
    this->doodleSize = size;
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
    return doodleSize;
}

[[nodiscard]] float Doodle::getSpeed() const {
    return doodleSpeed;
}
