#ifndef SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP

#include "Platforms.hpp"
#include <iostream>

template<size_t count>
class MovablePlatforms : public Platforms<MovablePlatform, count> {
public:

    MovablePlatforms(std::string_view textureFilename,
                     std::uniform_real_distribution<float> &distribution_x,
                     std::uniform_real_distribution<float> &distribution_y,
                     std::mt19937 &mt,
                     float speedDx) : Platforms<MovablePlatform, count>(textureFilename,
                                                                        distribution_x,
                                                                        distribution_y,
                                                                        mt) , speedDx{speedDx} {

        this->actualPlatformAmount = 2;

        for (auto &plat: this->platforms) {
            plat.setX(distribution_x(mt));
            plat.setY(-distribution_y(mt));
        }

        for (auto &m_plat: this->platforms) {
            m_plat.setSpeed(speedDx);
        }
    }

    void changePlatformsAmount(float height, uint32_t score) {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                        [&](auto &plat) {
                            if (plat.getY() > height) {
                                if (this->actualPlatformAmount < count and
                                    score > 800 * (this->actualPlatformAmount + 1)
                                        ) {
                                    std::cout << "incr pl\n";
                                    this->actualPlatformAmount += 1;
                                }
                            }
                        });
    }

    void changePlatformsPositionX(float windowWidth) {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount, [&](auto &plat) {
            std::cout << plat.getSpeed() << '\n';
            plat.changeX(plat.getSpeed());
            if (plat.getX() > windowWidth - MovablePlatform::getSize().x) {
                plat.setSpeed(-(this->speedDx));
            } else if (plat.getX() < 0) {
                plat.setSpeed(this->speedDx);
            }
//            this->platformSprite.setPosition(plat.getX(), plat.getY());
//
//            window.draw(this->platformSprite);
        });
    }

    [[nodiscard]] float getDx() const {
        return speedDx;
    }

    void setDx(float newSpeedDx) {
        this->speedDx = newSpeedDx;
    }

    void changeDx(float dxSpeedDx) {
        this->speedDx += dxSpeedDx;
    }


protected:
    float speedDx{0};
};

#endif
