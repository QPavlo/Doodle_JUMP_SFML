#ifndef SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP

#include "Platforms.hpp"
#include <iostream>

template<size_t count>
class MovablePlatforms : public Platforms<MovablePlatform, count> {
public:

    MovablePlatforms(std::string_view textureFilename,
                     std::uniform_real_distribution<float> distribution_x,
                     std::uniform_real_distribution<float> distribution_y,
                     std::mt19937 &mt,
                     float speedDx);

    void changePlatformsAmount(float height, uint32_t score);

    void changePlatformsPositionX(float windowWidth);

    [[nodiscard]] float getDx() const;

    void setDx(float newSpeedDx);

    void changeDx(float dxSpeedDx);

protected:
    float speedDx{0};
};
//
//#include "../src/MovablePlatforms.cpp"
//#include "../src/Platforms.cpp"

#endif
