#include "../headers/StaticPlatform.hpp"

StaticPlatform::StaticPlatform() = default;

[[nodiscard]] sf::Vector2f StaticPlatform::getPosition() const {
    return platformPosition;
}

[[nodiscard]] sf::Vector2f StaticPlatform::getSize() {
    return StaticPlatform::platformSize;
}

[[nodiscard]] float StaticPlatform::getX() const {
    return platformPosition.x;
}

[[nodiscard]] float StaticPlatform::getY() const {
    return platformPosition.y;
}

void StaticPlatform::setPosition(sf::Vector2f coordinates) {
    this->platformPosition = coordinates;
}

void StaticPlatform::setCoordinates(float x, float y) {
    this->platformPosition = {x, y};
}

void StaticPlatform::setX(float x) {
    this->platformPosition.x = x;
}

void StaticPlatform::changeX(float dx) {
    this->platformPosition.x += dx;
}

void StaticPlatform::changeY(float dy) {
    this->platformPosition.y += dy;
}

void StaticPlatform::setY(float y) {
    this->platformPosition.y = y;
}

[[maybe_unused]] void StaticPlatform::setSize(sf::Vector2f size) {
    StaticPlatform::platformSize = size;
}

sf::Vector2f StaticPlatform::platformSize{};