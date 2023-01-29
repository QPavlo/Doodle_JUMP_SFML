#include "../headers/Menu.hpp"
#include "../headers/StaticPlatform.hpp"
#include "../headers/MovablePlatform.hpp"
#include "../headers/Doodle.hpp"
#include "../headers/Obstacle.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <array>

template<typename T>
[[nodiscard]] constexpr T negative(T num) {
    return -num;
}

[[nodiscard]] int32_t monster_collision_detection(const Doodle &doodle,
                                                  const Obstacle &monster) {

    if (((doodle.getX() + (doodle.getSize().x / 1.5f) > monster.getX()) and
         (doodle.getX() + (doodle.getSize().x / 3.0f) < monster.getX() + BasePlatform::getSize().x) and
         (doodle.getY() + doodle.getSize().y > monster.getY()) and
         (doodle.getY() + doodle.getSize().y < monster.getY() + BasePlatform::getSize().y))) {
        return 2;
    }

    if ((doodle.getX() + (doodle.getSize().x / 1.5f) > monster.getX()) and
        (doodle.getX() + (doodle.getSize().x / 3.0f) < monster.getX() + monster.getSize().x) and
        (doodle.getY() + doodle.getSize().y - 30 > monster.getY()) and
        (doodle.getY() < monster.getY() + monster.getSize().y - 30)) {
        return 1;
    }
    return 0;
}

[[nodiscard]] bool platform_collision_detection(const Doodle &doodle,
                                                const BasePlatform &platform) {
    if ((doodle.getX() + (doodle.getSize().x / 1.5f) > platform.getX()) and
        (doodle.getX() + (doodle.getSize().x / 3.0f) < platform.getX() + BasePlatform::getSize().x) and
        (doodle.getY() + doodle.getSize().y > platform.getY()) and
        (doodle.getY() + doodle.getSize().y < platform.getY() + BasePlatform::getSize().y)) {
        return true;
    }
    return false;
}

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

    sf::Texture doodle, platform, movable_platform, background, monster;

    doodle.loadFromFile("../img/doodle.png");
    platform.loadFromFile("../img/platform.png");
    movable_platform.loadFromFile("../img/movable_platform.png");
    background.loadFromFile("../img/background.png");
    monster.loadFromFile("../img/monster.png");

    sf::Sprite spriteDoodle{doodle},
            spritePlatform{platform},
            spriteM_Platform{movable_platform},
            spriteBackground{background},
            spriteMonster{monster};


    float monster_scale = 0.4f;

    spriteMonster.scale(monster_scale, monster_scale);

    std::array<StaticPlatform, 10> platforms{};
    std::array<MovablePlatform, 4> movable_platforms{};

    Doodle doodle_params{static_cast<sf::Vector2f>(doodle.getSize())};
    Obstacle monster_params{monster_scale * static_cast<sf::Vector2f>(monster.getSize())};
    MovablePlatform::setSize(static_cast<sf::Vector2f>(platform.getSize()));

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distribution_x(0, width - MovablePlatform::getSize().x);
    std::uniform_real_distribution<float> distribution_y(0, height);
    std::uniform_real_distribution<float> small_distribution_y(0, height / 10);

    for (auto &plat: platforms) {
        plat.setX(distribution_x(mt));
        plat.setY(distribution_y(mt));
    }

    for (auto &m_plat: movable_platforms) {
        m_plat.setCoordinates(distribution_x(mt), negative(distribution_y(mt)));
    }


    monster_params.setCoordinates({distribution_x(mt), negative(distribution_y(mt))});

    float h = 250;

    float dy = 0.0f, dx = 3.0f;
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
            doodle_params.changeX(5);

            if (doodle_params.getX() > width) {
                doodle_params.setX(negative(doodle_params.getCoordinates().x));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            doodle_params.changeX(-5);

            if (doodle_params.getX()
                + doodle_params.getSize().x < 0) {
                doodle_params.setX(width);
            }
        }

        dy += 0.25f;
//        y += dy;

        doodle_params.changeY(dy);

        if (doodle_params.getY() > height - 33) {
            lose_game_window(window);
        }

        if (doodle_params.getY() < h) {
            score += static_cast<uint32_t>(doodle_params.getY() / 100);
            doodle_params.setY(h);

            std::for_each_n(platforms.begin(), platforms.size() - less_platforms,
                            [&, i = 0](auto &plat) mutable {
                                if (plat.getY() > height) {
                                    if (less_platforms < 5
                                        and i == platforms.size() - less_platforms - 1
                                        and score > 800 * (less_platforms + 1)
                                            ) {
                                        less_platforms += 1;
                                    } else {
                                        plat.setY(0);
                                        plat.setX(distribution_x(mt));
                                    }
                                } else {
                                    plat.changeY(-dy);
                                }
                                i += 1;
                            });

            if (score > 10) {
                for (auto &m_plat: movable_platforms) {
                    if (m_plat.getY() > height) {
                        m_plat.setY(negative(small_distribution_y(mt)));
                        m_plat.setX(distribution_x(mt));
                    } else {
                        m_plat.changeY(-dy);
                    }
                }

                if (monster_flag) {
                    if (monster_params.getY() > height) {
                        monster_params.setX(distribution_x(mt));
                        monster_params.setY(negative(static_cast<float>(monster.getSize().y)));

//                        spriteMonster.setPosition(distribution_x(mt),
//                                                  negative(static_cast<float>(monster.getSize().y)));
                    } else {
                        monster_params.setY(monster_params.getY() - dy);
//                        spriteMonster.setPosition(spriteMonster.getPosition().x, spriteMonster.getPosition().y - dy);
                    }

                    if (monster_params.getY() > height) {
                        monster_flag = false;
                    }
                }
            }
        }

        std::for_each_n(platforms.begin(), platforms.size() - less_platforms, [&](const auto &plat) {
            if (platform_collision_detection(doodle_params, plat)) {
                if (dy > 0) {
                    dy = -10;
                }
            }
        });

        spriteDoodle.setPosition(doodle_params.getX(), doodle_params.getY());
        window.draw(spriteBackground);
        window.draw(spriteDoodle);

        std::for_each_n(platforms.begin(), platforms.size() - less_platforms, [&](auto &plat) {
            spritePlatform.setPosition(plat.getX(), plat.getY());
            window.draw(spritePlatform);
        });

        if (score > 10) {
            for (const auto &m_plat: movable_platforms) {
                if (platform_collision_detection(doodle_params, m_plat)) {
                    if (dy > 0) {
                        dy = -10;
                    }
                }
            }

            if (score % 100 == 0) {
                dx += 0.03;
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
//                monster_params.setCoordinates(spriteMonster.getPosition());
                auto monster_coll_det = monster_collision_detection(doodle_params,
                                                                    monster_params);
                if (monster_coll_det == 1) {
                    lose_game_window(window);
                } else if (monster_coll_det == 2) {
                    if (dy > 0) {
                        dy = -10;
                    }
                    monster_params.setCoordinates({1000, 1000});

                }
                spriteMonster.setPosition(monster_params.getCoordinates());
                window.draw(spriteMonster);
            }
        }

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