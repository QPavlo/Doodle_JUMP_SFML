#ifndef SFML_TEST_MOVABLE_PLATFORM_HPP
#define SFML_TEST_MOVABLE_PLATFORM_HPP

#include "StaticPlatform.hpp"
#include <SFML/Graphics.hpp>

class MovablePlatform : public StaticPlatform {

public:
    MovablePlatform() = default;

    [[nodiscard]] float getSpeed() const {
        return movablePlatformSpeed;
    }

    void setSpeed(float speed) {
        this->movablePlatformSpeed = speed;
    }

private:
    float movablePlatformSpeed{0};
};

#endif //SFML_TEST_MOVABLE_PLATFORM_HPP
