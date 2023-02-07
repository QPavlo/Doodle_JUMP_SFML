#include "../headers/MovablePlatforms.hpp"

template<size_t count>
MovablePlatforms<count>::MovablePlatforms(std::string_view textureFilename,
                                          std::uniform_real_distribution<float> distribution_x,
                                          std::uniform_real_distribution<float> distribution_y,
                                          std::mt19937 &mt,
                                          float speedDx): Platforms<MovablePlatform, count>(textureFilename),
                                                          speedDx{speedDx} {

    this->actualPlatformAmount = 2;

    for (auto &plat: this->platforms) {
        plat.setX(distribution_x(mt));
        plat.setY(-distribution_y(mt));
    }

    for (auto &m_plat: this->platforms) {
        m_plat.setSpeed(speedDx);
    }
}

template<size_t count>
void MovablePlatforms<count>::changePlatformsAmount(float height, uint32_t score) {
    std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                    [&](auto &plat) {
                        if (plat.getY() > height) {
                            if (this->actualPlatformAmount < count and
                                score > 800 * (this->actualPlatformAmount + 1)
                                    ) {
                                this->actualPlatformAmount += 1;
                            }
                        }
                    });
}

template<size_t count>
void MovablePlatforms<count>::changePlatformsPositionX(float windowWidth) {
    std::for_each_n(this->platforms.begin(), this->actualPlatformAmount, [&](auto &plat) {
        plat.changeX(plat.getSpeed());
        if (plat.getX() > windowWidth - MovablePlatform::getSize().x) {
            plat.setSpeed(-(this->speedDx));
        } else if (plat.getX() < 0) {
            plat.setSpeed(this->speedDx);
        }
    });
}

template<size_t count>
[[nodiscard]] float MovablePlatforms<count>::getDx() const {
    return speedDx;
}

template<size_t count>
void MovablePlatforms<count>::setDx(float newSpeedDx) {
    this->speedDx = newSpeedDx;
}

template<size_t count>
void MovablePlatforms<count>::changeDx(float dxSpeedDx) {
    this->speedDx += dxSpeedDx;
}