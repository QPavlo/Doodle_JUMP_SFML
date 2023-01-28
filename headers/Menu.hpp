#ifndef SFML_TEST_MENU_HPP
#define SFML_TEST_MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>


class Menu {
public:

    enum class MenuOption : int32_t {
        PLAY_GAME_OPTION = 0,
        OPTIONS_OPTION = 1,
        EXIT_OPTION = 2
    };

    Menu(float width, float height);

    ~Menu() = default;

    void draw(sf::RenderWindow &window);

    void MoveUp();

    void MoveDown();

    int GetPressedItem() const { return selectedItemIndex; }

    const sf::Font &getFond() { return font; }

private:
    static constexpr uint32_t Num_Of_Items = 3;
    int selectedItemIndex;
    sf::Font font;
    std::array<sf::Text, Num_Of_Items> menu;
};

#endif
