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

        for (auto &plat: platforms) {
            plat.setX(distribution_x(mt));
            plat.setY(this->distribution_y(mt));
        }
    }

    void changePlatformPosition(float height, float doodleDy) {
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

    virtual void changePlatformsAmount(float height, float doodleDy, uint32_t score) {
        std::for_each_n(platforms.begin(), actualPlatformAmount,
                        [&, i = 0](auto &plat) mutable {
                            if (plat.getY() > height) {
                                if (actualPlatformAmount >= 7
                                    and i == actualPlatformAmount - 1
                                    and score > 800 * (platforms.size() - actualPlatformAmount + 1)
                                        ) {
                                    std::cout << "less pl\n";
                                    actualPlatformAmount -= 1;
                                } else {
                                    plat.setY(0);
                                    plat.setX(distribution_x(mt));
                                }
                            } else {
                                plat.changeY(doodleDy);
                            }
                            i += 1;
                        });
    }

    [[nodiscard]] constexpr std::array<T, count> &getPlatform() const {
        return platforms;
    }

    [[nodiscard]] std::array<T, count> &getPlatform() {
        return platforms;
    }

protected:
    sf::Texture platformTexture;
    sf::Sprite platformSprite;
    std::array<T, count> platforms{};
    int32_t actualPlatformAmount{count};
    std::uniform_real_distribution<float> &distribution_x;
    std::uniform_real_distribution<float> &distribution_y;
    std::mt19937 &mt;
};


template<size_t count>
class StaticPlatforms : public Platforms<StaticPlatform, count> {
public:
    void changePlatformsAmount(float height, float doodleDy, uint32_t score) {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                        [&, i = 0](auto &plat) mutable {
                            if (plat.getY() > height) {
                                if (this->actualPlatformAmount >= 7
                                    and i == this->actualPlatformAmount - 1
                                    and score > 800 * (this->platforms.size() - this->actualPlatformAmount + 1)
                                        ) {
                                    std::cout << "less pl\n";
                                    this->actualPlatformAmount -= 1;
                                } else {
                                    plat.setY(0);
                                    plat.setX(distribution_x(this->mt));
                                }
                            } else {
                                plat.changeY(doodleDy);
                            }
                            i += 1;
                        });
    }


};

template<size_t count>
class MovablePlatforms : public Platforms<MovablePlatform, count> {
public:
    void changePlatformsAmount(float height, float doodleDy, uint32_t score) {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                        [&, i = 0](auto &plat) mutable {
                            if (plat.getY() > height) {
                                if (this->actualPlatformAmount >= 7
                                    and i == this->actualPlatformAmount - 1
                                    and score > 800 * (this->platforms.size() - this->actualPlatformAmount + 1)
                                        ) {
                                    std::cout << "less pl\n";
                                    this->actualPlatformAmount -= 1;
                                } else {
                                    plat.setY(0);
                                    plat.setX(distribution_x(this->mt));
                                }
                            } else {
                                plat.changeY(doodleDy);
                            }
                            i += 1;
                        });
    }


protected:
    float speedDx{0};
};

#endif //SFML_DOODLE_JUMP_PLATFORMS_HPP
