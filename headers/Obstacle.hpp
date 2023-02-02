#ifndef SFML_TEST_OBSTACLE_HPP
#define SFML_TEST_OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    explicit Obstacle(std::string_view textureFilename) {
        obstacleTexture.loadFromFile(textureFilename.data());
        obstacleSprite.setTexture(obstacleTexture);
    }

    void setPosition(sf::Vector2f newPosition) {
        this->obstaclePosition = newPosition;
    }

    void setX(float x) {
        this->obstaclePosition.x = x;
    }

    void setY(float y) {
        this->obstaclePosition.y = y;
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
        return static_cast<sf::Vector2f>(obstacleTexture.getSize());
    }

    [[nodiscard]] const sf::Sprite &getSprite() const {
        return obstacleSprite;
    }

    [[nodiscard]] sf::Sprite &getSprite() {
        return obstacleSprite;
    }

private:
    sf::Texture obstacleTexture{};
    sf::Sprite obstacleSprite{};
    sf::Vector2f obstaclePosition{};
};


#endif //SFML_TEST_OBSTACLE_HPP
