#ifndef SFML_DOODLE_JUMP_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_PLATFORMS_HPP

#include "StaticPlatform.hpp"
#include "MovablePlatform.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <random>

template<typename T, size_t count>
class Platforms {
public:
    static_assert(std::is_base_of<StaticPlatform, T>::value, "T::value_type is not derived from BasePlatform");

    Platforms(std::string_view textureFilename,
              std::uniform_real_distribution<float> &distribution_x,
              std::uniform_real_distribution<float> &distribution_y,
              std::mt19937 &mt) : distribution_x{distribution_x}, distribution_y{distribution_y}, mt{mt} {
        this->platformTexture.loadFromFile(textureFilename.data());
        this->platformSprite.setTexture(platformTexture);

    }

    void changePlatformPosition(float height, float doodleDy) {
        std::for_each_n(platforms.begin(), actualPlatformAmount,
                        [&](auto &plat) mutable {
                            if (plat.getY() > height) {
                                plat.setY(0);
                                plat.setX(distribution_x(mt));
                            } else {
                                plat.changeY(-doodleDy);
                            }
                        });

    }

    virtual void changePlatformsAmount(float height, uint32_t score) = 0;

    void checkDoodleCollision(Doodle &doodle) {
        std::for_each_n(platforms.begin(), actualPlatformAmount, [&](const auto &plat) {
            if (plat.collisionDetected(doodle)) {
                if (doodle.getDy() > 0) {
                    doodle.setDy(-10);
                }
            }
        });
    }

    void drawPlatforms(sf::RenderWindow &window) {
        std::for_each_n(platforms.begin(), actualPlatformAmount, [&](auto &plat) {
            platformSprite.setPosition(plat.getX(), plat.getY());
            window.draw(platformSprite);
        });
    }

    [[nodiscard]] constexpr std::array<T, count> &getPlatforms() const {
        return platforms;
    }

    [[nodiscard]] std::array<T, count> &getPlatforms() {
        return platforms;
    }

protected:
    sf::Texture platformTexture;
    sf::Sprite platformSprite;
    std::array<T, count> platforms{};
    int32_t actualPlatformAmount{0};
    std::uniform_real_distribution<float> &distribution_x;
    std::uniform_real_distribution<float> &distribution_y;
    std::mt19937 &mt;
};

#endif //SFML_DOODLE_JUMP_PLATFORMS_HPP
