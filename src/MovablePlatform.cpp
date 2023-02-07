#include "../headers/MovablePlatform.hpp"

MovablePlatform::MovablePlatform() = default;

float MovablePlatform::getSpeed() const {
    return movablePlatformSpeed;
}

void MovablePlatform::setSpeed(float speed) {
    this->movablePlatformSpeed = speed;
}