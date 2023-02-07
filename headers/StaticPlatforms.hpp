#ifndef SFML_DOODLE_JUMP_STATIC_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_STATIC_PLATFORMS_HPP

#include "Platforms.hpp"
#include <iostream>

template<size_t count>
class StaticPlatforms : public Platforms<StaticPlatform, count> {
public:

    StaticPlatforms(std::string_view textureFilename,
                    std::uniform_real_distribution<float> distribution_x,
                    std::uniform_real_distribution<float> distribution_y,
                    std::mt19937 &mt);

    void changePlatformsAmount(float windowHeight, uint32_t score) override;
};

#endif
