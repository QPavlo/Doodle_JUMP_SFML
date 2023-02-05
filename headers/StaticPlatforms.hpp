#ifndef SFML_DOODLE_JUMP_STATIC_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_STATIC_PLATFORMS_HPP

#include "Platforms.hpp"
#include <iostream>

template<size_t count>
class StaticPlatforms : public Platforms<StaticPlatform, count> {
public:

    StaticPlatforms(std::string_view textureFilename,
                    std::uniform_real_distribution<float> &distribution_x,
                    std::uniform_real_distribution<float> &distribution_y,
                    std::mt19937 &mt) :
            Platforms<StaticPlatform, count>(textureFilename,
                                             distribution_x,
                                             distribution_y,
                                             mt) {
        this->actualPlatformAmount = count;

        for (auto &plat: this->platforms) {
            plat.setX(distribution_x(mt));
            plat.setY(distribution_y(mt));
        }

    }

    void changePlatformsAmount(float windowHeight, uint32_t score) override {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                        [&](auto &plat) {
                            if (plat.getY() > windowHeight) {
                                if (this->actualPlatformAmount >= 5 and
                                    &(plat) == &(this->platforms[this->actualPlatformAmount - 1]) and
                                    score > 800 * (this->platforms.size() - this->actualPlatformAmount + 1)
                                        ) {
                                    this->actualPlatformAmount -= 1;
                                }
                            }
                        });
    }
};

#endif
