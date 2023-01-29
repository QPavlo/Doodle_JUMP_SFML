#ifndef SFML_TEST_OBSTACLE_HPP
#define SFML_TEST_OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    explicit Obstacle(sf::Vector2f size) : obstaclePosition{}, obstacleSize{size} {}

    void setPosition(sf::Vector2f newPosition) {
        this->obstaclePosition = newPosition;
    }

    void setX(float x) {
        this->obstaclePosition.x = x;
    }

    void setY(float y) {
        this->obstaclePosition.y = y;
    }

    void setSize(sf::Vector2f size) {
        this->obstacleSize = size;
    }

    [[nodiscard]] sf::Vector2f getPosition() const {
        return obstaclePosition;
    }

    [[nodiscard]] float getX() const {
        return obstaclePosition.x;
    }

    [[nodiscard]] float getY() const {
        return obstaclePosition.y;
    }

    [[nodiscard]] sf::Vector2f getSize() const {
        return obstacleSize;
    }

private:
    sf::Vector2f obstaclePosition{};
    sf::Vector2f obstacleSize{};
};


#endif //SFML_TEST_OBSTACLE_HPP
