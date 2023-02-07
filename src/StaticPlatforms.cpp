#include "../headers/StaticPlatforms.hpp"

template<size_t count>
StaticPlatforms<count>::StaticPlatforms(std::string_view textureFilename,
                                        std::uniform_real_distribution<float> distribution_x,
                                        std::uniform_real_distribution<float> distribution_y,
                                        std::mt19937 &mt) :
        Platforms<StaticPlatform, count>(textureFilename) {
    this->actualPlatformAmount = count;

    for (auto &plat: this->platforms) {
        plat.setX(distribution_x(mt));
        plat.setY(distribution_y(mt));
    }
}

template<size_t count>
void StaticPlatforms<count>::changePlatformsAmount(float windowHeight, uint32_t score) {
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