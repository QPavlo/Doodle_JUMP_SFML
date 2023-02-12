#include <iostream>
#include "../headers/Obstacle.hpp"

Obstacle::Obstacle(std::string_view textureFilename, float randomStartX, std::mt19937 &mt)
        : mt{mt} {
    obstacleTexture.loadFromFile(textureFilename.data());
    obstacleSprite.setTexture(obstacleTexture);
    obstacleSprite.setPosition(randomStartX, -100);
}

void Obstacle::setPosition(sf::Vector2f newPosition) {
    this->obstacleSprite.setPosition(newPosition);
}

void Obstacle::setX(float x) {
    this->obstacleSprite.setPosition(x, obstacleSprite.getPosition().y);
}

void Obstacle::setY(float y) {
    this->obstacleSprite.setPosition(obstacleSprite.getPosition().x, y);
}

[[nodiscard]] sf::Vector2f Obstacle::getPosition() const {
    return obstacleSprite.getPosition();
}

[[nodiscard]] float Obstacle::getX() const {
    return obstacleSprite.getPosition().x;
}

[[nodiscard]] float Obstacle::getY() const {
    return obstacleSprite.getPosition().y;
}

[[nodiscard]] sf::Vector2f Obstacle::getSize() const {
    return static_cast<sf::Vector2f>(obstacleTexture.getSize());
}

[[nodiscard]] const sf::Sprite &Obstacle::getSprite() const {
    return obstacleSprite;
}

[[nodiscard]] sf::Sprite &Obstacle::getSprite() {
    return obstacleSprite;
}

void Obstacle::spawnObstacle(float randNewX, float randNewY) {
    uint16_t temp_rand = chanceToAppear(mt);
    if (temp_rand <= 999 and !obstacleVisibility) {
        setPosition({randNewX, -(getSize().y) - randNewY});
        obstacleVisibility = true;
    }
}

void Obstacle::drawObstacle(sf::RenderWindow &window) {
    if (obstacleVisibility) {
        window.draw(obstacleSprite);
    }
}

[[nodiscard]]Obstacle::ObstacleCollisionType Obstacle::collisionDetected(const Doodle &doodle) const {
    if (((doodle.getX() + (doodle.getSize().x / 1.5f) > this->getX()) and
         (doodle.getX() + (doodle.getSize().x / 3.0f) < this->getX() + this->getSize().x) and
         (doodle.getY() + doodle.getSize().y > this->getY()) and
         (doodle.getY() + doodle.getSize().y < this->getY() + 0.15f * this->getSize().y))) {
        return ObstacleCollisionType::COLLISION_FROM_TOP;
    }

    if ((doodle.getX() + (doodle.getSize().x / 1.5f) > this->getX()) and
        (doodle.getX() + (doodle.getSize().x / 3.0f) < this->getX() + this->getSize().x) and
        (doodle.getY() + doodle.getSize().y - 45 > this->getY()) and
        (doodle.getY() < this->getY() + this->getSize().y - 45)) {
        return ObstacleCollisionType::COLLISION_FROM_BOTTOM;
    }
    return ObstacleCollisionType::NO_COLLISION;
}

void Obstacle::collisionDetected(const sf::Sprite &bullet) {
    if (bullet.getGlobalBounds().intersects(this->obstacleSprite.getGlobalBounds())) {
        this->obstacleVisibility = false;
    }
}

void Obstacle::changeObstaclePosition(float height, float doodleDy, float newRandomX) {
    if (obstacleVisibility) {
        if (this->getY() > height) {
            this->setX(newRandomX);
            this->setY(-(this->getSize().y));
        } else {
            this->setY(this->getY() - doodleDy);
        }

        if (this->getY() > height) {
            obstacleVisibility = false;
        }
    }
}

void Obstacle::checkDoodleCollision(Doodle &doodle, sf::RenderWindow &window) {
    if (obstacleVisibility) {
        auto collisionStatus = collisionDetected(doodle);
        if (collisionStatus == ObstacleCollisionType::COLLISION_FROM_BOTTOM) {
            lose_game_window(window);
        } else if (collisionStatus == ObstacleCollisionType::COLLISION_FROM_TOP) {
            doodle.setDy(-10);
            obstacleVisibility = false;
        }
    }
}