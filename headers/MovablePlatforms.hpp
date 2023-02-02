#ifndef SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP
#define SFML_DOODLE_JUMP_MOVABLE_PLATFORMS_HPP

#include "Platforms.hpp"
#include <iostream>

template<size_t count>
class MovablePlatforms : public Platforms<MovablePlatform, count> {
public:
    void changePlatformsAmount(float height, uint32_t score) {
        std::for_each_n(this->platforms.begin(), this->actualPlatformAmount,
                        [&, i = 0](auto &plat) mutable {
                            if (plat.getY() > height) {
                                if (this->actualPlatformAmount <= count
                                    and i == this->actualPlatformAmount - 1
                                    and score > 800 * (this->platforms.size() - this->actualPlatformAmount + 1)
                                        ) {
                                    std::cout << "less pl\n";
                                    this->actualPlatformAmount += 1;
                                }
                            }
                            i += 1;
                        });
    }


protected:
    float speedDx{0};
};

#endif
