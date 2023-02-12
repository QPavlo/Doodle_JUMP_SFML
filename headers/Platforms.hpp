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

    explicit Platforms(std::string_view textureFilename);

    void changePlatformPosition(float height,
                                float doodleDy,
                                std::uniform_real_distribution<float> randomX_Generator,
                                std::uniform_real_distribution<float> randomSmallY_Generator,
                                std::mt19937 &mt);

    virtual void changePlatformsAmount(float height, uint32_t score) = 0;

    void checkDoodleCollision(Doodle &doodle);

    void drawPlatforms(sf::RenderWindow &window);

    [[nodiscard]] constexpr std::array<T, count> &getPlatforms() const;

    [[nodiscard]] std::array<T, count> &getPlatforms();

protected:
    sf::Texture platformTexture;
    sf::Sprite platformSprite;
    std::array<T, count> platforms{};
    int32_t actualPlatformAmount{0};
};

#endif //SFML_DOODLE_JUMP_PLATFORMS_HPP
