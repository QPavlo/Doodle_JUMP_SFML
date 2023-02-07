#ifndef SFML_TEST_MOVABLE_PLATFORM_HPP
#define SFML_TEST_MOVABLE_PLATFORM_HPP

#include "StaticPlatform.hpp"
#include <SFML/Graphics.hpp>

class MovablePlatform : public StaticPlatform {

public:
    MovablePlatform();

    [[nodiscard]] float getSpeed() const;

    void setSpeed(float speed);

private:
    float movablePlatformSpeed{0};
};

#endif //SFML_TEST_MOVABLE_PLATFORM_HPP
