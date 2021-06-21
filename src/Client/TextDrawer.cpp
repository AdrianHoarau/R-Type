/*
** TextDrawer.cpp for lib_test in /home/arthurbertaud/Second_year/OOP/lib_test/src
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Thu Mar 12 7:09:27 PM 2020 arthurbertaud
** Last update Tue Mar 23 4:03:00 PM 2020 arthurbertaud
*/

#include "TextDrawer.hpp"
#include <iostream>

TextDrawer::TextDrawer()
{
    if (_font.loadFromFile(defaultFont))
        _text.setFont(_font);
    else
    {
        std::cerr << "Error: cannot load font, the path might be erroned, default path will be used." << std::endl;
        if (_font.loadFromFile(defaultFont))
            _text.setFont(_font);
    }
}

void TextDrawer::draw(sf::Vector2f pos, const std::string& to_print, sf::RenderWindow& window, const sf::Color& color)
{
    _text.setString(to_print);
    _text.setPosition(pos);
    _text.setCharacterSize(45);
    _text.setFillColor(color);
    window.draw(_text);
}

void TextDrawer::drawSize(sf::Vector2f pos, const std::string& to_print, sf::RenderWindow& window, int size, const sf::Color& color)
{
    _text.setString(to_print);
    _text.setPosition(pos);
    _text.setCharacterSize(size);
    _text.setFillColor(color);
    window.draw(_text);
}

void TextDrawer::drawPos(sf::Vector2f pos, const std::string& to_print, sf::RenderWindow& window, int size, const sf::Vector2f& scale, const sf::Color& color)
{
    pos.x *= scale.x;
    pos.y *= scale.y;
    _text.setString(to_print);
    _text.setPosition(pos);
    _text.setCharacterSize(size);
    _text.setFillColor(color);
    window.draw(_text);
}

void TextDrawer::setScale(const sf::Vector2f& scale)
{
    _scale = scale;
}