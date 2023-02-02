#include "../headers/Menu.hpp"
#include "../headers/StaticPlatform.hpp"
#include "../headers/MovablePlatform.hpp"
#include "../headers/Doodle.hpp"
#include "../headers/Obstacle.hpp"
#include "../headers/Platforms.hpp"
#include "../headers/StaticPlatforms.hpp"
#include "../headers/MovablePlatforms.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <array>

template<typename T>
[[nodiscard]] constexpr T negative(T num) {
    return -num;
}

enum MonsterCollision : uint32_t {
    NO_COLLISION = 0,
    COLLISION_FROM_BOTTOM = 1,
    COLLISION_FROM_TOP = 2
};

[[nodiscard]] int32_t monster_collision_detection(const Doodle &doodle,
                                                  const Obstacle &monster) {

    if (((doodle.getX() + (doodle.getSize().x / 1.5f) > monster.getX()) and
         (doodle.getX() + (doodle.getSize().x / 3.0f) < monster.getX() + monster.getSize().x) and
         (doodle.getY() + doodle.getSize().y > monster.getY()) and
         (doodle.getY() + doodle.getSize().y < monster.getY() + 0.2f * monster.getSize().y))) {
        return MonsterCollision::COLLISION_FROM_TOP;
    }

    if ((doodle.getX() + (doodle.getSize().x / 1.5f) > monster.getX()) and
        (doodle.getX() + (doodle.getSize().x / 3.0f) < monster.getX() + monster.getSize().x) and
        (doodle.getY() + doodle.getSize().y - 45 > monster.getY()) and
        (doodle.getY() < monster.getY() + monster.getSize().y - 45)) {
        return MonsterCollision::COLLISION_FROM_BOTTOM;
    }
    return MonsterCollision::NO_COLLISION;
}

[[nodiscard]] bool platform_collision_detection(const Doodle &doodle,
                                                const StaticPlatform &platform) {
    if ((doodle.getX() + (doodle.getSize().x / 1.5f) > platform.getX()) and
        (doodle.getX() + (doodle.getSize().x / 3.0f) < platform.getX() + StaticPlatform::getSize().x) and
        (doodle.getY() + doodle.getSize().y > platform.getY()) and
        (doodle.getY() + doodle.getSize().y < platform.getY() + StaticPlatform::getSize().y)) {
        return true;
    }
    return false;
}

void play_game(sf::RenderWindow &window, const sf::Font &font);

void lose_game_window(sf::RenderWindow &window) {
    sf::Texture lose_screen;
    lose_screen.loadFromFile("../img/lose_screen.png");
    sf::Sprite spriteLose_screen{lose_screen};
    spriteLose_screen.scale(1.15, 1.65);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    play_game(window, sf::Font());
                }
            }
        }
        window.clear();
        window.draw(spriteLose_screen);
        window.display();
    }
}

