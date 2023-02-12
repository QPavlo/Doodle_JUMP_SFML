#ifndef SFML_TEST_OBSTACLE_HPP
#define SFML_TEST_OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include "Doodle.hpp"

void lose_game_window(sf::RenderWindow &window);

class Obstacle {
public:
    enum ObstacleCollisionType : uint32_t {
        NO_COLLISION = 0,
        COLLISION_FROM_BOTTOM = 1,
        COLLISION_FROM_TOP = 2
    };

    Obstacle(std::string_view textureFilename, float randomStartX, std::mt19937 &mt);

    void setPosition(sf::Vector2f newPosition);

    void setX(float x);

    void setY(float y);

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] sf::Vector2f getSize() const;

    [[nodiscard]] const sf::Sprite &getSprite() const;

    [[nodiscard]] sf::Sprite &getSprite();

    void spawnObstacle(float randNewX, float randNewY);

    void drawObstacle(sf::RenderWindow &window);

    [[nodiscard]]ObstacleCollisionType collisionDetected(const Doodle &doodle) const;

    void changeObstaclePosition(float height, float doodleDy, float newRandomX);

    void collisionDetected(const sf::Sprite &bullet);

    void checkDoodleCollision(Doodle &doodle, sf::RenderWindow &window);

private:
    bool obstacleVisibility{false};
    uint8_t hp{3};
    std::uniform_int_distribution<uint16_t> chanceToAppear{0, UINT16_MAX};
    std::mt19937 &mt;
    sf::Texture obstacleTexture{};
    sf::Sprite obstacleSprite{};
};


#endif //SFML_TEST_OBSTACLE_HPP
