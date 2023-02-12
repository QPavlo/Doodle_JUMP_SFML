#include "../headers/Platforms.hpp"

template<typename T, size_t count>
Platforms<T, count>::Platforms(std::string_view textureFilename) {
    this->platformTexture.loadFromFile(textureFilename.data());
    this->platformSprite.setTexture(platformTexture);
    StaticPlatform::setSize(static_cast<sf::Vector2f>(platformTexture.getSize()));
}

template<typename T, size_t count>
void Platforms<T, count>::changePlatformPosition(float height, float doodleDy,
                                                 std::uniform_real_distribution<float> randomX_Generator,
                                                 std::uniform_real_distribution<float> randomSmallY_Generator,
                                                 std::mt19937 &mt) {
    std::for_each_n(platforms.begin(), actualPlatformAmount,
                    [&](auto &plat) mutable {
                        if (plat.getY() > height) {
                            plat.setY(randomSmallY_Generator(mt));
                            plat.setX(randomX_Generator(mt));
                        } else {
                            plat.changeY(-doodleDy);
                        }
                    });

}

template<typename T, size_t count>
void Platforms<T, count>::checkDoodleCollision(Doodle &doodle) {
    std::for_each_n(platforms.begin(), actualPlatformAmount, [&](const auto &plat) {
        if (plat.collisionDetected(doodle)) {
            if (doodle.getDy() > 0) {
                doodle.setDy(-10);
            }
        }
    });
}

template<typename T, size_t count>
void Platforms<T, count>::drawPlatforms(sf::RenderWindow &window) {
    std::for_each_n(platforms.begin(), actualPlatformAmount, [&](auto &plat) {
        platformSprite.setPosition(plat.getX(), plat.getY());
        window.draw(platformSprite);
    });
}

template<typename T, size_t count>
[[nodiscard]] constexpr std::array<T, count> &Platforms<T, count>::getPlatforms() const {
    return platforms;
}

template<typename T, size_t count>
[[nodiscard]] std::array<T, count> &Platforms<T, count>::getPlatforms() {
    return platforms;
}