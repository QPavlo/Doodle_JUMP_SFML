#ifndef SFML_TEST_DOODLE_HPP
#define SFML_TEST_DOODLE_HPP

#include <SFML/Graphics.hpp>

class Doodle {
public:
    explicit Doodle(std::string_view textureFilename);

    void setPosition(sf::Vector2f newPosition);

    void applyCurrentPosition();

    void setSpeed(float speed);

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

    [[nodiscard]] const sf::Texture &getTexture() const;

    [[nodiscard]] sf::Texture &getTexture();

    [[nodiscard]] sf::Sprite &getSprite();

    [[nodiscard]] const sf::Sprite &getSprite() const;

    [[nodiscard]] float getSpeed() const;

private:
    sf::Vector2f doodlePosition{};
    sf::Texture doodleTexture{};
    sf::Sprite doodleSprite{};
    float doodleSpeed{0};
    float doodleY_Acceleration{0};
};

#endif //SFML_TEST_DOODLE_HPP
