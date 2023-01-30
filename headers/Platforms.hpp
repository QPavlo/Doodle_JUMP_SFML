#ifndef SFML_DOODLE_JUMP_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_PLATFORMS_HPP

#include "BasePlatform.hpp"
#include "MovablePlatform.hpp"
#include "StaticPlatform.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <random>

template<typename T,
        size_t count>
class Platforms {
public:
    Platforms(std::string_view textureFilename,
              std::uniform_real_distribution<float> &distribution_x,
              std::uniform_real_distribution<float> &distribution_y,
              std::mt19937 &mt) : distribution_x{distribution_x}, distribution_y{distribution_y}, mt{mt} {
        this->platformTexture.loadFromFile(textureFilename.data());
        this->platformSprite.setTexture(platformTexture);
    }

    void changePlatformPosition(int32_t height, float doodleDy) {
        std::for_each_n(platforms.begin(), actualPlatformAmount,
                        [&, i = 0](auto &plat) mutable {
                            if (plat.getY() > height) {
                                plat.setY(0);
                                plat.setX(distribution_x(mt));

                            } else {
                                plat.changeY(-doodleDy);
                            }
                            i += 1;
                        });
    }

private:
    sf::Texture platformTexture;
    sf::Sprite platformSprite;
    std::array<T, count> platforms{};
    int32_t actualPlatformAmount{0};
    std::uniform_real_distribution<float> &distribution_x;
    std::uniform_real_distribution<float> &distribution_y;
    std::mt19937 &mt;
};

#endif //SFML_DOODLE_JUMP_PLATFORMS_HPP
