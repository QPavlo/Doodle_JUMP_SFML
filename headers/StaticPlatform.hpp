#ifndef SFML_TEST_STATIC_PLATFORM_H
#define SFML_TEST_STATIC_PLATFORM_H

#include "Doodle.hpp"
#include <SFML/Graphics.hpp>

class StaticPlatform {
public:
    StaticPlatform();

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] static sf::Vector2f getSize();

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    void setPosition(sf::Vector2f coordinates);

    void setCoordinates(float x, float y);

    void setX(float x);

    void changeX(float dx);

    void changeY(float dy);

    void setY(float y);

    [[nodiscard]] bool collisionDetected(const Doodle &doodle) const;

    static void setSize(sf::Vector2f size);

protected:
    sf::Vector2f platformPosition{};
    static sf::Vector2f platformSize;

};

#endif //SFML_TEST_STATIC_PLATFORM_H
