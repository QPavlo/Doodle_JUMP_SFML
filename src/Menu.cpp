#include "../headers/Menu.hpp"

Menu::Menu(float width, float height) {
    if (!Menu::font.loadFromFile("../font/arial.ttf")) {
        std::cerr << "font not found\n";
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition((width / 2) - (width / 10), height / (Num_Of_Items + 1) * 1);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition((width / 2) - (width / 10), height / (Num_Of_Items + 1) * 2);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition((width / 2) - (width / 10), height / (Num_Of_Items + 1) * 3);

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window) {
    for (int32_t i = 0; i < Num_Of_Items; ++i) {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex -= 1;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < Num_Of_Items) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex += 1;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}