void play_game(sf::RenderWindow &window, const sf::Font &font) {
    float width = static_cast<float>(window.getSize().x);
    float height = static_cast<float>(window.getSize().y);
    uint32_t score = 0;

    sf::Texture platform, movable_platform, background;

    platform.loadFromFile("../img/platform.png");
    movable_platform.loadFromFile("../img/movable_platform.png");
    background.loadFromFile("../img/background.png");

    sf::Sprite spritePlatform{platform},
            spriteM_Platform{movable_platform},
            spriteBackground{background};


    std::array<StaticPlatform, 10> platforms{};
    std::array<MovablePlatform, 5> movable_platforms{};

    Doodle doodle{"../img/doodle.png"};
    Obstacle monster{"../img/monster.png"};
    MovablePlatform::setSize(static_cast<sf::Vector2f>(platform.getSize()));

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distribution_x(0, width - MovablePlatform::getSize().x);
    std::uniform_real_distribution<float> distribution_y(0, height);
    std::uniform_real_distribution<float> small_distribution_y(0, height / 10);

    StaticPlatforms<10> platforms1{"../img/platform.png", distribution_x, distribution_y, mt};

    for (auto &plat: platforms) {
        plat.setX(distribution_x(mt));
        plat.setY(distribution_y(mt));
    }

    for (auto &m_plat: movable_platforms) {
        m_plat.setCoordinates(distribution_x(mt), negative(distribution_y(mt)));
    }

    monster.setPosition({distribution_x(mt), negative(distribution_y(mt))});

    float h = 250;
    float dx = 3.0f;
    bool monster_flag = false;
    int32_t less_platforms = 0;

    for (auto &m_plat: movable_platforms) {
        m_plat.setSpeed(dx);
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            doodle.changeX(5);

            if (doodle.getX() > width) {
                doodle.setX(negative(doodle.getSize().x));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            doodle.changeX(-5);

            if (doodle.getX() + doodle.getSize().x < 0) {
                doodle.setX(width);
            }
        }

        doodle.changeDy(0.25f);
        doodle.changeY(doodle.getDy());

        if (doodle.getY() > height - 33) {
            lose_game_window(window);
        }

        if (doodle.getY() < h) {
            score += static_cast<uint32_t>(doodle.getY() / 100);
            doodle.setY(h);

            platforms1.changePlatformPosition(height, doodle.getDy());
            platforms1.changePlatformsAmount(height, score);

            if (score > 1000) {
                for (auto &m_plat: movable_platforms) {
                    if (m_plat.getY() > height) {
                        m_plat.setY(negative(small_distribution_y(mt)));
                        m_plat.setX(distribution_x(mt));
                    } else {
                        m_plat.changeY(-doodle.getDy());
                    }
                }

                if (monster_flag) {
                    if (monster.getY() > height) {
                        monster.setX(distribution_x(mt));
                        monster.setY(negative(monster.getSize().y));
                    } else {
                        monster.setY(monster.getY() - doodle.getDy());
                    }

                    if (monster.getY() > height) {
                        monster_flag = false;
                    }
                }
            }
        }

        platforms1.checkDoodleCollision(doodle);
        window.draw(spriteBackground);
        window.draw(doodle.getSprite());

        platforms1.drawPlatforms(window);


#pragma region
        if (score > 1000) {
            for (const auto &m_plat: movable_platforms) {
                if (platform_collision_detection(doodle, m_plat)) {
                    if (doodle.getDy() > 0) {
                        doodle.setDy(-10);
                    }
                }
            }

            if (score % 100 == 0) {
                dx += 0.02;
            }

            for (auto &m_plat: movable_platforms) {
                m_plat.changeX(m_plat.getSpeed());
                if (m_plat.getX() > width - MovablePlatform::getSize().x) {
                    m_plat.setSpeed(-dx);
                } else if (m_plat.getX() < 0) {
                    m_plat.setSpeed(dx);
                }

                spriteM_Platform.setPosition(m_plat.getX(), m_plat.getY());
                window.draw(spriteM_Platform);
            }

            float temp_rand = distribution_x(mt);

            if (temp_rand >= 244.92 and temp_rand <= 245 and !monster_flag) {
                monster_flag = true;
            }

            if (monster_flag) {
//                monster.setPosition(spriteMonster.getPosition());
                auto monster_coll_det = monster_collision_detection(doodle,
                                                                    monster);

                if (monster_coll_det == MonsterCollision::COLLISION_FROM_BOTTOM) {
                    lose_game_window(window);
                } else if (monster_coll_det == MonsterCollision::COLLISION_FROM_TOP) {
                    doodle.setDy(-10);
                    monster.setPosition({1000, 1000});
                }
//                spriteMonster.setPosition(monster.getPosition());

                monster.getSprite().setPosition(monster.getPosition());
                window.draw(monster.getSprite());
            }
        }
#pragma endregion

        sf::Text textScore{};

        textScore.setFont(font);
        textScore.setFillColor(sf::Color::Black);
        textScore.setString("score: " + std::to_string(score));
        textScore.setPosition(30, 20);

        window.draw(textScore);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 533), "Obstacle Jump!");
    window.setFramerateLimit(60);

    Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Enter:
                        switch (menu.GetPressedItem()) {
                            case static_cast<int32_t>(Menu::MenuOption::PLAY_GAME_OPTION) :
                                window.clear();
                                play_game(window, menu.getFond());
                                break;
                            case static_cast<int32_t>(Menu::MenuOption::OPTIONS_OPTION):
                                std::cout << "Option button has been pressed\n"; // implement later
                                break;
                            case static_cast<int32_t>(Menu::MenuOption::EXIT_OPTION):
                                window.close();
                                break;
                            default:
                                std::cerr << "default case worked in menu\n";
                                break;
                        }
                        break;
                    default:
                        std::cerr << "default case worked out menu, in event\n";
                        break;
                }
            } else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
    return 0;
}