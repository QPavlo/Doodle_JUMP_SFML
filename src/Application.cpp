#include "../headers/Menu.hpp"
#include "../headers/StaticPlatform.hpp"
#include "../headers/MovablePlatform.hpp"
#include "../headers/Doodle.hpp"
#include "../headers/Obstacle.hpp"
#include "../headers/Platforms.hpp"
#include "../headers/StaticPlatforms.hpp"
#include "../headers/MovablePlatforms.hpp"

#include "Platforms.cpp"
#include "StaticPlatforms.cpp"
#include "MovablePlatforms.cpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

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
                    throw 0; // implement later
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

    sf::Texture background;
    background.loadFromFile("../img/background.png");

    sf::Sprite spriteBackground{background};

    sf::Texture bullet;
    bullet.loadFromFile("../img/bullet.png");

    sf::Sprite bulletSprite{bullet};
    bulletSprite.setScale(3, 3);
    bool bulletFlag = false;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> randomX_Generator(0, width - 60);
    std::uniform_real_distribution<float> randomY_Generator(0, height);
    std::uniform_real_distribution<float> randomSmallY_Generator(-30, 0);

    Doodle doodle{"../img/doodle.png"};
    Obstacle monster{"../img/monster.png", randomX_Generator(mt), mt};

    StaticPlatforms<10> staticPlatforms{"../img/platform.png", randomX_Generator, randomY_Generator, mt};
    MovablePlatforms<5> movablePlatforms{"../img/movable_platform.png", randomX_Generator, randomY_Generator, mt, 3.0f};

    float h = 250;

    while (window.isOpen()) {
        window.draw(spriteBackground);
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            doodle.changeX(5);

            if (doodle.getX() > width) {
                doodle.setX(-(doodle.getSize().x));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            doodle.changeX(-5);

            if (doodle.getX() + doodle.getSize().x < 0) {
                doodle.setX(width);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and !bulletFlag) {
            bulletSprite.setPosition(doodle.getPosition().x + (doodle.getSize() * 0.73f).x,
                                     doodle.getPosition().y);
            bulletFlag = true;
        }

        doodle.changeDy(0.25f);
        doodle.changeY(doodle.getDy());

        if (doodle.getY() > height - 33) {
            lose_game_window(window);
        }

        if (doodle.getY() < h) {
            score += static_cast<uint32_t>(doodle.getY() / 100);
            doodle.setY(h);

            staticPlatforms.changePlatformPosition(height, doodle.getDy(), randomX_Generator,
                                                   randomSmallY_Generator, mt);
            staticPlatforms.changePlatformsAmount(height, score);

            if (score > 100) {
                movablePlatforms.changePlatformPosition(height,
                                                        doodle.getDy(),
                                                        randomX_Generator,
                                                        randomSmallY_Generator, mt);
                movablePlatforms.changePlatformsAmount(height, score);

                monster.changeObstaclePosition(height, doodle.getDy(), randomX_Generator(mt));
            }
        }
        doodle.drawDoodle(window);

        bulletSprite.setPosition(bulletSprite.getPosition().x,
                                 bulletSprite.getPosition().y - 25
        );

        if (bulletSprite.getPosition().y < 0) {
            bulletFlag = false;
        }

        if (bulletFlag) {
            monster.collisionDetected(bulletSprite);
            window.draw(bulletSprite);
        }

        staticPlatforms.checkDoodleCollision(doodle);
        staticPlatforms.drawPlatforms(window);

        if (score > 100) {
            movablePlatforms.checkDoodleCollision(doodle);

            if (score % 100 == 0) {
                movablePlatforms.changeDx(0.02);
            }

            movablePlatforms.changePlatformsPositionX(width);
            movablePlatforms.drawPlatforms(window);

            monster.spawnObstacle(randomX_Generator(mt), randomY_Generator(mt));
            monster.checkDoodleCollision(doodle, window);
            monster.drawObstacle(window);
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
    sf::RenderWindow window(sf::VideoMode(400, 533), "Doodle Jump!");
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
                        }
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