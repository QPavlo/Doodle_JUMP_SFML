#ifndef SFML_TEST_Base_PLATFORM_HPP
#define SFML_TEST_Base_PLATFORM_HPP

#include <SFML/Graphics.hpp>

class BasePlatform {

public:
    BasePlatform() = default;

    [[nodiscard]] sf::Vector2f getCoordinates() const {
        return movablePlatformCoordinates;
    }

    [[nodiscard]] static sf::Vector2f getSize() {
        return movablePlatformSize;
    }

    [[nodiscard]] float getX() const {
        return movablePlatformCoordinates.x;
    }

    [[nodiscard]] float getY() const {
        return movablePlatformCoordinates.y;
    }

    void setCoordinates(sf::Vector2f coordinates) {
        this->movablePlatformCoordinates = coordinates;
    }

    void setCoordinates(float x, float y) {
        this->movablePlatformCoordinates = {x, y};
    }

    void setX(float x) {
        this->movablePlatformCoordinates.x = x;
    }

    void changeX(float dx) {
        this->movablePlatformCoordinates.x += dx;
    }

    void changeY(float dy) {
        this->movablePlatformCoordinates.y += dy;
    }

    void setY(float y) {
        this->movablePlatformCoordinates.y = y;
    }

    static void setSize(sf::Vector2f size) {
        BasePlatform::movablePlatformSize = size;
    }

private:
    sf::Vector2f movablePlatformCoordinates{};
    static sf::Vector2f movablePlatformSize;
};

sf::Vector2f BasePlatform::movablePlatformSize{};

#endif
