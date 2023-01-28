#ifndef SFML_TEST_MOVABLE_PLATFORM_HPP
#define SFML_TEST_MOVABLE_PLATFORM_HPP

#include "BasePlatform.hpp"
#include <SFML/Graphics.hpp>

class MovablePlatform : public BasePlatform {

public:
    MovablePlatform() = default;

    [[nodiscard]] float getSpeed() const {
        return movablePlatformSpeed;
    }

    void setSpeed(float speed) {
        this->movablePlatformSpeed = speed;
    }

private:
    float movablePlatformSpeed{};
};

#endif //SFML_TEST_MOVABLE_PLATFORM_HPP
