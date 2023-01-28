#ifndef SFML_TEST_OBSTACLE_HPP
#define SFML_TEST_OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    explicit Obstacle(sf::Vector2f size) : obstacleCoordinates{}, obstacleSize{size} {}

    void setCoordinates(sf::Vector2f coordinates) {
        this->obstacleCoordinates = coordinates;
    }

    void setSize(sf::Vector2f size) {
        this->obstacleSize = size;
    }

    [[nodiscard]] sf::Vector2f getCoordinates() const {
        return obstacleCoordinates;
    }

    [[nodiscard]] float getX() const {
        return obstacleCoordinates.x;
    }

    [[nodiscard]] float getY() const {
        return obstacleCoordinates.y;
    }

    [[nodiscard]] sf::Vector2f getSize() const {
        return obstacleSize;
    }

private:
    sf::Vector2f obstacleCoordinates{};
    sf::Vector2f obstacleSize{};
};


#endif //SFML_TEST_OBSTACLE_HPP
