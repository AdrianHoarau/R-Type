/*
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Thu Mar 12 6:59:12 PM 2020 arthurbertaud
** Last update Sat Apr 3 5:25:38 PM 2020 arthurbertaud
*/

#ifndef TextDrawer_HPP_
#define TextDrawer_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#define defaultFont "../../ressources/fonts/04b_25__.ttf"

class TextDrawer
{
public:
    TextDrawer();
    TextDrawer(const TextDrawer&) = default;
    TextDrawer& operator=(const TextDrawer&) = default;
    ~TextDrawer() = default;
    void draw(sf::Vector2f, const std::string& , sf::RenderWindow& , const sf::Color& color = sf::Color::White);
    void setScale(const sf::Vector2f& scale);
    void drawSize(sf::Vector2f pos, const std::string& to_print, sf::RenderWindow& window, int size, const sf::Color& color= sf::Color::Black);
    void drawPos(sf::Vector2f pos, const std::string& to_print, sf::RenderWindow& window, int size, const sf::Vector2f& scale, const sf::Color& color= sf::Color::White);
protected:
private:
    sf::Font _font;
    sf::Text _text;
    sf::Vector2f _scale;
};

#endif /* !TextDrawer_HPP_ */