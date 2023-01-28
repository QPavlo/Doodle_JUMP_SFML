#ifndef SFML_TEST_DOODLE_HPP
#define SFML_TEST_DOODLE_HPP

#include <SFML/Graphics.hpp>

class Doodle {
public:
    explicit Doodle(sf::Vector2f size) : doodleSize{size} {}

    void setCoordinates(sf::Vector2f coordinates) {
        this->doodleCoordinates = coordinates;
    }

    void setSpeed(float speed) {
        this->doodleSpeed = speed;
    }

    void setSize(sf::Vector2f size) {
        this->doodleSize = size;
    }

    void setX(float x) {
        doodleCoordinates.x = x;
    }

    void setY(float y) {
        doodleCoordinates.y = y;
    }

    void changeX(float dx) {
        doodleCoordinates.x += dx;
    }

    void changeY(float dy) {
        doodleCoordinates.y += dy;
    }

    [[nodiscard]] float getX() const {
        return doodleCoordinates.x;
    }

    [[nodiscard]] float getY() const {
        return doodleCoordinates.y;
    }


    [[nodiscard]] sf::Vector2f getCoordinates() const {
        return doodleCoordinates;
    }

    [[nodiscard]] sf::Vector2f getSize() const {
        return doodleSize;
    }

    [[nodiscard]] float getSpeed() const {
        return doodleSpeed;
    }

private:
    sf::Vector2f doodleCoordinates{};
    sf::Vector2f doodleSize{};
    float doodleSpeed{};
    float doodleDY{};
};

#endif //SFML_TEST_DOODLE_HPP
