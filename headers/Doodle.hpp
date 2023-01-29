#ifndef SFML_TEST_DOODLE_HPP
#define SFML_TEST_DOODLE_HPP

#include <SFML/Graphics.hpp>

class Doodle {
public:
    explicit Doodle(sf::Vector2f size);

    void setPosition(sf::Vector2f newPosition);

    void setSpeed(float speed);

    void setSize(sf::Vector2f size);

    void setX(float x);

    void setDy(float accelerationY);

    void setY(float y);

    void changeX(float dx);

    void changeY(float dy);

    void changeDy(float d_accelerationY);

    [[nodiscard]] float getX() const;


    [[nodiscard]] float getY() const;

    [[nodiscard]] float getDy() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] sf::Vector2f getSize() const;

    [[nodiscard]] float getSpeed() const;

private:
    sf::Vector2f doodlePosition{};
    sf::Vector2f doodleSize{};
    float doodleSpeed{0};
    float doodleY_Acceleration{0};
};

#endif //SFML_TEST_DOODLE_HPP
